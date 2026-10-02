#ifndef PRIORITY_CALCULATOR_H
#define PRIORITY_CALCULATOR_H

#include <string>
#include <vector>

using namespace std;

struct DisasterArea
{
    string areaName;

    double severity;
    int populationAffected;
    double medicalNeed;
    double waitingTime;
    int resourceDemand;

    double priorityScore;
    string priorityLevel;
};

double normalizeScale(double value, double maximumValue);

double calculatePriority(
    double severity,
    int populationAffected,
    double medicalNeed,
    double waitingTime,
    int resourceDemand,
    int maximumPopulation,
    double maximumWaitingTime,
    int maximumResourceDemand
);

string getPriorityLevel(double priorityScore);

void calculateAllPriorities(vector<DisasterArea>& areas);

void displayPriorities(const vector<DisasterArea>& areas);

#endif