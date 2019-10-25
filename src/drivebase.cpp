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

void driveForDistance(float distance, int speed) {
  // function drives robot for set distance where distance is
  // given in cm.  A negative numebr makes the robot drive backwards.
  // distance -- distance in cm
  // speed    -- speed in RPM -- please note cartridge installed for range
  //             red    - 100RPM max
  //             green  - 200RPM
  //             blue   - 600RPM

  float degreesTravel = (distance / (3.14 * WHEEL_DIAM)) * 360;
  // set the "window" for which we need to encoder to reach and stop movement
  float degreesTravelAbs = fabsf(degreesTravel);
  float minTarget = degreesTravelAbs -5;
  float maxTarget = degreesTravelAbs +5;

  left_wheel.tare_position();       // ensure encoders are reset before
  right_wheel.tare_position();      // movement.
  left_wheel.move_absolute(degreesTravel, speed);
  right_wheel.move_absolute(degreesTravel, speed);

  if(DEBUG){
     std::cout << "\ndriveForDistance -- distance: " << distance << " speed: " << speed << "\n";
     std::cout << "Degrees to travel: " << degreesTravel << "\n";
     std::cout << "minTarget: " << minTarget << " maxTarget: " << maxTarget << "\n";
  }
  // We need to make sure motors reach there target +- 5 degrees.
  while (!((fabs(left_wheel.get_position()) < (maxTarget)) && (fabs(left_wheel.get_position()) > minTarget))) {
    pros::delay(2);
  }
  if(DEBUG) {
    std::cout << "Encoder Left: " << left_wheel.get_position() << " Right: " << right_wheel.get_position() << "\n";
  }
  // we sill stop the motors
  left_wheel.move_velocity(0);
  right_wheel.move_velocity(0);
}

void pivotTurn(float angle, int speed){
  // Make a pivot turn - left wheel and right wheel both turn in opposite direction
  // a postivie angle -- clockwise (left wheel forward, right wheel backward)
  // a negative angle -- counter clockwise (left hweel backwards, right wheel forward)

  // calculate the circumference of the turnign circle based on robot size
  // THe WHEEL_BASE in this case is the d (2 x r) of the turning circle hence dPi
  float turnCircleCirc = 3.14 * WHEEL_BASE;
  float toTravelCircleDistance = (angle * turnCircleCirc ) / 360;
  float degreesTravel = (toTravelCircleDistance / (3.14 * WHEEL_DIAM)) * 360;

  float degreesTravelAbs = fabsf(degreesTravel);
  float minTarget = degreesTravelAbs -5;
  float maxTarget = degreesTravelAbs +5;

  left_wheel.tare_position();       // ensure encoders are reset before
  right_wheel.tare_position();      // movement.

  if(DEBUG){
    std::cout << "\nPivot Turn Function -- " << " speed: " << speed << "\n";
    std::cout << "Degrees to travel: " << degreesTravel << " Angle: " << angle << "\n";
    std::cout << "minTarget: " << minTarget << " maxTarget: " << maxTarget << "\n";
  }

  if(angle >= 0) {
    //clockwise
    left_wheel.move_absolute(degreesTravel, speed);
    right_wheel.move_absolute(-degreesTravel, speed);
  }
  if (angle <= 0){
    // counter clockwise
    left_wheel.move_absolute(degreesTravel, speed);
    right_wheel.move_absolute(-degreesTravel, speed);
  }
  // We need to make sure motors reach there target +- 5 degrees.
  while (!((fabs(left_wheel.get_position()) < (maxTarget)) && (fabs(left_wheel.get_position()) > minTarget))) {
    pros::delay(2);
  }
  // we sill stop the motors
  left_wheel.move_velocity(0);
  right_wheel.move_velocity(0);
  if(DEBUG) {
    std::cout << "Encoder Left: " << left_wheel.get_position() << " Right: " << right_wheel.get_position() << "\n";
  }
}

void swingTurn(float angle, int speed){
  // Make a swing turn - left wheel OR right wheel turn depending on angle sign direction
  // a postivie angle -- clockwise (left wheel forward, right wheel stopped)
  // a negative angle -- counter clockwise (left hweel stopped, right wheel forward)

  // calculate the circumference of the turnign circle based on robot size
  float turnCircleCirc = 3.14 * WHEEL_BASE;
  float toTravelCircleDistance = (angle * turnCircleCirc ) / 360;
  // WHEEL_DIAM in this case is the radius of the turning circle - so we must do 2PIr
  float degreesTravel = ((toTravelCircleDistance / (3.14 * WHEEL_DIAM)) * 360) * 2;
  float degreesTravelAbs = fabsf(degreesTravel);
  float minTarget = degreesTravelAbs -5;
  float maxTarget = degreesTravelAbs +5;

  left_wheel.tare_position();       // ensure encoders are reset before
  right_wheel.tare_position();      // movement.

  if(DEBUG){
    std::cout << "\nSwingTurn -- speed: " << speed << "\n";
    std::cout << "Degrees to travel: " << degreesTravel << " Angle: " << angle << "\n";
    std::cout << "minTarget: " << minTarget << " maxTarget: " << maxTarget << "\n";
  }

  if(angle >= 0) {
    //clockwise
    right_wheel.move_velocity(0);      // make sure we got a break on right wheel for swing turn
    left_wheel.move_absolute(degreesTravelAbs, speed);
    // We need to make sure motors reach there target +- 5 degrees.
    while (!((fabs(left_wheel.get_position()) < (maxTarget)) && (fabs(left_wheel.get_position()) > minTarget))) {
      pros::delay(2);
    }
  }
  if (angle <= 0){
    left_wheel.move_velocity(0);      // make sure we got a break on left wheel for swing turn
    right_wheel.move_absolute(degreesTravelAbs, speed);
    // We need to make sure motors reach there target +- 5 degrees.
    while (!((fabs(right_wheel.get_position()) < (maxTarget)) && (fabs(right_wheel.get_position()) > minTarget))) {
      pros::delay(2);
    }
  }
  left_wheel.move_velocity(0);
  right_wheel.move_velocity(0);
  if(DEBUG) {
    std::cout << "Encoder Left: " << left_wheel.get_position() << " Right: " << right_wheel.get_position() << "\n";
  }
}
