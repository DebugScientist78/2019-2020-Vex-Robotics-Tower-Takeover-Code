#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

pros::Motor leftFront(1,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
pros::Motor leftBack(2,MOTOR_GEARSET_18,false);
pros::Motor rightFront(3,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(4,MOTOR_GEARSET_18,true);

pros::Motor intakeLeft(9,MOTOR_GEARSET_36,false);
pros::Motor intakeRight(8,MOTOR_GEARSET_36,true);

pros::Motor titler(11,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);

pros::Motor arm(7,MOTOR_GEARSET_36,false,MOTOR_ENCODER_COUNTS);

pros::ADIGyro gyro(1,1);
pros::ADIPotentiometer pot(2);
pros::ADIDigitalIn tilterBtn(3);
pros::ADIDigitalIn armBtn(4);

int autoMode = BLUE_LEFT_GOAL;
bool choosingAuto = true;
int driveAccelCap = 0;

bool intakeOn = false;
bool intakeInward = true;

bool driveRunning = false;
bool liftRunning = false;

bool at90 = true;
bool MASTER_OVERRIDE = false;