#include "sorting_searching.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;


// PRIORITY QUEUE
// Comparator determines which area gets higher priority.
bool PriorityComparator::operator()(
    const DisasterArea& first,
    const DisasterArea& second
) const
{
    // Rule 1:
    // Higher priority score comes first.
    if (first.priorityScore != second.priorityScore)
    {
        return first.priorityScore < second.priorityScore;
    }

    // Rule 2:
    // If priority is equal, longer waiting time comes first.
    if (first.waitingTime != second.waitingTime)
    {
        return first.waitingTime < second.waitingTime;
    }

    // Rule 3:
    // If both are equal, use alphabetical order.
    return first.areaName > second.areaName;
}

// Add an area to the priority queue.
void PriorityQueueManager::addArea(
    const DisasterArea& area
)
{
    priorityQueue.push(area);
}

// Check whether the queue is empty.
bool PriorityQueueManager::isEmpty() const
{
    return priorityQueue.empty();
}

// Remove and return the highest-priority area.
DisasterArea PriorityQueueManager::getNextArea()
{
    if (priorityQueue.empty())
    {
        return DisasterArea{};
    }

    DisasterArea nextArea = priorityQueue.top();

    priorityQueue.pop();

    return nextArea;
}

// Display areas in processing order.
void PriorityQueueManager::displayProcessingOrder() const
{
    cout << "\nPRIORITY QUEUE PROCESSING :\n";

    // Copy queue so original queue is not destroyed.
    priority_queue< DisasterArea, vector<DisasterArea>,
        PriorityComparator
    > tempQueue = priorityQueue;

    int position = 1;

    cout << fixed << setprecision(2);

    while (!tempQueue.empty())
    {
        const DisasterArea& area = tempQueue.top();

        cout << position++ << ". "
             << area.areaName
             << " | Priority: "
             << area.priorityScore
             << " | Waiting: "
             << area.waitingTime
             << " hours"
             << " | Level: "
             << area.priorityLevel
             << endl;
        tempQueue.pop();
    }
}

// Linear search by area name.
int searchAreaByName(
    const vector<DisasterArea>& areas,
    const string& areaName
)
{
    for (int i = 0; i < static_cast<int>(areas.size()); i++)
    {
        if (areas[i].areaName == areaName)
        {
            return i;
        }
    }

    return -1;
}

// Sort areas by priority.
void sortAreasByPriority(
    vector<DisasterArea>& areas
)
{
    sort(
        areas.begin(),
        areas.end(),

        [](const DisasterArea& first,
           const DisasterArea& second)
        {
            // Rule 1:
            // Higher priority first.
            if (first.priorityScore != second.priorityScore)
            {
                return first.priorityScore > second.priorityScore;
            }

            // Rule 2:
            // Equal priority -> longer waiting time first.
            if (first.waitingTime != second.waitingTime)
            {
                return first.waitingTime > second.waitingTime;
            }

            // Rule 3:
            // Equal priority and waiting time ->
            // alphabetical order.
            return first.areaName < second.areaName;
        }
    );
}


// Display sorted priority report.
void displaySortedReport(
    const vector<DisasterArea>& areas
)
{
    cout << "\nSORTED PRIORITY REPORT :\n";

    cout << left
         << setw(6) << "Rank"
         << setw(18) << "Area"
         << setw(12) << "Priority"
         << setw(15) << "Waiting"
         << setw(12) << "Level"
         << endl;


    cout << fixed << setprecision(2);

    for (int i = 0; i < static_cast<int>(areas.size()); i++)
    {
        cout << left
             << setw(6) << i + 1
             << setw(18) << areas[i].areaName
             << setw(12) << areas[i].priorityScore
             << setw(15) << areas[i].waitingTime
             << setw(12) << areas[i].priorityLevel
             << endl;
    }

}