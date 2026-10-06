
from django.db import models


class DisasterArea(models.Model):
    areaName = models.CharField(max_length=100)

    severity = models.FloatField(default=1)

    populationAffected = models.PositiveIntegerField(default=0)

    medicalNeed = models.FloatField(default=1)

    waitingTime = models.FloatField(default=0)

    resourceDemand = models.PositiveIntegerField(default=0)

    priorityScore = models.FloatField(default=0.0)

    priorityLevel = models.CharField(
        max_length=20,
        default="Not Calculated"
    )

    def __str__(self):
        return self.areaName


class AvailableResources(models.Model):
    """
    Represents the resources available for allocation.

    Matches the resource quantities used by the C++
    ResourceAllocator.
    """

    food = models.PositiveIntegerField(default=0)

    water = models.PositiveIntegerField(default=0)

    medicine = models.PositiveIntegerField(default=0)

    blankets = models.PositiveIntegerField(default=0)

    def __str__(self):
        return (
            f"Food: {self.food}, "
            f"Water: {self.water}, "
            f"Medicine: {self.medicine}, "
            f"Blankets: {self.blankets}"
        )


class ResourceRequest(models.Model):
    """
    Represents the resource demand of a disaster area.

    Matches the ResourceRequest concept used by the
    C++ ResourceAllocator.
    """

    area = models.ForeignKey(
        DisasterArea,
        on_delete=models.CASCADE,
        related_name="resource_requests"
    )

    foodDemand = models.PositiveIntegerField(default=0)

    waterDemand = models.PositiveIntegerField(default=0)

    medicineDemand = models.PositiveIntegerField(default=0)

    blanketDemand = models.PositiveIntegerField(default=0)

    def __str__(self):
        return f"{self.area.areaName} Resource Request"


class AllocationRecord(models.Model):
    """
    Stores the result of resource allocation for an area.

    This corresponds to the AllocationRecord generated
    by the C++ ResourceAllocator.
    """

    area = models.ForeignKey(
        DisasterArea,
        on_delete=models.CASCADE,
        related_name="allocation_records"
    )

    priorityScore = models.FloatField(default=0.0)

    priorityLevel = models.CharField(
        max_length=20,
        default="Not Calculated"
    )

    foodDemand = models.PositiveIntegerField(default=0)
    foodAllocated = models.PositiveIntegerField(default=0)
    foodUnmet = models.PositiveIntegerField(default=0)

    waterDemand = models.PositiveIntegerField(default=0)
    waterAllocated = models.PositiveIntegerField(default=0)
    waterUnmet = models.PositiveIntegerField(default=0)

    medicineDemand = models.PositiveIntegerField(default=0)
    medicineAllocated = models.PositiveIntegerField(default=0)
    medicineUnmet = models.PositiveIntegerField(default=0)

    blanketDemand = models.PositiveIntegerField(default=0)
    blanketAllocated = models.PositiveIntegerField(default=0)
    blanketUnmet = models.PositiveIntegerField(default=0)

    def __str__(self):
        return f"{self.area.areaName} Allocation"


class RemainingResources(models.Model):
    """
    Stores the resources remaining after allocation.
    """

    food = models.PositiveIntegerField(default=0)

    water = models.PositiveIntegerField(default=0)

    medicine = models.PositiveIntegerField(default=0)

    blankets = models.PositiveIntegerField(default=0)

    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return (
            f"Remaining - Food: {self.food}, "
            f"Water: {self.water}, "
            f"Medicine: {self.medicine}, "
            f"Blankets: {self.blankets}"
        )

