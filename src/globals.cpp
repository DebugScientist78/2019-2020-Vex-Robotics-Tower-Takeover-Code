#include "main.h"
/*
SlewArgs *MySlewArgs_leftOne = new SlewArgs();
SlewArgs *MySlewArgs_leftTwo = new SlewArgs();
SlewArgs *MySlewArgs_rightOne = new SlewArgs();
SlewArgs *MySlewArgs_rightTwo = new SlewArgs();
SlewArgs *arm_Args = new SlewArgs();
SlewArgs *intakeRight_Args = new SlewArgs();
SlewArgs *intakeLeft_Args = new SlewArgs();
SlewArgs *tilter_Args = new SlewArgs();*/

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor leftFront(1,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
pros::Motor leftBack(2,MOTOR_GEARSET_18,false);
pros::Motor rightFront(3,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(4,MOTOR_GEARSET_18,true);

pros::Motor intakeLeft(5,MOTOR_GEARSET_36,false);
pros::Motor intakeRight(6,MOTOR_GEARSET_36,true);

pros::Motor arm(7,MOTOR_GEARSET_36,false,MOTOR_ENCODER_COUNTS);

pros::ADIGyro gyro(1,1);
pros::ADIPotentiometer pot(2);
pros::ADIDigitalIn liftBtn(3);

int autoMode;
int driveAccelCap = 0;

bool intakeOn = false;
bool intakeInward = true;
