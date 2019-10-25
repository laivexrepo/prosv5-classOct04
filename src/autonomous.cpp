#include "autonomous.h"
#include "portdef.h"
#include "globals.h"

// provide a button function to start autonomous manual from controller for testing

void manualAutonomous(){
  // place this function in the top of the opcontrol function in main.cpp
if(DEBUG){ std::cout << "Entered Manual Autonomous Control Function \n"; }
  bool autoCheck=true;
  while (autoCheck) {
     if (master.get_digital(DIGITAL_A)) {
        // If the button A is pushed on the master remote, we will call Autonomous
        // function
        if(DEBUG){ std::cout << "Starting Autonomus Task \n"; }
        autonomous();        // Run autonomous manual
        autoCheck=false;
    }
    if (master.get_digital(DIGITAL_Y)) {
       // Drop out of autonomous check when the Y button is pressed
       autoCheck=false;
    }
  }
}
