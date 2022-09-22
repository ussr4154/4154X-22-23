#include "main.h"
using namespace okapi;

std::shared_ptr<OdomChassisController> chassis =
  ChassisControllerBuilder()
    .withMotors({8,10,9},{5,7,6})
    .withDimensions({AbstractMotor::gearset::blue, (60.0 / 36.0)}, {{3.25_in, 11.25_in}, imev5BlueTPR})
    .withOdometry()
    .buildOdometry();

std::shared_ptr<AsyncMotionProfileController> profileController = 
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      4.0, // Maximum linear velocity of the Chassis in m/s
      2.5, // Maximum linear acceleration of the Chassis in m/s^2
      1.0 // Maximum linear jerk of the Chassis in m/s^3
    })
    .withOutput(chassis)
    .buildMotionProfileController();


void spinRoller(int theta){
  intake.tare_position();

  while(fabs(intake.get_position()) < theta){
    intake = -70;
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

  while(fabs(intake.get_position()) < 300){
    intake = -120;
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

  flywheel.move_velocity(435);

  spinRoller(200);

  chassis->setMaxVelocity(200);

  chassis->moveDistance(0.3_ft);

  pros::delay(200);

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(87_deg);

  chassis->setMaxVelocity(350);

  clearEncoders();

  profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {6_ft, 0_ft, 0_deg}}, "moveA");
  profileController->setTarget("moveA");
  profileController->waitUntilSettled();

  pros::delay(200);

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(-84_deg);

  clearEncoders();

  chassis->setMaxVelocity(350);

  profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {4.7_ft, 0_ft, 0_deg}}, "moveB");
  profileController->setTarget("moveB");
  profileController->waitUntilSettled();

  chassis->setMaxVelocity(170);

    angleUp();
  
  chassis->turnAngle(-24_deg);

  index();

  pros::delay(1000);

  index();

  flywheel = 0;

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(63_deg);

  chassis->setMaxVelocity(500);

  profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {8.4_ft, 0_ft, 0_deg}}, "moveC");
  profileController->setTarget("moveC");
  profileController->waitUntilSettled();

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(-37_deg);

  chassis->setMaxVelocity(350);

  chassis->moveDistance(1.3_ft);

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(-86_deg);

  intake = 127;

  pros::delay(200);

  chassis->moveDistance(-.9_ft);

  spinRoller(300);

}

void testAuton(){

  flywheel.move_velocity(440);

  spinRoller(200);

  chassis->setMaxVelocity(200);

  chassis->moveDistance(0.3_ft);

  pros::delay(200);

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(87_deg);

  chassis->setMaxVelocity(350);

  clearEncoders();

  profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {6_ft, 0_ft, 0_deg}}, "moveA");
  profileController->setTarget("moveA");
  profileController->waitUntilSettled();

  pros::delay(200);

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(-84_deg);

  clearEncoders();

  chassis->setMaxVelocity(350);

  profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {4.6_ft, 0_ft, 0_deg}}, "moveB");
  profileController->setTarget("moveB");
  profileController->waitUntilSettled();

  chassis->setMaxVelocity(140);

  angleUp();
  
  chassis->turnAngle(-24_deg);
  
  pros::delay(500);

  index();

  pros::delay(1000);

  index();

  flywheel.move_velocity(530);

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(-110_deg);

  pros::delay(200);

  intake = 127;

  chassis->setMaxVelocity(190);

  angleDown();

  chassis->moveDistance(-5_ft);

  pros::delay(500);

  intake = 0;

  chassis->turnAngle(57_deg);
  
  pros::delay(200);

  index();

  pros::delay(500);

  index();

  pros::delay(500);

  index();

  
}