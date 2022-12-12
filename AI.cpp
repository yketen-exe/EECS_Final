/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Alec Murrell, Ethan George, Joey Painter, Sophia Liang
 * alecmurr, eten, painterj, sxliang
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

/*
* Requires: buildingState is a valid state representing the current building
* Modifies: Nothing
* Effects:  Returns a string that represents the decision the AI makes
*           given the current state of the building, which it reads
*           from buildingState.
*           The string should share the exact format as a
*           human player's move input.
*/
string getAIMoveString(const BuildingState& buildingState) {
    string AIMove = "";
    int maxAnger = -1;
    int secondMaxAnger = -1;
    int thirdMaxAnger = -1;
    int maxAngerFloor = -1;
    int secondAngerFloor = -1;
    int thirdAngerFloor = -1;

    for (int i = 0; i < NUM_FLOORS; ++i) {
        int currentMaxAnger = 0;
        for (int j = 0; j < buildingState.floors[i].numPeople; j++) {
            currentMaxAnger += buildingState.floors[i].people[j].angerLevel;
        }
        if (currentMaxAnger > maxAnger && buildingState.floors[i].numPeople > 0) {
            thirdMaxAnger = secondMaxAnger;
            secondMaxAnger = maxAnger;
            maxAnger = currentMaxAnger;
            thirdAngerFloor = secondAngerFloor;
            secondMaxAnger = maxAngerFloor;
            maxAngerFloor = i;
            
        }
        else if (currentMaxAnger > secondMaxAnger && buildingState.floors[i].numPeople > 0 ) {
            thirdMaxAnger = secondMaxAnger;
            secondMaxAnger = currentMaxAnger;
            thirdAngerFloor = secondAngerFloor;
            secondAngerFloor = i;
        }
        else if (currentMaxAnger > thirdMaxAnger && buildingState.floors[i].numPeople > 0)
            thirdMaxAnger = currentMaxAnger;
            thirdAngerFloor = i;
    }
    
    _Elevator availableElevators[NUM_ELEVATORS];
    _Elevator unavailableElevators[NUM_ELEVATORS];
    int sizeAvailable = 0;
    int sizeUnavailable = 0;
    int numAvailable = 0;
    int numUnavailable = 0;
    bool elevatorTo1st = false;
    bool elevatorTo2nd = false;
    for (int j = 0; j < NUM_ELEVATORS; j++) {
        if (buildingState.elevators[j].isServicing == false) {
            numAvailable++;
            availableElevators[sizeAvailable] = buildingState.elevators[j];
            sizeAvailable++;
        }
        else {
            numUnavailable++;
            unavailableElevators[sizeUnavailable] = buildingState.elevators[j];
            sizeUnavailable++;
        }
    }

    if (numUnavailable == 3) {
        return "";
    }
    else if (numUnavailable == 2) {
        
        for (int j = 0; j < numUnavailable; j++) {
            if (unavailableElevators[j].targetFloor == maxAngerFloor) {
                elevatorTo1st = true;
            }
            if (availableElevators[j].targetFloor == secondAngerFloor) {
                elevatorTo2nd = true;
            }
        }
        
        if (elevatorTo1st == true && elevatorTo2nd == true) {
            maxAngerFloor = thirdAngerFloor;
            maxAnger = thirdMaxAnger;
        }
        else if (elevatorTo2nd == false && elevatorTo1st == true) {
            maxAngerFloor = secondAngerFloor;
            maxAnger = secondMaxAnger;
            secondMaxAnger = thirdMaxAnger;
            secondAngerFloor = thirdAngerFloor;
        }
        
        for (int i =0; i < NUM_ELEVATORS; i++) {
            if (buildingState.elevators[i].isServicing == false) {
                int currentFloor = buildingState.elevators[i].currentFloor;
                if (maxAngerFloor == -1) {
                    if (currentFloor > 5) {
                        AIMove = "e";
                        AIMove.append(1, char(i) + 48);
                        AIMove.append(1, 'f');
                        AIMove.append(1, char(currentFloor - 1) + 48);
                        return AIMove;
                    }
                    else if (currentFloor < 5) {
                        AIMove = "e";
                        AIMove.append(1, char(i) + 48);
                        AIMove.append(1, 'f');
                        AIMove.append(1, char(currentFloor + 1) + 48);
                        return AIMove;
                    }
                    else {
                        return "";
                    }
                }
                else if (buildingState.floors[currentFloor].numPeople > 0) {
                        AIMove = "e";
                        AIMove.append(1, char(i) + 48);
                        AIMove.append(1, 'p');
                        return AIMove;
                }
                else {
                        AIMove = "e";
                        AIMove.append(1, char(i) + 48);
                        AIMove.append(1, 'f');
                        AIMove.append(1, char(maxAngerFloor) + 48);
                        return AIMove;
                }
            }
                
        }
    
    }
    else if (numUnavailable == 1) {
        if (unavailableElevators[0].targetFloor == maxAngerFloor) {
            elevatorTo1st = true;
            maxAngerFloor = secondAngerFloor;
            maxAnger = secondMaxAnger;
            secondMaxAnger = thirdMaxAnger;
            secondAngerFloor = thirdAngerFloor;
        }
        int nearestElevator = -1;
        int nearestDistance = 11;
        for (int i = 0; i < NUM_ELEVATORS; i++) {
            if (buildingState.elevators[i].isServicing == false) {
                int currentFloor1 = buildingState.elevators[i].currentFloor;
                if(fabs(currentFloor1 - maxAngerFloor) < nearestDistance) {
                    nearestElevator = i;
                    nearestDistance = fabs(currentFloor1 - maxAngerFloor);
                }
            }
        }
        int nearestElevatorFloor = buildingState.elevators[nearestElevator].currentFloor;
        if (maxAngerFloor == -1) {
            if (nearestElevatorFloor > 5) {
                AIMove = "e";
                AIMove.append(1, char(nearestElevator) + 48);
                AIMove.append(1, 'f');
                AIMove.append(1, char(nearestElevatorFloor - 1) + 48);
                return AIMove;
            }
            else if (nearestElevatorFloor < 5) {
                AIMove = "e";
                AIMove.append(1, char(nearestElevator) + 48);
                AIMove.append(1, 'f');
                AIMove.append(1, char(nearestElevatorFloor + 1) + 48);
                return AIMove;
            }
            else {
                return "";
            }
        }
        if (nearestDistance == 0 && buildingState.floors[nearestElevatorFloor].numPeople > 0) {
            AIMove = "e";
            AIMove.append(1, char(nearestElevator) + 48);
            AIMove.append(1, 'p');
            return AIMove;
        }
        else {
            AIMove = "e";
            AIMove.append(1, char(nearestElevator) + 48);
            AIMove.append(1, 'f');
            AIMove.append(1, char(maxAngerFloor) + 48);
            return AIMove;
        }
    }
    else {
        int nearestElevator1 = -1;
        int nearestDistance1 = 11;
        for (int i = 0; i < NUM_ELEVATORS; i++) {
            if (buildingState.elevators[i].isServicing == false) {
                int currentFloor2 = buildingState.elevators[i].currentFloor;
                if(fabs(currentFloor2 - maxAngerFloor) < nearestDistance1) {
                     nearestElevator1 = i;
                    nearestDistance1 = fabs(currentFloor2 - maxAngerFloor);
                }
            }
        }
        if (maxAngerFloor == -1) {
            if (buildingState.elevators[nearestElevator1].currentFloor > 5) {
                AIMove = "e";
                AIMove.append(1, char(nearestElevator1) + 48);
                AIMove.append(1, 'f');
                AIMove.append(1, char(buildingState.elevators[nearestElevator1].currentFloor - 1) + 48);
                return AIMove;
            }
            else if (buildingState.elevators[nearestElevator1].currentFloor < 5) {
                AIMove = "e";
                AIMove.append(1, char(nearestElevator1) + 48);
                AIMove.append(1, 'f');
                AIMove.append(1, char(buildingState.elevators[nearestElevator1].currentFloor + 1) + 48);
                return AIMove;
            }
            else {
                return "";
            }
        }
        if (nearestDistance1 == 0) {
            AIMove = "e";
            AIMove.append(1, char(nearestElevator1) + 48);
            AIMove.append(1, 'p');
            return AIMove;
        }
        else {
            AIMove = "e";
            AIMove.append(1, char(nearestElevator1) + 48);
            AIMove.append(1, 'f');
            AIMove.append(1, char(maxAngerFloor) + 48);
            return AIMove;
        }
       
    }
    return "";
    }
    
/*
* Requires: buildingState is a valid state representing the current building
*           move is a pickup move that was generated by getAIMoveString()
*           floorToPickup represents the floor the pickup move occurred.
* Modifies: Nothing
* Effects:  Returns a string representing which people indices
*           should be picked up. The string should share the exact format
*           as a human player's pickup list input.
*/
string getAIPickupList(const Move& move, const BuildingState& buildingState,
                       const Floor& floorToPickup) {
    int maxAnger = 0;
    int targetFloor = -1;
    int currentFloor = floorToPickup.getPersonByIndex(0).getCurrentFloor();
    string pickUpList = "";
    
    for (int i = 0; i < floorToPickup.getNumPeople(); i++ ) {
        if(floorToPickup.getPersonByIndex(i).getAngerLevel() >= maxAnger) {
            maxAnger = floorToPickup.getPersonByIndex(i).getAngerLevel();
            targetFloor = floorToPickup.getPersonByIndex(i).getTargetFloor();
        }
    }
    
    if (targetFloor > currentFloor) {
        for (int i =0; i <floorToPickup.getNumPeople(); i++) {
            if (floorToPickup.getPersonByIndex(i).getTargetFloor() > currentFloor ) {
                pickUpList.append(1, char(i)+48);
            }
        }
    }
    else if (targetFloor < currentFloor) {
        for (int i =0; i <floorToPickup.getNumPeople(); i++) {
            if (floorToPickup.getPersonByIndex(i).getTargetFloor() < currentFloor ) {
                pickUpList.append(1, char(i)+48);
            }
        }
    }
    
    return pickUpList;
}
