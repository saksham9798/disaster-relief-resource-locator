# Algorithm Design — Disaster Relief Resource Allocation

## 1. Problem Definition

This project is designed to efficiently distribute limited relief resources among disaster-affected areas according to their priority level.

The priority of an affected area will be determined using factors such as:

* Severity of the disaster
* Population affected
* Medical need
* Resource demand

The system will prioritize affected areas and allocate available resources according to the selected allocation strategy.

---

## 2. Objective

The main objective is to design an algorithm that:

1. Calculates the priority of each affected area.
2. Ranks affected areas according to their priority.
3. Processes high-priority areas before lower-priority areas.
4. Allocates limited resources according to the selected allocation strategy.
5. Handles situations where available resources are insufficient.
6. Reports the remaining resources and unmet demand.

---

## 3. Inputs

The algorithm will take the following information as input:

### Disaster Area

* Area ID
* Population affected
* Severity level
* Medical need
* Resource demand

### Resources (food, water, medicines)

* Resource type 
* Available quantity

### Additional information

* [To be decided: waiting time]
* [To be decided: other factors if required]

---

## 4. Outputs

The system should produce:

### Area Priority

* Area ID
* Population
* Severity
* Medical need
* Demand
* Calculated priority score (1–100)

### Priority Order

The areas arranged from highest priority to lowest priority.

### Resource Allocation

For each area:

* Resource requested
* Resource allocated
* Remaining requirement
* Allocation status

Possible allocation statuses:

* Fully Allocated
* Partially Allocated
* Not Allocated

### Remaining Resources

The quantity of each resource remaining after allocation.

---

## 5. Priority Calculation

The priority score will be calculated using multiple factors:

* Severity
* Population affected
* Medical need
* Demand

Each factor may have a different weight because the factors have different levels of importance.

The priority score will be normalized to a scale of 1–100.

The exact weighting and calculation method will be finalized after evaluating the characteristics of each factor.

---

## 6. Data Structures

The following data structures are being considered:

| Requirement                         | Proposed Data Structure | Reason                                       |
| ----------------------------------- | ----------------------- | -------------------------------------------- |
| Store information of an area        | Structure/Class         | Groups related area information              |
| Store multiple areas                | Array/Vector            | Stores a collection of areas                 |
| Process areas according to priority | Priority Queue          | Highest-priority area can be processed first |
| Store pending requests              | Queue                   | Maintains request order                      |
| Search areas                        | Searching algorithm     | Finds an area efficiently                    |
| Arrange areas by priority           | Sorting algorithm       | Produces priority ranking                    |

The final data structures will be selected based on the algorithm requirements and efficiency analysis.

---

## 7. Initial System Flow

Disaster Area Information

↓

Calculate Priority Score

↓

Insert Areas into Priority Queue

↓

Select Highest-Priority Area

↓

Check Resource Availability

↓

Allocate Available Resources

↓

Update Remaining Resources

↓

Process Next Area

↓

Generate Allocation Results

---

## 8. Resource Allocation Problem

The total resource demand may be greater than the available resources.

For example:

Available food = 1,000 units

Total requested food = 2,500 units

Therefore, the system must determine how the available 1,000 units should be distributed among the affected areas.

The initial allocation strategy will be priority-based.

Other allocation strategies may be considered later for comparison.

---

## 9. Edge Cases

The algorithm should handle cases such as:

1. No affected areas.
2. Only one affected area.
3. No resources available.
4. Available resources are greater than total demand.
5. Available resources are less than total demand.
6. Two areas have the same priority.
7. An area has zero demand.
8. Invalid severity or medical-need values.
9. Negative resource quantities.
10. Multiple areas requesting the same limited resource.

---

## 10. Algorithm Analysis

The following operations will be analyzed:

* Priority calculation
* Insertion into priority queue
* Removal of highest-priority area
* Searching
* Sorting
* Resource allocation

Time complexity and space complexity will be determined after the final algorithms and data structures are selected.

---

## 11. Testing

The algorithm will be tested using different scenarios, including:

* High resources and low demand
* Low resources and high demand
* Multiple high-priority areas
* Equal-priority areas
* No available resources
* Multiple resource types

Expected results will be compared with the actual algorithm output.
