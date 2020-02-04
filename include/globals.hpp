#ifndef GLOBALS_HPP_
#define GlOBALS_HPP_

  /*******************************************/
 /*   Motors and Sensor local Initlization  */
/*******************************************/

extern pros::Controller master;
extern pros::Controller partner;

extern pros::Motor leftFront;
extern pros::Motor leftBack;
extern pros::Motor rightFront;
extern pros::Motor rightBack;

extern pros::Motor intakeLeft;
extern pros::Motor intakeRight;

extern pros::Motor titler;
extern pros::Motor arm;

extern pros::ADIGyro gyro;

extern pros::ADIPotentiometer pot;
extern pros::ADIDigitalIn tilterBtn;
extern pros::ADIDigitalIn armBtn;

//void setup();

extern int autoMode;
extern bool choosingAuto;
extern int driveAccelCap;

extern bool intakeOn;
extern bool intakeInward;

extern bool driveRunning;
extern bool liftRunning;

extern bool MASTER_OVERRIDE;
extern bool at90;

#endif