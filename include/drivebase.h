#ifndef DRIVE_BASE_H_
#define DRIVE_BASE_H_

// ------- Define drivebase parameters ----------------------
#define WHEEL_DIAM 10   // diameter in cm
#define WHEEL_BASE 29   // wheel base distance between center
                        // of two frontwheels

void tankControl();
void arcadeControl();

void driveForDistance(float distance);  // drive a distance in cm.

#endif
