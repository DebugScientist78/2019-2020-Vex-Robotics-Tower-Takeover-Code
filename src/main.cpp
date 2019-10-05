#include "main.h"
#include "controls.h"
#include "display.h"

/*
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::Motor leftOne(1,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);
    okapi::IntegratedEncoder leftEnc(leftOne);
	pros::Motor leftTwo(2,MOTOR_GEARSET_18,false);
    pros::Motor rightOne(3,MOTOR_GEARSET_18,true,MOTOR_ENCODER_COUNTS);
    okapi::IntegratedEncoder rightEnc(rightOne);
	pros::Motor rightTwo(4,MOTOR_GEARSET_18,true);

	pros::ADIGyro gyro(1);

	pros::Motor intakeLeft(5,false);
	pros::Motor intakeRight(6,false);

	pros::Motor arm(7,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);
	//pros::Motor tilter(8,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);
	//DisplaySetup();
	/*SlewArgs *MySlewArgs_leftOne = new SlewArgs();
	SlewArgs *MySlewArgs_leftTwo = new SlewArgs();
	SlewArgs *MySlewArgs_rightOne = new SlewArgs();
	SlewArgs *MySlewArgs_rightTwo = new SlewArgs();
	SlewArgs *arm_Args = new SlewArgs();
	SlewArgs *intakeRight_Args = new SlewArgs();
	SlewArgs *intakeLeft_Args = new SlewArgs();
	//SlewArgs *tilter_Args = new SlewArgs();

	MySlewArgs_leftOne->motor = &leftOne;
	MySlewArgs_leftTwo->motor = &leftTwo;
	MySlewArgs_rightOne->motor = &rightOne;
	MySlewArgs_rightTwo->motor = &rightTwo;
	arm_Args->motor = &arm;
	intakeLeft_Args->motor = &intakeLeft;
	intakeRight_Args->motor = &intakeRight;
	pros::Task SlewLeftOne(TaskSlew,(void*)MySlewArgs_leftOne,"SlewLeftOne");
	pros::Task SlewLeftTwo(TaskSlew,(void*)MySlewArgs_leftTwo,"SlewLeftTwo");
	pros::Task SlewRightOne(TaskSlew,(void*)MySlewArgs_rightOne,"SlewRightOne");
	pros::Task SlewRightTwo(TaskSlew,(void*)MySlewArgs_rightTwo,"SlewRightTwo");*/
}


// haha ver foony

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	DisplaySetup();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	Routine();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor leftOne(1);
	pros::Motor leftTwo(2);
	pros::Motor rightOne(3);
	pros::Motor rightTwo(4);

	pros::Motor intakeLeft(5);
	pros::Motor intakeRight(6);

	pros::Motor arm(7);
	//pros::Motor tilter(8);

	int left_y, left_x, right_x, fwd, rot, side;

	SlewArgs *MySlewArgs_leftOne = new SlewArgs();
	SlewArgs *MySlewArgs_leftTwo = new SlewArgs();
	SlewArgs *MySlewArgs_rightOne = new SlewArgs();
	SlewArgs *MySlewArgs_rightTwo = new SlewArgs();
	SlewArgs *arm_Args = new SlewArgs();
	SlewArgs *intakeRight_Args = new SlewArgs();
	SlewArgs *intakeLeft_Args = new SlewArgs();
	//SlewArgs *tilter_Args = new SlewArgs();

	MySlewArgs_leftOne->motor = &leftOne;
	MySlewArgs_leftTwo->motor = &leftTwo;
	MySlewArgs_rightOne->motor = &rightOne;
	MySlewArgs_rightTwo->motor = &rightTwo;
	arm_Args->motor = &arm;
	intakeLeft_Args->motor = &intakeLeft;
	intakeRight_Args->motor = &intakeRight;
	//tilter_Args->motor = &tilter;

	while (true) {
		left_y = master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_Y);
		left_x = master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_X);

		right_x = master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_RIGHT_X);
		//pros::Task SlewLeftOne(TaskSlew,(void*)MySlewArgs_leftOne,"SlewLeftOne");
		//pros::Task SlewLeftTwo(TaskSlew,(void*)MySlewArgs_leftTwo,"SlewLeftTwo");
		//pros::Task SlewRightOne(TaskSlew,(void*)MySlewArgs_rightOne,"SlewRightOne");
		//pros::Task SlewRightTwo(TaskSlew,(void*)MySlewArgs_rightTwo,"SlewRightTwo");
		//pros::Task SlewArm(TaskSlew,(void*)arm_Args,"Arm task");
		//pros::Task SlewIntakeLeft(TaskSlew,(void*)intakeLeft_Args,"Left Intake Slew");
		//pros::Task SlewIntakeRight(TaskSlew,(void*)intakeRight_Args,"Right Intake Slew");
		//pros::Task SlewAdjust(TaskUpdate,(void*)tilter_Args,"Tilter Slew");

		//std::cout << "analog right x axis: " << right << std::endl;
		
		  /********************/
		 /* Driver Contorls  */
		/********************/
		if (std::abs(left_y) > DEADBAND && std::abs(right_x) < DEADBAND && std::abs(left_x < DEADBAND)) {
			fwd = left_y;
		} else {
			fwd = 0;
		}
		if (std::abs(left_x) > DEADBAND && std::abs(left_y) < DEADBAND && std::abs(right_x) < DEADBAND) {
			side = left_x;
		} else {
			side = 0;
		}
		if (std::abs(right_x) > DEADBAND && std::abs(left_x) < DEADBAND && std::abs(left_y) < DEADBAND) {
			rot = right_x;
		}
		else {
			rot = 0;
		}
	
		/*if (master.get_digital(DIGITAL_R1) == 1 && master.get_digital(DIGITAL_R2) == 0) {
			prevTime = pros::millis();
			arm_Args->target = 127;

		}
		else if (master.get_digital(DIGITAL_R2) == 1 && master.get_digital(DIGITAL_R1) == 0) {
			arm_Args->target = -127;
		}
		else {
			arm_Args->target = 0;
		}*/

		/*if (master.get_digital(DIGITAL_L1) ==1 && master.get_digital(DIGITAL_L2) ==0) {
			tilter_Args->target = 127;
		}
		else if (master.get_digital(DIGITAL_L2) ==1 && master.get_digital(DIGITAL_L1) ==0) {
			tilter_Args->target = -127;
		}
		else {
			tilter_Args->target = 0;
		}*/
		SlewRate(fwd+rot-side,&leftOne);
		SlewRate(fwd-rot+side,&rightOne);
		SlewRate(fwd+rot+side,&leftTwo);
		SlewRate(fwd-rot-side,&rightTwo);
		pros::delay(10);
	}
}