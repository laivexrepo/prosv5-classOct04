#ifndef DRIVE_BASE_H_
#define DRIVE_BASE_H_

// ------- Define drivebase parameters ----------------------
#define WHEEL_DIAM 10   // diameter in cm
#define WHEEL_BASE 29   // wheel base distance between center
                        // of two frontwheels

#define MOTOR_MAX_SPEED 100

void tankControl();
void arcadeControl();

void driveForDistance(float distance, int speed);  // drive a distance in cm.
void pivotTurn(float angle, int speed);            // pivot turn for angle and speed
void swingTurn(float angle, int speed);

#endif
