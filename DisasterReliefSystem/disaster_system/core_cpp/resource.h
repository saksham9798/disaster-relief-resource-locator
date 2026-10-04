#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

using namespace std;

// Available resources in the system
struct AvailableResources
{
    int food;
    int water;
    int medicine;
    int blankets;
};


// Resource requirement of one disaster area
struct ResourceRequest
{
    string areaName;

    double priorityScore;
    double waitingTime;
    string priorityLevel;

    int foodDemand;
    int waterDemand;
    int medicineDemand;
    int blanketDemand;
};


// Result of resource allocation for one area
struct AllocationRecord
{
    string areaName;

    double priorityScore;
    string priorityLevel;

    // Original demand
    int foodDemand;
    int waterDemand;
    int medicineDemand;
    int blanketDemand;

    // Allocated resources
    int foodAllocated;
    int waterAllocated;
    int medicineAllocated;
    int blanketAllocated;

    // Remaining / unmet demand
    int foodUnmet;
    int waterUnmet;
    int medicineUnmet;
    int blanketUnmet;
};


// Final resources remaining after allocation
struct RemainingResources
{
    int food;
    int water;
    int medicine;
    int blankets;
};

#endif