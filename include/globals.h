#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "main.h"

// ------------ make sure all motors are available to all code -------------
extern pros::Motor left_wheel;
extern pros::Motor right_wheel;
extern pros::Motor liftMotor1;
extern pros::Motor clawMotor;

extern pros::Controller master;
extern pros::Controller partner;

extern pros::ADIEncoder encoderOdometer;

// ----------- Golbal variable to control drive base mode -----------------
#define ARCADE_MODE true

// ----------- Global variables to assist in code development ------------
#define DEBUG false

#endif
