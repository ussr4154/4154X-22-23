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

  while(intake.get_position() < theta){
    intake = 70;
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

void fullWinPoint(){

  flywheel.move_velocity(570);

  spinRoller(300);

  chassis->setMaxVelocity(300);

  chassis->moveDistance(0.2_ft);
  
  pros::delay(2800);

  index();

  pros::delay(1100);

  index();

  chassis->setMaxVelocity(200);

  chassis->turnAngle(74_deg);

  chassis->setMaxVelocity(400);

  pros::delay(200);

  /*profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {3.5_ft, 0_ft, 0_deg}}, "moveA");
  profileController->setTarget("moveA");
  profileController->waitUntilSettled();
  */
  pros::delay(300);

  chassis->setMaxVelocity(200);

  chassis->turnAngle(75_deg);

}

void testAuton(){

  flywheel.move_velocity(540);

  spinRoller(200);

  chassis->setMaxVelocity(200);

  chassis->moveDistance(0.3_ft);

  pros::delay(200);

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(88_deg);

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

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(-21.5_deg);

  index();

  pros::delay(1000);

  index();

  flywheel = 0;

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(65_deg);

  chassis->setMaxVelocity(500);

  profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {8.4_ft, 0_ft, 0_deg}}, "moveC");
  profileController->setTarget("moveC");
  profileController->waitUntilSettled();

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(-37_deg);

  chassis->setMaxVelocity(350);

  profileController->generatePath(
      {{0_ft, 0_ft, 0_deg}, {2_ft, 0_ft, 0_deg}}, "moveC");
  profileController->setTarget("moveC");
  profileController->waitUntilSettled();

  chassis->setMaxVelocity(200);
  
  chassis->turnAngle(-86_deg);

  pros::delay(200);

  chassis->moveDistance(-1.2_ft);

  spinRoller(300);

}