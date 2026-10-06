#include "priority_calculator.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    int numberOfAreas;

    if (!(cin >> numberOfAreas))
    {
        return 1;
    }

    cin.ignore();

    vector<DisasterArea> areas;

    for (int i = 0; i < numberOfAreas; i++)
    {
        string line;

        if (!getline(cin, line))
        {
            return 1;
        }

        stringstream ss(line);

        DisasterArea area;

        string severity;
        string population;
        string medicalNeed;
        string waitingTime;
        string resourceDemand;

        getline(ss, area.areaName, '\t');
        getline(ss, severity, '\t');
        getline(ss, population, '\t');
        getline(ss, medicalNeed, '\t');
        getline(ss, waitingTime, '\t');
        getline(ss, resourceDemand, '\t');

        try
        {
            area.severity = stod(severity);
            area.populationAffected = stoi(population);
            area.medicalNeed = stod(medicalNeed);
            area.waitingTime = stod(waitingTime);
            area.resourceDemand = stoi(resourceDemand);

            area.priorityScore = 0.0;
            area.priorityLevel = "Not Calculated";
        }
        catch (...)
        {
            return 1;
        }

        areas.push_back(area);
    }

    // Use the actual C++ priority algorithm.
    calculateAllPriorities(areas);

    // Return results in a simple format:
    // index | score | level

    for (int i = 0; i < static_cast<int>(areas.size()); i++)
    {
        cout << i
             << "|"
             << areas[i].priorityScore
             << "|"
             << areas[i].priorityLevel
             << endl;
    }

    return 0;
}