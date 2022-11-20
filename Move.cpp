/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Alec Murrell, Ethan George, Joey Painter, Sophia Liang
 * alecmurr, eten, painterj, sxliang
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    stringstream ss(commandString);
    char e;
    char move;
    if (commandString == "") {
        isPass = true;
    }
    else if (commandString == "s" || commandString == "S") {
        isSave = true;
    }
    else if (commandString == "Q" || commandString == "q") {
        isQuit = true;
    }
    else {
        ss >> e >> elevatorId >> move;
        if ( move == 'p') {
            isPickup = true;
        }
        else if (move == 'f') {
            ss >> targetFloor;
        }
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPassMove() == true ||
        isQuitMove() == true ||
        isSaveMove() == true) {
        return true;
    }
    else if (elevatorId >= 0 && elevatorId <NUM_ELEVATORS && elevators[elevatorId].isServicing() == false) {
        if (isPickupMove() == true) {
            return true;
        }
        else if (isPickupMove() != true && targetFloor >= 0 && targetFloor < NUM_FLOORS && elevators[elevatorId].getCurrentFloor() != targetFloor) {
            return true;
        }
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    targetFloor = currentFloor;
    for (size_t i = 0; i < pickupList.length(); i++ ) {
        peopleToPickup[i] = pickupList.at(i) - '0';
        numPeopleToPickup++;
        totalSatisfaction += (MAX_ANGER - pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel());
        if (fabs(pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor() - currentFloor) > fabs(targetFloor - currentFloor)) {
            targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
        }
    }
   
}


//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
