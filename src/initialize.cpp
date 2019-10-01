#include "main.h"
#include "auton.h"
#include "display.h"
#include "controls.h"

bool skillsOveride = false;

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		//pros::lcd::set_text(2, "I was pressed!");
		autoMode++;
	} else {
		//pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void nitialize() {
    pros::Motor leftOne(1,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);
    okapi::IntegratedEncoder leftEnc(leftOne);
	pros::Motor leftTwo(2,MOTOR_GEARSET_18,false);
    pros::Motor rightOne(3,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);
    okapi::IntegratedEncoder rightEnc(rightOne);
	pros::Motor rightTwo(4,MOTOR_GEARSET_18,false);

	pros::ADIGyro gyro(1);

	pros::Motor intakeLeft(5,false);
	pros::Motor intakeRight(6,false);

	pros::Motor arm(7,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);
	pros::Motor tilter(8,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);
	SlewArgs *MySlewArgs_leftOne = new SlewArgs();
    SlewArgs *MySlewArgs_leftTwo = new SlewArgs();
    SlewArgs *MySlewArgs_rightOne = new SlewArgs();
    SlewArgs *MySlewArgs_rightTwo = new SlewArgs();
    SlewArgs *arm_Args = new SlewArgs();
    SlewArgs *intakeRight_Args = new SlewArgs();
    SlewArgs *intakeLeft_Args = new SlewArgs();
    SlewArgs *tilter_Args = new SlewArgs();

    MySlewArgs_leftOne->motor = &leftOne;
    MySlewArgs_leftOne->motor = &leftOne;
    MySlewArgs_rightOne->motor = &rightOne;
    MySlewArgs_rightTwo->motor = &rightTwo;
    arm_Args->motor = &arm;
    intakeLeft_Args->motor = &intakeLeft;
    intakeRight_Args->motor = &intakeRight;
    tilter_Args->motor = &tilter;
	//TaskHandle Slew = taskCreate(SlewRate,TASK_STACK_DEPTH_DEFAULT,NULL,TASK_PRIORITY_DEFAULT);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void ddisabled() {
	
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void drcompetition_initialize() {
	DisplaySetup();
}
