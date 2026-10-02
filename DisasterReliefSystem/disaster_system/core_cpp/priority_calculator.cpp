#include "priority_calculator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Normalize a value to the range 0-100
double normalizeScale(double value, double maximumValue)
{
    if (maximumValue <= 0)
    {
        return 0;
    }

    return (value / maximumValue) * 100;
}


// Calculate priority score for one disaster area
double calculatePriority(
    double severity,
    int populationAffected,
    double medicalNeed,
    double waitingTime,
    int resourceDemand,
    int maximumPopulation,
    double maximumWaitingTime,
    int maximumResourceDemand
)
{
    // Normalize severity and medical need
    double normalizedSeverity = (severity / 10.0) * 100;
    double normalizedMedicalNeed = (medicalNeed / 10.0) * 100;

    // Normalize remaining factors
    double normalizedPopulation =
        normalizeScale(populationAffected, maximumPopulation);

    double normalizedWaitingTime =
        normalizeScale(waitingTime, maximumWaitingTime);

    double normalizedResourceDemand =
        normalizeScale(resourceDemand, maximumResourceDemand);


    // Apply weights
    double priorityScore =
        (normalizedSeverity * 0.30) +
        (normalizedPopulation * 0.25) +
        (normalizedMedicalNeed * 0.20) +
        (normalizedWaitingTime * 0.15) +
        (normalizedResourceDemand * 0.10);


    return priorityScore;
}


// Determine priority category
string getPriorityLevel(double priorityScore)
{
    if (priorityScore >= 80)
    {
        return "Critical";
    }
    else if (priorityScore >= 60)
    {
        return "High";
    }
    else if (priorityScore >= 40)
    {
        return "Medium";
    }
    else
    {
        return "Low";
    }
}


// Calculate priority for all disaster areas
void calculateAllPriorities(vector<DisasterArea>& areas)
{
    if (areas.empty())
    {
        return;
    }

    int maximumPopulation = 0;
    double maximumWaitingTime = 0;
    int maximumResourceDemand = 0;


    // Find maximum values
    for (const DisasterArea& area : areas)
    {
        maximumPopulation =
            max(maximumPopulation, area.populationAffected);

        maximumWaitingTime =
            max(maximumWaitingTime, area.waitingTime);

        maximumResourceDemand =
            max(maximumResourceDemand, area.resourceDemand);
    }


    // Calculate priority for each area
    for (DisasterArea& area : areas)
    {
        area.priorityScore = calculatePriority(
            area.severity,
            area.populationAffected,
            area.medicalNeed,
            area.waitingTime,
            area.resourceDemand,
            maximumPopulation,
            maximumWaitingTime,
            maximumResourceDemand
        );

        area.priorityLevel =
            getPriorityLevel(area.priorityScore);
    }
}


// Display priority results
void displayPriorities(const vector<DisasterArea>& areas)
{
    cout << "\nPRIORITY RESULTS : \n";

    cout << fixed << setprecision(2);

    for (const DisasterArea& area : areas)
    {
        cout << "\nArea: " << area.areaName << endl;
        cout << "Priority Score: " << area.priorityScore << "/100" << endl;
        cout << "Priority Level: " << area.priorityLevel << endl;
    }

}