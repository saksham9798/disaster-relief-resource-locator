from .models import DisasterArea


def normalize_scale(value, maximum_value):
    """
    Normalize a value to a 0-100 scale.
    """

    if maximum_value <= 0:
        return 0

    return (value / maximum_value) * 100


def calculate_priority(area, maximum_population,
                       maximum_waiting_time,
                       maximum_resource_demand):

    severity_score = (
        (area.severity - 1) / 9
    ) * 100

    medical_score = (
        (area.medicalNeed - 1) / 9
    ) * 100

    population_score = normalize_scale(
        area.populationAffected,
        maximum_population
    )

    waiting_score = normalize_scale(
        area.waitingTime,
        maximum_waiting_time
    )

    resource_score = normalize_scale(
        area.resourceDemand,
        maximum_resource_demand
    )

    priority_score = (

        severity_score * 0.30

        + population_score * 0.25

        + medical_score * 0.20

        + waiting_score * 0.15

        + resource_score * 0.10
    )

    return round(priority_score, 2)


def get_priority_level(priority_score):

    if priority_score >= 80:
        return "Critical"

    elif priority_score >= 60:
        return "High"

    elif priority_score >= 40:
        return "Medium"

    else:
        return "Low"


def calculate_all_priorities():

    areas = list(
        DisasterArea.objects.all()
    )

    if not areas:
        return

    maximum_population = max(
        area.populationAffected
        for area in areas
    )

    maximum_waiting_time = max(
        area.waitingTime
        for area in areas
    )

    maximum_resource_demand = max(
        area.resourceDemand
        for area in areas
    )

    for area in areas:

        score = calculate_priority(
            area,
            maximum_population,
            maximum_waiting_time,
            maximum_resource_demand
        )

        area.priorityScore = score

        area.priorityLevel = get_priority_level(
            score
        )

        area.save(
            update_fields=[
                "priorityScore",
                "priorityLevel"
            ]
        )