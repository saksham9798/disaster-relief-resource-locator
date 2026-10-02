#ifndef SORTING_SEARCHING_H
#define SORTING_SEARCHING_H

#include "priority_calculator.h"
#include <vector>
#include <queue>
#include <string>

using namespace std;

// PRIORITY QUEUE COMPARATOR

struct PriorityComparator
{
    bool operator()(
        const DisasterArea& first,
        const DisasterArea& second
    ) const;
};

// PRIORITY QUEUE MANAGER

class PriorityQueueManager
{
private:

    priority_queue<
        DisasterArea,
        vector<DisasterArea>,
        PriorityComparator
    > priorityQueue;

public:

    void addArea(const DisasterArea& area);

    bool isEmpty() const;

    DisasterArea getNextArea();

    void displayProcessingOrder();
};

// SEARCHING

int searchAreaByName(
    const vector<DisasterArea>& areas,
    const string& areaName
);

// SORTING

void sortAreasByPriority(
    vector<DisasterArea>& areas
);

void displaySortedReport(
    const vector<DisasterArea>& areas
);

#endif