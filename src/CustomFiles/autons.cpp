#include "main.h"
using namespace okapi;

std::shared_ptr<OdomChassisController> chassis =
  ChassisControllerBuilder()
    .withMotors({8,10,9},{5,7,6})
    .withDimensions({AbstractMotor::gearset::blue, (60.0 / 36.0)}, {{3.25_in, 11.25_in}, imev5BlueTPR})
    .withOdometry()
    .buildOdometry();

// Chassis constructor
Drive EZchassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {10, 8, 9}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{7, 5, 6}

  // IMU Port
  ,2

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.666

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  ,{1, 2}

  // Right Tracking Wheel Ports (negative port will reverse it!)
  ,{3, 4}
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,9
);

void goForward(int distance){

    double wheelCircumference = 10.2101761242;
    double ticksPerRevolution = 500.0;
    double constant = (wheelCircumference/ticksPerRevolution);

    int target = (distance/constant);

    middleLeft.tare_position();

    float kP = 0.1;
    float kD = 0.01;
    float prevError = 0.0;

  while(fabs(middleLeft.get_position() < target)){

    double error = distance - middleLeft.get_position();
    double derivative = error - prevError;
    prevError = error;

    int power = (error*kP) + (derivative*kD);

    frontLeft = power;
    frontRight = -power;
    middleLeft = power;
    middleRight = -power;
    backLeft = power;
    backRight = -power;

  }

  frontLeft = 0;
  frontRight = 0;
  middleLeft = 0;
  middleRight = 0;
  backLeft = 0;
  backRight = 0;

}

void defaultConstants() {
  EZchassis.set_slew_min_power(80, 80);
  EZchassis.set_slew_distance(7, 7);
  EZchassis.set_pid_constants(&EZchassis.headingPID, 11, 0, 20, 0);
  EZchassis.set_pid_constants(&EZchassis.forward_drivePID, 0.45, 0, 5, 0);
  EZchassis.set_pid_constants(&EZchassis.backward_drivePID, 0.45, 0, 5, 0);
  EZchassis.set_pid_constants(&EZchassis.turnPID, 5, 0.003, 35, 15);
  EZchassis.set_pid_constants(&EZchassis.swingPID, 7, 0, 45, 0);
}

std::shared_ptr<AsyncMotionProfileController> profileController = 
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      4.0, // Maximum linear velocity of the Chassis in m/s
      2.5, // Maximum linear acceleration of the Chassis in m/s^2
      1.0 // Maximum linear jerk of the Chassis in m/s^3
    })
    .withOutput(chassis)
    .buildMotionProfileController();


void spinRoller(int theta, bool rev = false){
  intake.tare_position();
  
  if(rev){
    while(fabs(intake.get_position()) < theta){
    intake = 70;
    }
  }
  else {
    while(fabs(intake.get_position()) < theta){
      intake = -70;
    }
  }

  intake = 0;
}

void clearEncoders(){
  frontLeft.tare_position();
  frontRight.tare_position();
  middleLeft.tare_position();
  middleRight.tare_position();
  backLeft.tare_position();
  backRight.tare_position();
}

void index(){
  intake.tare_position();

  while(fabs(intake.get_position()) < 260){
    intake = -127;
  }

  intake = 0;
}

void angleUp(){
  
  leftFlywheel.set_value(true);
  rightFlywheel.set_value(true);

}

void angleDown(){
  
  leftFlywheel.set_value(false);
  rightFlywheel.set_value(false);

}

void fullWinPoint(){

  angleUp();


  EZchassis.set_drive_pid(-3, 30, true);
  EZchassis.wait_drive();

  spinRoller(400, true);

  chassis->setMaxVelocity(300);

  EZchassis.set_drive_pid(4, 30, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(88, 100);
  EZchassis.wait_drive();

  flywheel.move_velocity(440);

  EZchassis.set_drive_pid(37, 127, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(0, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(37, 110, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-33, 100);
  EZchassis.wait_drive();

  pros::delay(500);

  index();

  pros::delay(500);

  index();

  pros::delay(200);

  EZchassis.set_turn_pid(46, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(72, 110, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(0, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(7, 40, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-90, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-11, 40, true);
  EZchassis.wait_drive();

  spinRoller(400, true);
}

void fiveDisc(){

  angleUp();

  spinRoller(200);

  chassis->setMaxVelocity(300);

  chassis->moveDistance(0.3_ft);

  EZchassis.set_turn_pid(88, 100);
  EZchassis.wait_drive();

  flywheel.move_velocity(440);

  EZchassis.set_drive_pid(37, 127, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(0, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(39, 110, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-33, 100);
  EZchassis.wait_drive();

  pros::delay(500);

  index();

  pros::delay(500);

  index();

  pros::delay(400);

  flywheel.move_velocity(460);

  EZchassis.set_drive_pid(-5, 110, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-127, 100);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-45, 35, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-55, 100);
  EZchassis.wait_drive();

  intake = 0;

  pros::delay(300);

  index();

  pros::delay(700);

  index();

  pros::delay(700);

  index();
  
}

void skills(){

  flywheel.move_velocity(380);

  spinRoller(250, true);

  EZchassis.set_drive_pid(18, 70, true);
  EZchassis.wait_drive();

  pros::delay(100);

  EZchassis.set_turn_pid(89, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-21.5, 50, true);
  EZchassis.wait_drive();

  spinRoller(250, true);

  angleUp();

  EZchassis.set_drive_pid(64, 110, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(110, 100);
  EZchassis.wait_drive();

  pros::delay(200);

  index();
  
  pros::delay(300);

  index();

  pros::delay(100);

  intake = 127;

  EZchassis.set_turn_pid(180, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-56, 40, true);
  EZchassis.wait_drive();

  pros::delay(200);

  flywheel.move_velocity(365);

  EZchassis.set_drive_pid(28, 70, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(134, 100);
  EZchassis.wait_drive();

  pros::delay(100);

  index();

  pros::delay(500);

  index();

  pros::delay(500);

  index();

  pros::delay(100);

  EZchassis.set_turn_pid(232, 100);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-56, 40, true);
  EZchassis.wait_drive();

  pros::delay(400);

  intake = 0;

  EZchassis.set_turn_pid(180, 100);
  EZchassis.wait_drive();
  
  EZchassis.set_drive_pid(18, 70, true);
  EZchassis.wait_drive();

  pros::delay(100);

  index();

  pros::delay(500);

  index();

  pros::delay(500);

  index();

  EZchassis.set_drive_pid(-35, 60, true);
  EZchassis.wait_drive();

  intake = 127;

  EZchassis.set_drive_pid(-18, 30, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(233, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-12, 30, true);
  EZchassis.wait_drive();

  pros::delay(400);

  EZchassis.set_drive_pid(12, 30, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(180, 100);
  EZchassis.wait_drive();

  intake = 0;

  EZchassis.set_drive_pid(57, 70, true);
  EZchassis.wait_drive();

  pros::delay(100);

  index();

  pros::delay(500);

  index();

  EZchassis.set_drive_pid(-49, 70, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(270, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-10, 70, true);
  EZchassis.wait_drive();

  spinRoller(400, true);

  EZchassis.set_drive_pid(20, 70, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(180, 50);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-20, 70, true);
  EZchassis.wait_drive();

  spinRoller(400, true);

  EZchassis.set_drive_pid(20, 70, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(233, 50);
  EZchassis.wait_drive();

  expansion.set_value(true);

  pros::delay(3000);

  EZchassis.set_drive_pid(5, 30, true);
  EZchassis.wait_drive();
  /*

  chassis->setMaxVelocity(200);

  chassis->turnAngle(62_deg);

  flywheel = 0;

  intake = 127;

  pros::delay(100);

  chassis->setMaxVelocity(180);

  chassis->moveDistance(-6.2_ft);

  chassis->turnAngle(-7_deg);

  chassis->setMaxVelocity(450);

  flywheel.move_velocity(350);

  profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {5_ft, 0_ft, 0_deg}}, "moveB");
  profileController->setTarget("moveB");
  profileController->waitUntilSettled();

  chassis->setMaxVelocity(160);

  chassis->turnAngle(-25_deg);

  pros::delay(100);

  index();

  pros::delay(400);

  index();

  pros::delay(400);
  
  index();

  pros::delay(100);

  flywheel = 0;

  chassis->setMaxVelocity(160);

  chassis->moveDistance(-0.1_ft);

  chassis->turnAngle(75_deg);

  */
}

void testAuton(){

  //angleUp();

  flywheel.move_velocity(570);

  EZchassis.set_drive_pid(25, 90, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-89, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-11, 30, true);
  EZchassis.wait_drive();

  spinRoller(400, true);

  EZchassis.set_drive_pid(5, 30, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(-72, 100);
  EZchassis.wait_drive();

  index();

  pros::delay(700);

  index();
  
  pros::delay(200);

  EZchassis.set_turn_pid(0, 100);
  EZchassis.wait_drive();

  EZchassis.set_drive_pid(-6.5, 30, true);
  EZchassis.wait_drive();

  EZchassis.set_turn_pid(45, 100);
  EZchassis.wait_drive();

  angleUp();

  flywheel.move_velocity(440);

  intake = 127;

  EZchassis.set_drive_pid(-58, 42, true);
  EZchassis.wait_drive();

  pros::delay(400);

  EZchassis.set_turn_pid(-42, 100);
  EZchassis.wait_drive();

  pros::delay(200);

  index();

  pros::delay(600);

  index();

  pros::delay(600);

  index();

}