//this main file is for testing purpose
#include "priority_calculator.h"
#include "sorting_searching.h"
#include "resource_allocator.h"
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

    // Input Disaster Aera Data
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

    // PRIORITY QUEUE
    PriorityQueueManager priorityManager;

    // Insert all disaster areas into priority queue.
    for (const DisasterArea& area : areas)
    {
        priorityManager.addArea(area);
    }

    // Display processing order.
    priorityManager.displayProcessingOrder();

    // SEARCHING
    string searchName;

    cout << "\nEnter area name to search: ";
    cin >> searchName;

    int searchIndex = searchAreaByName(areas, searchName);

    if (searchIndex != -1)
    {
        cout << "\nSEARCH RESULT :\n";

        cout << "Area Name: "
             << areas[searchIndex].areaName
             << endl;

        cout << "Priority Score: "
             << areas[searchIndex].priorityScore
             << endl;

        cout << "Priority Level: "
             << areas[searchIndex].priorityLevel
             << endl;

        cout << "Waiting Time: "
             << areas[searchIndex].waitingTime
             << " hours"
             << endl;

    }
    else
    {
        cout << "\nArea not found." << endl;
    }


    // SORTING
    sortAreasByPriority(areas);

    displaySortedReport(areas);

    // AVAILABLE RESOURCES
    AvailableResources available;

    cout << "\nAVAILABLE RESOURCES :\n";

    cout << "Food: ";
    cin >> available.food;

    if (available.food < 0)
    {
        cout << "Food cannot be negative." << endl;
        return 1;
    }


    cout << "Water: ";
    cin >> available.water;

    if (available.water < 0)
    {
        cout << "Water cannot be negative." << endl;
        return 1;
    }


    cout << "Medicine: ";
    cin >> available.medicine;

    if (available.medicine < 0)
    {
        cout << "Medicine cannot be negative." << endl;
        return 1;
    }


    cout << "Blankets: ";
    cin >> available.blankets;

    if (available.blankets < 0)
    {
        cout << "Blankets cannot be negative." << endl;
        return 1;
    }


    // RESOURCE REQUIREMENTS
    vector<ResourceRequest> requests;

    for (const DisasterArea& area : areas)
    {
        ResourceRequest request;

        request.areaName = area.areaName;
        request.priorityScore = area.priorityScore;
        request.waitingTime = area.waitingTime;
        request.priorityLevel = area.priorityLevel;


        cout << "\nRESOURCE DEMAND :\n";

        cout << "Area: "
             << area.areaName
             << endl;


        cout << "Food demand: ";
        cin >> request.foodDemand;

        if (request.foodDemand < 0)
        {
            cout << "Food demand cannot be negative."
                 << endl;
            return 1;
        }


        cout << "Water demand: ";
        cin >> request.waterDemand;

        if (request.waterDemand < 0)
        {
            cout << "Water demand cannot be negative."
                 << endl;
            return 1;
        }


        cout << "Medicine demand: ";
        cin >> request.medicineDemand;

        if (request.medicineDemand < 0)
        {
            cout << "Medicine demand cannot be negative."
                 << endl;
            return 1;
        }


        cout << "Blanket demand: ";
        cin >> request.blanketDemand;

        if (request.blanketDemand < 0)
        {
            cout << "Blanket demand cannot be negative."
                 << endl;
            return 1;
        }


        requests.push_back(request);
    }


    // RESOURCE ALLOCATION
    ResourceAllocator allocator(available);

    vector<AllocationRecord> allocationRecords =
        allocator.allocateResources(requests);


    // FINAL REPORT
    allocator.displayAllocationReport(
        allocationRecords
    );

    allocator.displayRemainingResources();

    return 0;
}