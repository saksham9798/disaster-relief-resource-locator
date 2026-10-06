from django import forms

from .models import (
    DisasterArea,
    AvailableResources,
    ResourceRequest,
)


# =====================================================
# DISASTER AREA FORM
# =====================================================

class DisasterAreaForm(forms.ModelForm):

    class Meta:
        model = DisasterArea

        fields = [
            "areaName",
            "severity",
            "populationAffected",
            "medicalNeed",
            "waitingTime",
            "resourceDemand",
        ]

        labels = {
            "areaName": "Disaster Area Name",
            "severity": "Severity (1-10)",
            "populationAffected": "Population Affected",
            "medicalNeed": "Medical Need (1-10)",
            "waitingTime": "Waiting Time",
            "resourceDemand": "Resource Demand",
        }

        widgets = {

            "areaName": forms.TextInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter disaster area name",
                }
            ),

            "severity": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "1-10",
                    "min": "1",
                    "max": "10",
                    "step": "0.1",
                }
            ),

            "populationAffected": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter affected population",
                    "min": "0",
                }
            ),

            "medicalNeed": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "1-10",
                    "min": "1",
                    "max": "10",
                    "step": "0.1",
                }
            ),

            "waitingTime": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter waiting time",
                    "min": "0",
                    "step": "0.1",
                }
            ),

            "resourceDemand": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter resource demand",
                    "min": "0",
                }
            ),
        }


# =====================================================
# AVAILABLE RESOURCES FORM
# =====================================================

class AvailableResourcesForm(forms.ModelForm):

    class Meta:
        model = AvailableResources

        fields = [
            "food",
            "water",
            "medicine",
            "blankets",
        ]

        labels = {
            "food": "Available Food",
            "water": "Available Water",
            "medicine": "Available Medicine",
            "blankets": "Available Blankets",
        }

        widgets = {

            "food": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter available food",
                    "min": "0",
                }
            ),

            "water": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter available water",
                    "min": "0",
                }
            ),

            "medicine": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter available medicine",
                    "min": "0",
                }
            ),

            "blankets": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter available blankets",
                    "min": "0",
                }
            ),
        }


# =====================================================
# RELIEF REQUEST FORM
# =====================================================

class ResourceRequestForm(forms.ModelForm):

    class Meta:
        model = ResourceRequest

        fields = [
            "area",
            "foodDemand",
            "waterDemand",
            "medicineDemand",
            "blanketDemand",
        ]

        labels = {
            "area": "Disaster Area",
            "foodDemand": "Food Required",
            "waterDemand": "Water Required",
            "medicineDemand": "Medicine Required",
            "blanketDemand": "Blankets Required",
        }

        widgets = {

            "area": forms.Select(
                attrs={
                    "class": "form-input",
                }
            ),

            "foodDemand": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter food requirement",
                    "min": "0",
                }
            ),

            "waterDemand": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter water requirement",
                    "min": "0",
                }
            ),

            "medicineDemand": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter medicine requirement",
                    "min": "0",
                }
            ),

            "blanketDemand": forms.NumberInput(
                attrs={
                    "class": "form-input",
                    "placeholder": "Enter blanket requirement",
                    "min": "0",
                }
            ),
        }