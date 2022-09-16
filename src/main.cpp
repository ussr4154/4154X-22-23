#include "main.h"

void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {

	frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	middleRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	middleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	backRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  	backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	testAuton();
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

	}
}
