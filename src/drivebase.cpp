#include "main.h"
#include "globals.h"
#include "portdef.h"
#include "drivebase.h"
#include "autonomous.h"

void tankControl()
{
  // We are running the robot in Tankmode
  int left = master.get_analog(ANALOG_LEFT_Y);
  int right = master.get_analog(ANALOG_RIGHT_Y);

  left_wheel = left;
  right_wheel = right;
}

void arcadeControl()
{
  // We are running the robot in arcade mode using LEFT joystick
  int power = master.get_analog(ANALOG_LEFT_Y);
  int turn = master.get_analog(ANALOG_LEFT_X);
  int left = power + turn;
  int right = power - turn;
  left_wheel = left;
  right_wheel = right;
}

void driveForDistance(float distance) {
  // function drives robot for set distance where distance is
  // given in cm.  A negative numebr makes the robot drive backwards.

  float degreesTravel = (distance / (3.14 * WHEEL_DIAM)) * 360;
  left_wheel.tare_position();       // ensure encoders are reset before
  right_wheel.tare_position();      // movement.
  left_wheel.move_absolute(degreesTravel, MOTOR_MAX_SPEED);
  right_wheel.move_absolute(degreesTravel, MOTOR_MAX_SPEED);

  std::cout << "Degrees to travel: " << degreesTravel << "\n";
  // We need to make sure motors reach there target +- 5 degrees.
  while (!((left_wheel.get_position() < (degreesTravel + 5)) && (left_wheel.get_position() > degreesTravel - 5))) {
    pros::delay(2);
  }
}
