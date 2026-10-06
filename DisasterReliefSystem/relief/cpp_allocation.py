import subprocess
from pathlib import Path

from django.conf import settings

from .models import (
    AvailableResources,
    ResourceRequest,
    AllocationRecord,
    RemainingResources,
)


def allocate_resources_with_cpp():

    """
    Sends resource data from Django to the C++ allocation program.

    Django:
        - Reads data from database
        - Sends input to C++
        - Saves C++ output

    C++:
        - Performs actual resource allocation
        - Calculates allocated and unmet resources
        - Calculates remaining resources
    """

    # ---------------------------------------------------------
    # 1. Get available resources
    # ---------------------------------------------------------

    available = AvailableResources.objects.order_by("-id").first()

    if available is None:
        raise ValueError("No available resources found.")

    # ---------------------------------------------------------
    # 2. Get resource requests in priority order
    # ---------------------------------------------------------

    # Higher priority areas are processed first.
    # The C++ ResourceAllocator allocates resources
    # in the order in which requests are supplied.

    requests = list(
        ResourceRequest.objects
        .select_related("area")
        .order_by("-area__priorityScore", "area__id")
    )

    # Remove old allocation results if there are no requests.
    if not requests:
        AllocationRecord.objects.all().delete()
        RemainingResources.objects.all().delete()
        return

    # ---------------------------------------------------------
    # 3. Locate C++ executable
    # ---------------------------------------------------------

    # Project structure:
    #
    # DisasterReliefSystem/
    #     disaster_system/
    #         core_cpp/
    #             allocation_bridge.exe
    #
    # BASE_DIR points to:
    # DisasterReliefSystem/

    cpp_directory = (
        Path(settings.BASE_DIR)
        / "disaster_system"
        / "core_cpp"
    )

    executable = cpp_directory / "allocation_bridge.exe"

    if not executable.exists():
        raise FileNotFoundError(
            f"C++ allocation executable not found: {executable}"
        )

    # ---------------------------------------------------------
    # 4. Prepare input for C++ bridge
    # ---------------------------------------------------------

    input_lines = []

    # First line:
    # food water medicine blankets

    input_lines.append(
        f"{available.food} "
        f"{available.water} "
        f"{available.medicine} "
        f"{available.blankets}"
    )

    # Second line:
    # number of requests

    input_lines.append(str(len(requests)))

    # Following lines:
    #
    # areaName|priorityScore|priorityLevel|waitingTime|
    # foodDemand|waterDemand|medicineDemand|blanketDemand

    for request in requests:

        area = request.area

        input_lines.append(
            "|".join([
                area.areaName,
                str(area.priorityScore),
                area.priorityLevel,
                str(area.waitingTime),
                str(request.foodDemand),
                str(request.waterDemand),
                str(request.medicineDemand),
                str(request.blanketDemand),
            ])
        )

    cpp_input = "\n".join(input_lines) + "\n"

    # ---------------------------------------------------------
    # 5. Run C++ allocation program
    # ---------------------------------------------------------

    result = subprocess.run(
        [str(executable)],
        input=cpp_input,
        text=True,
        capture_output=True,
        cwd=str(cpp_directory),
    )

    # ---------------------------------------------------------
    # 6. Check C++ execution
    # ---------------------------------------------------------

    if result.returncode != 0:

        raise RuntimeError(
            "C++ resource allocation failed:\n"
            + result.stderr
        )

    # ---------------------------------------------------------
    # 7. Remove old allocation results
    # ---------------------------------------------------------

    AllocationRecord.objects.all().delete()
    RemainingResources.objects.all().delete()

    # ---------------------------------------------------------
    # 8. Process C++ output
    # ---------------------------------------------------------

    output_lines = result.stdout.strip().splitlines()

    for line in output_lines:

        if not line:
            continue

        parts = line.split("|")

        # -----------------------------------------------------
        # Remaining resources
        # -----------------------------------------------------

        if parts[0] == "REMAINING":

            if len(parts) != 5:
                continue

            try:

                RemainingResources.objects.create(
                    food=int(parts[1]),
                    water=int(parts[2]),
                    medicine=int(parts[3]),
                    blankets=int(parts[4]),
                )

            except ValueError:
                continue

            continue

        # -----------------------------------------------------
        # Allocation record
        # -----------------------------------------------------

        if len(parts) != 16:
            continue

        try:

            index = int(parts[0])

            priority_score = float(parts[2])

            food_demand = int(parts[4])
            food_allocated = int(parts[5])
            food_unmet = int(parts[6])

            water_demand = int(parts[7])
            water_allocated = int(parts[8])
            water_unmet = int(parts[9])

            medicine_demand = int(parts[10])
            medicine_allocated = int(parts[11])
            medicine_unmet = int(parts[12])

            blanket_demand = int(parts[13])
            blanket_allocated = int(parts[14])
            blanket_unmet = int(parts[15])

        except ValueError:

            continue

        # -----------------------------------------------------
        # Make sure index is valid
        # -----------------------------------------------------

        if index < 0 or index >= len(requests):
            continue

        request = requests[index]

        area = request.area

        # -----------------------------------------------------
        # Save C++ result into Django database
        # -----------------------------------------------------

        AllocationRecord.objects.create(

            area=area,

            priorityScore=priority_score,

            priorityLevel=parts[3],

            foodDemand=food_demand,
            foodAllocated=food_allocated,
            foodUnmet=food_unmet,

            waterDemand=water_demand,
            waterAllocated=water_allocated,
            waterUnmet=water_unmet,

            medicineDemand=medicine_demand,
            medicineAllocated=medicine_allocated,
            medicineUnmet=medicine_unmet,

            blanketDemand=blanket_demand,
            blanketAllocated=blanket_allocated,
            blanketUnmet=blanket_unmet,
        )