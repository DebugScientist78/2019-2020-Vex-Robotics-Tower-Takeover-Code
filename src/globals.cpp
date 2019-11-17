#include "main.h"
#include "globals.hpp"
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
pros::Motor leftFront(1);
pros::Motor leftBack(2);
pros::Motor rightFront(3);
pros::Motor rightBack(4);

pros::Motor intakeLeft(5);
pros::Motor intakeRight(6);

pros::Motor arm(7);
pros::Motor tilter(8);

pros::ADIGyro gyro(1);
pros::ADIPotentiometer pot(2);

int autoMode;
