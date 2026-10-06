from django.shortcuts import render, redirect, get_object_or_404

from .models import (
    DisasterArea,
    AvailableResources,
    ResourceRequest,
    AllocationRecord,
)

from .forms import (
    DisasterAreaForm,
    AvailableResourcesForm,
    ResourceRequestForm,
)

from .priority_service import calculate_all_priorities


# =====================================================
# DASHBOARD
# =====================================================

def dashboard(request):

    areas = DisasterArea.objects.all().order_by(
        "-priorityScore"
    )

    resource_requests = ResourceRequest.objects.all()

    allocations = AllocationRecord.objects.all()

    context = {
        "areas": areas,

        "resource_requests": resource_requests,

        "allocations": allocations,

        "total_areas":
            DisasterArea.objects.count(),

        "total_requests":
            ResourceRequest.objects.count(),

        "total_allocations":
            AllocationRecord.objects.count(),

        "critical_areas":
            DisasterArea.objects.filter(
                priorityLevel="Critical"
            ).count(),

        "high_priority_areas":
            DisasterArea.objects.filter(
                priorityLevel="High"
            ).count(),
    }

    return render(
        request,
        "relief/dashboard.html",
        context
    )


# =====================================================
# DISASTER AREAS
# =====================================================

def areas(request):

    area_list = DisasterArea.objects.all().order_by(
        "-priorityScore"
    )

    return render(
        request,
        "relief/areas.html",
        {
            "areas": area_list
        }
    )


# =====================================================
# ADD DISASTER AREA
# =====================================================

def add_area(request):

    if request.method == "POST":

        form = DisasterAreaForm(request.POST)

        if form.is_valid():

            form.save()

            # Recalculate priority scores
            # for all disaster areas.
            calculate_all_priorities()

            return redirect("areas")

    else:

        form = DisasterAreaForm()

    return render(
        request,
        "relief/add_area.html",
        {
            "form": form,
            "edit_mode": False
        }
    )


# =====================================================
# EDIT DISASTER AREA
# =====================================================

def edit_area(request, area_id):

    area = get_object_or_404(
        DisasterArea,
        id=area_id
    )

    if request.method == "POST":

        form = DisasterAreaForm(
            request.POST,
            instance=area
        )

        if form.is_valid():

            form.save()

            # Recalculate priority scores
            # because area information changed.
            calculate_all_priorities()

            return redirect("areas")

    else:

        form = DisasterAreaForm(
            instance=area
        )

    return render(
        request,
        "relief/add_area.html",
        {
            "form": form,
            "edit_mode": True
        }
    )


# =====================================================
# DELETE DISASTER AREA
# =====================================================

def delete_area(request, area_id):

    if request.method == "POST":

        area = get_object_or_404(
            DisasterArea,
            id=area_id
        )

        area.delete()

        # Recalculate priority scores
        # for remaining disaster areas.
        calculate_all_priorities()

    return redirect("areas")


# =====================================================
# RESOURCES
# =====================================================

def resources(request):

    available_resources = AvailableResources.objects.all()

    return render(
        request,
        "relief/resources.html",
        {
            "resources": available_resources
        }
    )


# =====================================================
# ADD AVAILABLE RESOURCES
# =====================================================

def add_resources(request):

    if request.method == "POST":

        form = AvailableResourcesForm(request.POST)

        if form.is_valid():

            form.save()

            return redirect("resources")

    else:

        form = AvailableResourcesForm()

    return render(
        request,
        "relief/add_resources.html",
        {
            "form": form,
            "edit_mode": False
        }
    )


# =====================================================
# EDIT RESOURCE STOCK
# =====================================================

def edit_resources(request, resource_id):

    resource = get_object_or_404(
        AvailableResources,
        id=resource_id
    )

    if request.method == "POST":

        form = AvailableResourcesForm(
            request.POST,
            instance=resource
        )

        if form.is_valid():

            form.save()

            return redirect("resources")

    else:

        form = AvailableResourcesForm(
            instance=resource
        )

    return render(
        request,
        "relief/add_resources.html",
        {
            "form": form,
            "edit_mode": True
        }
    )


# =====================================================
# DELETE RESOURCE STOCK
# =====================================================

def delete_resources(request, resource_id):

    if request.method == "POST":

        resource = get_object_or_404(
            AvailableResources,
            id=resource_id
        )

        resource.delete()

    return redirect("resources")


# =====================================================
# RELIEF REQUESTS
# =====================================================

def relief_requests(request):

    request_list = ResourceRequest.objects.select_related(
        "area"
    ).order_by(
        "-area__priorityScore"
    )

    return render(
        request,
        "relief/requests.html",
        {
            "resource_requests": request_list
        }
    )


# =====================================================
# ADD RELIEF REQUEST
# =====================================================

def add_request(request):

    if request.method == "POST":

        form = ResourceRequestForm(request.POST)

        if form.is_valid():

            form.save()

            return redirect("requests")

    else:

        form = ResourceRequestForm()

    return render(
        request,
        "relief/add_request.html",
        {
            "form": form
        }
    )


# =====================================================
# RESOURCE ALLOCATION
# =====================================================

def allocation(request):

    allocation_records = AllocationRecord.objects.select_related(
        "area"
    ).order_by(
        "-priorityScore"
    )

    return render(
        request,
        "relief/allocation.html",
        {
            "allocations": allocation_records
        }
    )


# =====================================================
# ANALYTICS
# =====================================================

def analytics(request):

    total_areas = DisasterArea.objects.count()

    context = {

        "total_areas":
            total_areas,

        "critical_count":
            DisasterArea.objects.filter(
                priorityLevel="Critical"
            ).count(),

        "high_count":
            DisasterArea.objects.filter(
                priorityLevel="High"
            ).count(),

        "medium_count":
            DisasterArea.objects.filter(
                priorityLevel="Medium"
            ).count(),

        "low_count":
            DisasterArea.objects.filter(
                priorityLevel="Low"
            ).count(),

        "total_requests":
            ResourceRequest.objects.count(),

        "total_allocations":
            AllocationRecord.objects.count(),
    }

    return render(
        request,
        "relief/analytics.html",
        context
    )