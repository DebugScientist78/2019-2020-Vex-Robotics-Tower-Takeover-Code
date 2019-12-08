#ifndef GLOBALS_HPP_
#define GlOBALS_HPP_
#include "main.h"
#include "controls.h"

/*static const int DRIVE_MAX_SPEED = 80;
static const int TURN_MAX_SPEED = 70;

static const int LIFT_MIN_SPEED = 30;
static const int LIFT_MAX_SPEED = 100;

static const int POT_MAX = 3340;
static const int POT_MIN = 1768;

static const int POT_AT_90 = 16000;
static const int POT_AT_45 = 8000;*/

/*extern SlewArgs *MySlewArgs_leftOne;
extern SlewArgs *MySlewArgs_leftTwo;
extern SlewArgs *MySlewArgs_rightOne;
extern SlewArgs *MySlewArgs_rightTwo;
extern SlewArgs *arm_Args;
extern SlewArgs *intakeRight_Args;
extern SlewArgs *intakeLeft_Args;
extern SlewArgs *tilter_Args;*/

  /*******************************************/
 /*   Motors and Sensor local Initlization  */
/*******************************************/

extern pros::Controller master;
extern pros::Motor leftFront;
extern pros::Motor leftBack;
extern pros::Motor rightFront;
extern pros::Motor rightBack;

extern pros::Motor intakeLeft;
extern pros::Motor intakeRight;

extern pros::Motor arm;
extern pros::Motor tilter;

extern pros::ADIGyro gyro;

extern pros::ADIPotentiometer pot;
extern pros::ADIDigitalIn liftBtn;

//void setup();

extern int autoMode;
extern int driveAccelCap;

extern bool intakeOn;
extern bool intakeInward;

extern bool driveRunning;
extern bool liftRunning;

#endif