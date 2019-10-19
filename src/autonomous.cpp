#include "autonomous.h"
#include "portdef.h"
#include "globals.h"

// provide a button function to start autonomous manula from controller for testing

void manualAutonomous(){
  if (master.get_digital(DIGITAL_A)) {
     // If the button A is pushed on the master remote, we will call Autonomous
     // function
     std::cout << "Starting Autonomus Task \n";
     autonomous();        // Run autonomous manual 
   }
}
