#include "main.h"

//Helper Functions
void setDrive(int left, int right) {

  frontLeft = left;
  middleLeft = left;
  backLeft = left;
  frontRight = right;
  middleRight = right;
  backRight = right;

}

//Drive Functions
void setDriveMotors() {

  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  setDrive(leftJoystick,rightJoystick);

}

void setBrakes() {
  frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  middleRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  middleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}