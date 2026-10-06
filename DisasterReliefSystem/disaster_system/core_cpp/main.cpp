#include "priority_calculator.h"
#include "sorting_searching.h"
#include "resource_allocator.h"
#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>

using namespace std;


// INPUT VALIDATION
bool readInt(
    const string& prompt, int& value, int minimum
)
{
    cout << prompt;

    if (!(cin >> value) || value < minimum)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input." << endl;
        return false;
    }
    return true;
}

bool readDouble(
    const string& prompt, double& value,double minimum, double maximum
)
{
    cout << prompt;

    if (!(cin >> value) || value < minimum || value > maximum)
    {
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input." << endl;
        return false;
    }
    return true;
}

// MAIN
int main()
{
    int numberOfAreas;

    // INPUT NUMBER OF AREAS
    if (!readInt(
            "Enter number of disaster areas: ", numberOfAreas, 1))
    {
        return 1;
    }

    vector<DisasterArea> areas;
    areas.reserve(numberOfAreas);

    // INPUT DISASTER AREAS
    for (int i = 0; i < numberOfAreas; i++)
    {
        DisasterArea area{};
        cout << "\nEnter details for Area "
             << i + 1 << endl;

        cout << "Area name: ";
        cin >> area.areaName;

        // Unique area names
        if (searchAreaByName( areas, area.areaName) != -1)
        {
            cout << "Area name must be unique." << endl;
            return 1;
        }

        if (!readDouble( "Severity (1-10): ", area.severity, 1.0, 10.0))
        {
            return 1;
        }


        if (!readInt( "Population affected: ", area.populationAffected, 1))
        {
            return 1;
        }

        if (!readDouble( "Medical need (1-10): ", area.medicalNeed, 1.0, 10.0))
        {
            return 1;
        }

        if (!readDouble( "Waiting time (hours): ", area.waitingTime, 0.0,
                numeric_limits<double>::max()))
        {
            return 1;
        }

        if (!readInt( "Resource demand: ", area.resourceDemand, 1))
        {
            return 1;
        }

        area.priorityScore = 0.0;

        area.priorityLevel = "Not Calculated";

        areas.push_back(area);
    }


    // CALCULATE PRIORITY
    calculateAllPriorities(areas);

    displayPriorities(areas);


    // CREATE PRIORITY QUEUE
    PriorityQueueManager priorityManager;

    for (const DisasterArea& area : areas)
    {
        priorityManager.addArea(area);
    }

    priorityManager.displayProcessingOrder();


    // SEARCH
    string searchName;

    cout << "\nEnter area name to search: ";

    cin >> searchName;

    int searchIndex =
        searchAreaByName( areas, searchName);


    if (searchIndex != -1)
    {
        const DisasterArea& area = areas[searchIndex];

        cout << "\nSEARCH RESULT :\n";

        cout << "Area Name: " << area.areaName
             << endl;

        cout << "Priority Score: " << area.priorityScore
             << endl;

        cout << "Priority Level: " << area.priorityLevel
             << endl;

        cout << "Waiting Time: " << area.waitingTime << " hours"
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
    AvailableResources available{};

    cout << "\nAVAILABLE RESOURCES :\n";

    if (!readInt( "Food: ", available.food, 0))
    {
        return 1;
    }


    if (!readInt( "Water: ", available.water, 0))
    {
        return 1;
    }


    if (!readInt( "Medicine: ", available.medicine, 0))
    {
        return 1;
    }


    if (!readInt( "Blankets: ", available.blankets, 0))
    {
        return 1;
    }


    // RESOURCE DEMANDS
    unordered_map<string, ResourceRequest> requestByArea;


    for (const DisasterArea& area : areas)
    {
        ResourceRequest request{};

        request.areaName = area.areaName;

        request.priorityScore = area.priorityScore;

        request.waitingTime = area.waitingTime;

        request.priorityLevel = area.priorityLevel;

        cout << "\nRESOURCE DEMAND :\n";

        cout << "Area: " << area.areaName
             << endl;

        if (!readInt( "Food demand: ", request.foodDemand, 0))
        {
            return 1;
        }

        if (!readInt( "Water demand: ", request.waterDemand, 0))
        {
            return 1;
        }

        if (!readInt( "Medicine demand: ", request.medicineDemand, 0))
        {
            return 1;
        }

        if (!readInt( "Blanket demand: ", request.blanketDemand, 0))
        {
            return 1;
        }

        requestByArea[request.areaName] = request;
    }


    // ACTUAL PRIORITY-QUEUE PROCESSING
    // Rebuild queue because the sorted vector was changed during reporting.
    PriorityQueueManager processingQueue;

    for (const DisasterArea& area : areas)
    {
        processingQueue.addArea(area);
    }


    vector<ResourceRequest> orderedRequests;

    orderedRequests.reserve(areas.size());

    cout << "\nINTEGRATED PROCESSING ORDER :\n";

    int rank = 1;


    while (!processingQueue.isEmpty())
    {
        DisasterArea area =
            processingQueue.getNextArea();


        cout << rank++ << ". "
             << area.areaName
             << " | Priority: "
             << area.priorityScore
             << " | Level: "
             << area.priorityLevel
             << endl;


        orderedRequests.push_back(
            requestByArea.at(
                area.areaName
            )
        );
    }


    // RESOURCE ALLOCATION
    ResourceAllocator allocator(available);

    vector<AllocationRecord>
        allocationRecords = allocator.allocateResources(orderedRequests);


    // FINAL REPORT
    allocator.displayAllocationReport(allocationRecords);

    allocator.displayRemainingResources();

    cout << "\nFINAL REPORT GENERATED SUCCESSFULLY."
         << endl;

    return 0;
}