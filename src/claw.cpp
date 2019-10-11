#include "main.h"
#include "globals.h"
#include "portdef.h"
#include "claw.h"

void clawControl(){
  if (master.get_digital(DIGITAL_L1)) {
     clawMotor.move_velocity(50);
   }
   else if (master.get_digital(DIGITAL_L2)) {
     clawMotor.move_velocity(-50);
   }
   else {
     clawMotor.move_velocity(0);
   }
}
