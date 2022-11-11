/*
 * Copyright 2022 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;
// declare your test functions here
void person_tests();
void elevator_tests();
void start_tests() {
    // call your test functions here
    person_tests();
    elevator_tests();
    return;
}
// write test functions here
void person_tests() {
    //initialize a person with targetFloor 5, anger 5
    Person p("0f0t5a5");
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 5" << endl;
    
    //simulate time being a multiple of TICKS_PER_ANGER_INCREASE
    bool exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 0" << endl;
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    //simulate time not being a multiple
    p.tick(TICKS_PER_ANGER_INCREASE - 1);
    //no change
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    p.tick(TICKS_PER_ANGER_INCREASE); //7 after
    p.tick(TICKS_PER_ANGER_INCREASE); //8 after
    p.tick(TICKS_PER_ANGER_INCREASE); //9 after
    exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 1" << endl;
    
    Person p1("6f4t5a6");
    cout << p1.getCurrentFloor() << " " << p1.getTurn() << " Expected 4 6" << endl;
    p1.tick(TICKS_PER_ANGER_INCREASE - 2);
    cout << p1.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    Person p2("11f8t5a9");
    bool exploded2 = p2.tick(TICKS_PER_ANGER_INCREASE);
    cout << p2.getCurrentFloor() << " " << p2.getTurn() << " Expected 8 11" << endl;
    cout << exploded2 << " Expected 1" << endl;
    Person p3("11f8t5a3");
    bool exploded3 = p3.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded3 << " Expected 0" << endl;
}

void elevator_tests() {
    Elevator e1;
    e1.setCurrentFloor(2);
    e1.serviceRequest(4);
    e1.tick(12);
    cout << "Expected: 3 Actual: " << e1.getCurrentFloor();
    cout << "Expected: 1 Actual: " << e1.isServicing();
    cout << "Expected: 4 Acutal: " << e1.getTargetFloor();
    
    Elevator e2;
    e2.setCurrentFloor(3);
    e2.serviceRequest(1);
    e2.tick(3);
    cout << "Expected: 2 Actual: " << e2.getCurrentFloor();
    cout << "Expected: 1 Actual: " << e2.isServicing();
    
    Elevator e3;
    e3.setCurrentFloor(3);
    e3.serviceRequest(3);
    e3.tick(4);
    cout << "Expected: 3 Actual: " << e3.getCurrentFloor();
    cout << "Expected: 0 Actual: " << e3.isServicing();
    cout << "Expected: 3 Actual: " << e3.getTargetFloor();
    
    Elevator e4;
    e4.setCurrentFloor(4);
    e4.serviceRequest(3);
    e4.tick(4);
    cout << "Expected: 4 Actual: " << e4.getCurrentFloor();
    e4.tick(4);
    cout << "Expected: 0 Actual: " << e4.isServicing();
    cout << "Expected: 3 Actual: " << e4.getTargetFloor();
    
    
}
// write test functions here
