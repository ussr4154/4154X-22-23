#include "main.h"

void initialize() {

	pros::lcd::initialize();
	defaultConstants();

	if (pros::competition::is_connected()){
		ez::as::initialize();
  	}

	ez::as::auton_selector.add_autons({
    Auton("Full Win Point", fullWinPoint),
    Auton("5 Shots", testAuton),
    //Auton("Alternate Roller", auto3),
  });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {

	/*frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	middleRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	middleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	backRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	*/
	skills();
}

void opcontrol() {

	while (true) {

		setBrakes();
		setDriveMotors();
		setIntake();
		//setIndex();
		setFlywheelToggle();
		setFlywheel();
		toggleShotAngle();
		setShotAngle();
		shootStrings();

		pros::delay(10);

	}
}
