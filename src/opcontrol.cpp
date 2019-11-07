#include "main.h"
#include "controls.h"
#include "display.h"
#include "test.h"

uint8_t prevTime;

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


void Maincontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor leftOne(1);
	pros::Motor leftTwo(2);
	pros::Motor rightOne(3);
	pros::Motor rightTwo(4);

	pros::Motor intakeLeft(5);
	pros::Motor intakeRight(6);

	pros::Motor arm(7);
	pros::Motor tilter(8);

	int left_y = 0;
	int left_x = 0;
	int right_x = 0;

	SlewArgs *MySlewArgs_leftOne = new SlewArgs();
	SlewArgs *MySlewArgs_leftTwo = new SlewArgs();
	SlewArgs *MySlewArgs_rightOne = new SlewArgs();
	SlewArgs *MySlewArgs_rightTwo = new SlewArgs();
	SlewArgs *arm_Args = new SlewArgs();
	SlewArgs *intakeRight_Args = new SlewArgs();
	SlewArgs *intakeLeft_Args = new SlewArgs();
	SlewArgs *tilter_Args = new SlewArgs();

	lcdArgs *MyLcdArgs = new lcdArgs();
	MyLcdArgs->ctrlr = &master;

	MySlewArgs_leftOne->motor = &leftOne;
	MySlewArgs_leftOne->motor = &leftOne;
	MySlewArgs_rightOne->motor = &rightOne;
	MySlewArgs_rightTwo->motor = &rightTwo;
	arm_Args->motor = &arm;
	intakeLeft_Args->motor = &intakeLeft;
	intakeRight_Args->motor = &intakeRight;
	tilter_Args->motor = &tilter;

	while (true) {
		left_y = master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_Y);
		left_x = master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_X);

		right_x = master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_RIGHT_X);
		pros::Task SlewLeftOne(TaskSlew,(void*)MySlewArgs_leftOne,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"SlewLeftOne");
		pros::Task SlewLeftTwo(TaskSlew,(void*)MySlewArgs_leftTwo,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"SlewLeftTwo");
		pros::Task SlewRightOne(TaskSlew,(void*)MySlewArgs_rightOne,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"SlewRightOne");
		pros::Task SlewRightTwo(TaskSlew,(void*)MySlewArgs_rightTwo,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"SlewRightTwo");
		pros::Task SlewArm(TaskSlew,(void*)arm_Args,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"Arm task");
		pros::Task SlewIntakeLeft(TaskSlew,(void*)intakeLeft_Args,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"Left Intake Slew");
		pros::Task SlewIntakeRight(TaskSlew,(void*)intakeRight_Args,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"Right Intake Slew");
		//pros::Task SlewAdjust(TaskUpdate,(void*)tilter_Args,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"Tilter Slew");

		//std::cout << "analog right x axis: " << right << std::endl;
		
		  /********************/
		 /* Driver Contorls  */
		/********************/
		if (std::abs(left_y) > DEADBAND && std::abs(right_x) < DEADBAND && std::abs(left_x < DEADBAND)) {
			MySlewArgs_leftOne->target = left_y;
			MySlewArgs_leftTwo->target = left_y;
			MySlewArgs_rightOne->target = -left_y;
			MySlewArgs_rightTwo->target = -left_y;
		}
		else if (std::abs(left_x) > DEADBAND && std::abs(left_y) < DEADBAND && std::abs(right_x) < DEADBAND) {
			MySlewArgs_leftOne->target = left_x;
			MySlewArgs_leftTwo->target = -left_x;
			MySlewArgs_rightOne->target = -left_x;
			MySlewArgs_rightTwo->target = left_x;
		}
		else if (std::abs(right_x) > DEADBAND && std::abs(left_x) < DEADBAND && std::abs(left_y) < DEADBAND) {
			MySlewArgs_leftOne->target = -right_x;
			MySlewArgs_leftTwo->target = -right_x;
			MySlewArgs_rightOne->target = right_x;
			MySlewArgs_rightTwo->target = right_x;
		}
		else {
			MySlewArgs_leftOne->target = 0;
			MySlewArgs_leftTwo->target = 0;
			MySlewArgs_rightOne->target = 0;
			MySlewArgs_rightTwo->target = 0;
		}
	
		if (master.get_digital(DIGITAL_R1) == 1 && master.get_digital(DIGITAL_R2) == 0) {
			prevTime = pros::millis();
			arm_Args->target = 127;

		}
		else if (master.get_digital(DIGITAL_R2) == 1 && master.get_digital(DIGITAL_R1) == 0) {
			arm_Args->target = -127;
		}
		else {
			arm_Args->target = 0;
		}

		if (master.get_digital(DIGITAL_L1) ==1 && master.get_digital(DIGITAL_L2) ==0) {
			tilter_Args->target = 127;
		}
		else if (master.get_digital(DIGITAL_L2) ==1 && master.get_digital(DIGITAL_L1) ==0) {
			tilter_Args->target = -127;
		}
		else {
			tilter_Args->target = 0;
		}
		MyLcdArgs->input = "JIM";
		pros::delay(25);
	}
}
