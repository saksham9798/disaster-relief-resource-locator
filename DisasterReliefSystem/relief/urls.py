from django.urls import path

from . import views


urlpatterns = [

    # =====================================================
    # DASHBOARD
    # =====================================================

    path(
        "",
        views.dashboard,
        name="dashboard"
    ),


    # =====================================================
    # DISASTER AREAS
    # =====================================================

    path(
        "areas/",
        views.areas,
        name="areas"
    ),

    path(
        "areas/add/",
        views.add_area,
        name="add_area"
    ),

    path(
        "areas/edit/<int:area_id>/",
        views.edit_area,
        name="edit_area"
    ),

    path(
        "areas/delete/<int:area_id>/",
        views.delete_area,
        name="delete_area"
    ),


    # =====================================================
    # RESOURCES
    # =====================================================

    path(
        "resources/",
        views.resources,
        name="resources"
    ),

    path(
        "resources/add/",
        views.add_resources,
        name="add_resources"
    ),

    path(
        "resources/edit/<int:resource_id>/",
        views.edit_resources,
        name="edit_resources"
    ),

    path(
        "resources/delete/<int:resource_id>/",
        views.delete_resources,
        name="delete_resources"
    ),


    # =====================================================
    # RELIEF REQUESTS
    # =====================================================

    path(
        "requests/",
        views.relief_requests,
        name="requests"
    ),

    path(
        "requests/add/",
        views.add_request,
        name="add_request"
    ),


    # =====================================================
    # RESOURCE ALLOCATION
    # =====================================================

    path(
        "allocation/",
        views.allocation,
        name="allocation"
    ),


    # =====================================================
    # ANALYTICS
    # =====================================================

    path(
        "analytics/",
        views.analytics,
        name="analytics"
    ),
]