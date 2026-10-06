import subprocess
from pathlib import Path

from .models import DisasterArea


def calculate_priorities_with_cpp():

    areas = list(
        DisasterArea.objects.all().order_by("id")
    )

    if not areas:
        return

    # -------------------------------------------------
    # Actual C++ folder
    #
    # disasterReliefSystem/
    #     disaster_system/
    #         core_cpp/
    # -------------------------------------------------

    project_directory = Path(__file__).resolve().parent.parent

    cpp_directory = (
        project_directory
        / "disaster_system"
        / "core_cpp"
    )

    executable = cpp_directory / "priority_bridge.exe"

    if not executable.exists():

        raise FileNotFoundError(
            f"C++ priority executable not found: {executable}"
        )

    # -------------------------------------------------
    # Prepare data for C++
    # -------------------------------------------------

    input_lines = [
        str(len(areas))
    ]

    for area in areas:

        input_lines.append(
            "\t".join([
                area.areaName,
                str(area.severity),
                str(area.populationAffected),
                str(area.medicalNeed),
                str(area.waitingTime),
                str(area.resourceDemand),
            ])
        )

    cpp_input = "\n".join(input_lines) + "\n"

    # -------------------------------------------------
    # Run C++ program
    # -------------------------------------------------

    result = subprocess.run(
        [str(executable)],
        input=cpp_input,
        text=True,
        capture_output=True,
        cwd=str(cpp_directory),
    )

    # -------------------------------------------------
    # Check C++ execution
    # -------------------------------------------------

    if result.returncode != 0:

        raise RuntimeError(
            "C++ priority calculator failed:\n"
            + result.stderr
        )

    # -------------------------------------------------
    # Read C++ results
    #
    # Format:
    # index|score|level
    # -------------------------------------------------

    results = result.stdout.strip().splitlines()

    for line in results:

        if not line:
            continue

        parts = line.split("|")

        if len(parts) != 3:
            continue

        index = int(parts[0])

        score = float(parts[1])

        level = parts[2]

        area = areas[index]

        area.priorityScore = round(
            score,
            2
        )

        area.priorityLevel = level

        area.save(
            update_fields=[
                "priorityScore",
                "priorityLevel"
            ]
        )