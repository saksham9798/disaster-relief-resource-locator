#include "resource_allocator.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Django -> C++ Resource Allocation Bridge

    INPUT FORMAT:

    Line 1:
    food water medicine blankets

    Line 2:
    number_of_requests

    Following lines:
    areaName|priorityScore|priorityLevel|waitingTime|
    foodDemand|waterDemand|medicineDemand|blanketDemand

    OUTPUT FORMAT:

    One allocation record per line:

    index|areaName|priorityScore|priorityLevel|
    foodDemand|foodAllocated|foodUnmet|
    waterDemand|waterAllocated|waterUnmet|
    medicineDemand|medicineAllocated|medicineUnmet|
    blanketDemand|blanketAllocated|blanketUnmet

    Final line:

    REMAINING|food|water|medicine|blankets
*/


// --------------------------------------------------
// Split string using delimiter
// --------------------------------------------------

vector<string> split(const string& text, char delimiter)
{
    vector<string> parts;
    string current;

    for (char ch : text)
    {
        if (ch == delimiter)
        {
            parts.push_back(current);
            current.clear();
        }
        else
        {
            current += ch;
        }
    }

    parts.push_back(current);

    return parts;
}


// --------------------------------------------------
// Main
// --------------------------------------------------

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // --------------------------------------------------
    // Read available resources
    // --------------------------------------------------

    AvailableResources available;

    if (!(cin
        >> available.food
        >> available.water
        >> available.medicine
        >> available.blankets))
    {
        cerr << "Invalid available resources input." << endl;
        return 1;
    }


    // --------------------------------------------------
    // Read number of requests
    // --------------------------------------------------

    int numberOfRequests;

    if (!(cin >> numberOfRequests))
    {
        cerr << "Invalid number of resource requests." << endl;
        return 1;
    }

    if (numberOfRequests < 0)
    {
        cerr << "Number of requests cannot be negative." << endl;
        return 1;
    }


    // Remove newline after integer input
    cin.ignore(10000, '\n');


    // --------------------------------------------------
    // Read resource requests
    // --------------------------------------------------

    vector<ResourceRequest> requests;

    requests.reserve(numberOfRequests);

    for (int i = 0; i < numberOfRequests; i++)
    {
        string line;

        getline(cin, line);

        if (line.empty())
        {
            cerr << "Invalid empty resource request at index "
                 << i << "." << endl;

            return 1;
        }

        vector<string> parts = split(line, '|');

        if (parts.size() != 8)
        {
            cerr << "Invalid resource request format at index "
                 << i << "." << endl;

            return 1;
        }

        try
        {
            ResourceRequest request;

            request.areaName = parts[0];

            request.priorityScore =
                stod(parts[1]);

            request.priorityLevel =
                parts[2];

            request.waitingTime =
                stod(parts[3]);

            request.foodDemand =
                stoi(parts[4]);

            request.waterDemand =
                stoi(parts[5]);

            request.medicineDemand =
                stoi(parts[6]);

            request.blanketDemand =
                stoi(parts[7]);


            // --------------------------------------------------
            // Validate values
            // --------------------------------------------------

            if (request.foodDemand < 0 ||
                request.waterDemand < 0 ||
                request.medicineDemand < 0 ||
                request.blanketDemand < 0)
            {
                cerr << "Resource demand cannot be negative."
                     << endl;

                return 1;
            }

            requests.push_back(request);
        }
        catch (...)
        {
            cerr << "Invalid numeric value in resource request "
                 << i << "." << endl;

            return 1;
        }
    }


    // --------------------------------------------------
    // Perform C++ resource allocation
    // --------------------------------------------------

    ResourceAllocator allocator(available);

    vector<AllocationRecord> records =
        allocator.allocateResources(requests);


    // --------------------------------------------------
    // Output allocation results
    // --------------------------------------------------

    for (size_t i = 0; i < records.size(); i++)
    {
        const AllocationRecord& record =
            records[i];

        cout
            << i << "|"
            << record.areaName << "|"
            << record.priorityScore << "|"
            << record.priorityLevel << "|"

            << record.foodDemand << "|"
            << record.foodAllocated << "|"
            << record.foodUnmet << "|"

            << record.waterDemand << "|"
            << record.waterAllocated << "|"
            << record.waterUnmet << "|"

            << record.medicineDemand << "|"
            << record.medicineAllocated << "|"
            << record.medicineUnmet << "|"

            << record.blanketDemand << "|"
            << record.blanketAllocated << "|"
            << record.blanketUnmet

            << endl;
    }


    // --------------------------------------------------
    // Output remaining resources
    // --------------------------------------------------

    RemainingResources remaining =
        allocator.getRemainingResources();

    cout
        << "REMAINING|"
        << remaining.food << "|"
        << remaining.water << "|"
        << remaining.medicine << "|"
        << remaining.blankets

        << endl;


    return 0;
}