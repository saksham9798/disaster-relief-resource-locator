from django.contrib import admin

from .models import (
    DisasterArea,
    AvailableResources,
    ResourceRequest,
    AllocationRecord,
    RemainingResources,
)


@admin.register(DisasterArea)
class DisasterAreaAdmin(admin.ModelAdmin):

    list_display = (
        "areaName",
        "severity",
        "populationAffected",
        "medicalNeed",
        "waitingTime",
        "resourceDemand",
        "priorityScore",
        "priorityLevel",
    )

    list_filter = (
        "priorityLevel",
    )

    search_fields = (
        "areaName",
    )

    ordering = (
        "-priorityScore",
    )


@admin.register(AvailableResources)
class AvailableResourcesAdmin(admin.ModelAdmin):

    list_display = (
        "food",
        "water",
        "medicine",
        "blankets",
    )

    ordering = (
        "-id",
    )


@admin.register(ResourceRequest)
class ResourceRequestAdmin(admin.ModelAdmin):

    list_display = (
        "area",
        "foodDemand",
        "waterDemand",
        "medicineDemand",
        "blanketDemand",
    )

    list_filter = (
        "area",
    )

    search_fields = (
        "area__areaName",
    )

    ordering = (
        "-area__priorityScore",
    )


@admin.register(AllocationRecord)
class AllocationRecordAdmin(admin.ModelAdmin):

    list_display = (
        "area",
        "priorityScore",
        "priorityLevel",
        "foodAllocated",
        "waterAllocated",
        "medicineAllocated",
        "blanketAllocated",
    )

    list_filter = (
        "priorityLevel",
    )

    search_fields = (
        "area__areaName",
    )

    ordering = (
        "-priorityScore",
    )


@admin.register(RemainingResources)
class RemainingResourcesAdmin(admin.ModelAdmin):

    list_display = (
        "food",
        "water",
        "medicine",
        "blankets",
        "created_at",
    )

    ordering = (
        "-created_at",
    )