//this main file is for testing purpose
#include "priority_calculator.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int numberOfAreas;

    cout << "Enter number of disaster areas: ";
    cin >> numberOfAreas;

    // Validate number of areas
    if (numberOfAreas <= 0)
    {
        cout << "Invalid number of areas." << endl;
        return 1;
    }

    vector<DisasterArea> areas;

    for (int i = 0; i < numberOfAreas; i++)
    {
        DisasterArea area;

        cout << "\nEnter details for Area " << i + 1 << endl;

        cout << "Area name: ";
        cin >> area.areaName;

        cout << "Severity (1-10): ";
        cin >> area.severity;

        if (area.severity < 1 || area.severity > 10)
        {
            cout << "Invalid severity. Enter a value from 1 to 10." << endl;
            return 1;
        }


        cout << "Population affected: ";
        cin >> area.populationAffected;

        if (area.populationAffected <= 0)
        {
            cout << "Population must be greater than 0." << endl;
            return 1;
        }


        cout << "Medical need (1-10): ";
        cin >> area.medicalNeed;

        if (area.medicalNeed < 1 || area.medicalNeed > 10)
        {
            cout << "Invalid medical need. Enter a value from 1 to 10." << endl;
            return 1;
        }


        cout << "Waiting time (hours): ";
        cin >> area.waitingTime;

        if (area.waitingTime < 0)
        {
            cout << "Waiting time cannot be negative." << endl;
            return 1;
        }


        cout << "Resource demand: ";
        cin >> area.resourceDemand;

        if (area.resourceDemand <= 0)
        {
            cout << "Resource demand must be greater than 0." << endl;
            return 1;
        }


        // Initially no score
        area.priorityScore = 0;
        area.priorityLevel = "Not Calculated";

        areas.push_back(area);
    }


    // Calculate priority
    calculateAllPriorities(areas);

    // Display results
    displayPriorities(areas);

    return 0;
}