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

extern pros::Vision vision_sensor;

// ------------ Global accessible functions -------------------------------
extern void robotDataLogger();

// ----------- Global variable to control drive base mode -----------------
#define ARCADE_MODE false     // run in tankmode - if true arcade mode

// ----------- Global variables to assist in code development ------------
#define DEBUG true            // turn on DEBUG statements, should be off in final build

#define MANUAL_AUTON true     // allow for autonomous testing use Remote intead of
                              // competition switch -- set to false for production
                              // and competition!!!
#endif
