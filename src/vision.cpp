#include "vision.h"
#include "portdef.h"
#include "globals.h"

void define_signature(){
  // NOT BEING USED RIGHT NOW - FOR LATER TO create signature from code into the
  // vision sensor
  pros::vision_signature_s_t RED_SIG =
    pros::Vision::signature_from_utility(EXAMPLE_SIG, -51, 51, 0, -1, 341, 170, 1.100, 0);

  vision_sensor.set_signature(EXAMPLE_SIG, &RED_SIG);
}

void get_signature() {
  // Gets the current signature idenrtified by EXAMPLE_SIG and prints out
  // the values of the signature to eventualy store and manual create

  pros::vision_signature_s_t sig = vision_sensor.get_signature(EXAMPLE_SIG);
  pros::Vision::print_signature(sig);
}

void detect_cube(){
  // simpel detect cube code function, assumes there is a signature EXAMPEL_SIG stored
  // on the vision sensor, it will loop 20 times and print out the x/y center coordinates
  // of the largest object detected -- see the object vision_object_s_t data eleemtns returned

  int count = 0;
  while (count < 20) {
    pros::vision_object_s_t rtn = vision_sensor.get_by_sig(0, EXAMPLE_SIG);
    // Gets the largest object of the EXAMPLE_SIG signature
    std::cout << "sig: " << rtn.signature;    // should be the number defined by EXAMPLE_SIG
    if (rtn.signature == 255) std::cout << " errno: " << errno << "\n";
    // errno - likley 33 no object found/seen/detected, 117 can't talk to sensor
    // lets print some values we get
    std::cout << "Middle Coord - X: " << rtn.x_middle_coord << " Middle Coord - Y: "  << rtn.y_middle_coord << "\n";

    pros::delay(2);
    count++;
  }
}
