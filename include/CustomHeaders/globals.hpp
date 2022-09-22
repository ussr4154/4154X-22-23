#include "main.h"

//Motors
extern pros::Motor frontLeft;
extern pros::Motor frontRight;
extern pros::Motor middleLeft;
extern pros::Motor middleRight;
extern pros::Motor backLeft;
extern pros::Motor backRight;
extern pros::Motor flywheel;
extern pros::Motor intake;


//Controller
extern pros::Controller controller;

//Sensors & Pistons
extern pros::ADIDigitalOut leftFlywheel;
extern pros::ADIDigitalOut rightFlywheel;
extern pros::ADIDigitalOut expansion;

//Global Variables
extern bool highAngle;