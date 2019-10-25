#include "main.h"
#include "globals.h"
#include "portdef.h"
#include "drivebase.h"
#include "lift.h"
#include "claw.h"
#include "autonomous.h"


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

	pros::Motor left_wheel (LEFT_MOTOR_PORT, MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor right_wheel (RIGHT_MOTOR_PORT, MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor liftMotor1 (LIFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor clawMotor(CLAW_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

  // Set the brake mode for the lift motor - hold position when stopped
	liftMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	// We can put LCD selector here
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// drive forward a given distance in cm.
	if(DEBUG){ std::cout << "Starting Autonomous Task \n"; }
	driveForDistance(100, 50);  // 100cm forward

	driveForDistance(-100, 50); // 100cm backwards

	// pivot turn
	pivotTurn(90, 50);

  pivotTurn(-90,50);

	driveForDistance(50, 100);  // 50cm forward

	swingTurn(90, 50);

	swingTurn(-90, 50);

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	if(DEBUG){ std::cout << "Starting Opcontrol Task \n"; }
  // call manual autonomous run option, should be commented out in
	// tournament production code to invertenly trigger autonmous
	// during driver control
	if(MANUAL_AUTON) {manualAutonomous(); }		// allow for manual autonmous starts
																						// define is does in globals.h

  while(true) {
	 if(ARCADE_MODE) {
		 arcadeControl();
	 }
	 else
	 {
		 tankControl();
   }
	 liftControl();
	 clawControl();
 	 pros::delay(20);
  }
}
