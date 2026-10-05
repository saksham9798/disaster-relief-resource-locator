#include "resource_allocator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;


// Constructor
ResourceAllocator::ResourceAllocator(
    const AvailableResources& resources
) : available(resources){}


// Resource allocation
vector<AllocationRecord>ResourceAllocator::allocateResources(
    const vector<ResourceRequest>& requests
)
{
    vector<AllocationRecord> records;

    records.reserve(requests.size());

    // Process areas one by one
    for (const ResourceRequest& request : requests)
    {
        AllocationRecord record{};

        record.areaName = request.areaName;
        record.priorityScore = request.priorityScore;
        record.priorityLevel = request.priorityLevel;


        // Store original demand
        record.foodDemand = request.foodDemand;
        record.waterDemand = request.waterDemand;
        record.medicineDemand = request.medicineDemand;
        record.blanketDemand = request.blanketDemand;


        // Allocate Food
        record.foodAllocated =
            min(request.foodDemand, available.food);

        available.food -= record.foodAllocated;

        record.foodUnmet =
            request.foodDemand - record.foodAllocated;

        // Allocate Water
        record.waterAllocated =
            min(request.waterDemand, available.water);

        available.water -= record.waterAllocated;

        record.waterUnmet =
            request.waterDemand - record.waterAllocated;


        // Allocate Medicine
        record.medicineAllocated =
            min(request.medicineDemand, available.medicine);

        available.medicine -= record.medicineAllocated;

        record.medicineUnmet =
            request.medicineDemand - record.medicineAllocated;


        // Allocate Blankets
        record.blanketAllocated =
            min(request.blanketDemand, available.blankets);

        available.blankets -= record.blanketAllocated;

        record.blanketUnmet =
            request.blanketDemand - record.blanketAllocated;


        // Store allocation result
        records.push_back(record);
    }

    return records;
}


// Get remaining resources
RemainingResources
ResourceAllocator::getRemainingResources() const
{
    RemainingResources remaining;

    remaining.food = available.food;
    remaining.water = available.water;
    remaining.medicine = available.medicine;
    remaining.blankets = available.blankets;

    return remaining;
}


// Display allocation report
void ResourceAllocator::displayAllocationReport(
    const vector<AllocationRecord>& records
) const

{    cout << "\nRESOURCE ALLOCATION REPORT\n";

    cout << fixed << setprecision(2);

    for (int i = 0;
         i < static_cast<int>(records.size());
         i++)
    {
        const AllocationRecord& record = records[i];

        cout << "\nRank: " << i + 1 << endl;
        cout << "Area: " << record.areaName << endl;
        cout << "Priority Score: "
             << record.priorityScore << endl;
        cout << "Priority Level: "
             << record.priorityLevel << endl;

        cout << "\nFood"
             << " | Demand: " << record.foodDemand
             << " | Allocated: " << record.foodAllocated
             << " | Unmet: " << record.foodUnmet
             << endl;

        cout << "Water"
             << " | Demand: " << record.waterDemand
             << " | Allocated: " << record.waterAllocated
             << " | Unmet: " << record.waterUnmet
             << endl;

        cout << "Medicine"
             << " | Demand: " << record.medicineDemand
             << " | Allocated: " << record.medicineAllocated
             << " | Unmet: " << record.medicineUnmet
             << endl;

        cout << "Blankets"
             << " | Demand: " << record.blanketDemand
             << " | Allocated: " << record.blanketAllocated
             << " | Unmet: " << record.blanketUnmet
             << endl;
    }
}


// Display remaining resources
void ResourceAllocator::displayRemainingResources() const
{   cout << "\nREMAINING RESOURCES :\n";

    cout << "Food      : " << available.food << endl;
    cout << "Water     : " << available.water << endl;
    cout << "Medicine  : " << available.medicine << endl;
    cout << "Blankets  : " << available.blankets << endl;
}