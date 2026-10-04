#ifndef RESOURCE_ALLOCATOR_H
#define RESOURCE_ALLOCATOR_H

#include "resource.h"

#include <vector>

using namespace std;

class ResourceAllocator
{
private:
    AvailableResources available;

public:

    ResourceAllocator(
        const AvailableResources& resources
    );

    vector<AllocationRecord> allocateResources(
        vector<ResourceRequest> requests
    );

    RemainingResources getRemainingResources() const;

    void displayAllocationReport(
        const vector<AllocationRecord>& records
    ) const;

    void displayRemainingResources() const;
};

#endif