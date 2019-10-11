#include "main.h"
#include "globals.h"
#include "portdef.h"
#include "lift.h"

void liftControl(){
  if (master.get_digital(DIGITAL_R1)) {
     liftMotor1.move_velocity(100);
   }
   else if (master.get_digital(DIGITAL_R2)) {
     liftMotor1.move_velocity(-100);
   }
   else {
     liftMotor1.move_velocity(0);
   }
}
