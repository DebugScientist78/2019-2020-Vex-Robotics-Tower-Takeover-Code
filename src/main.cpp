#include "main.h"
#include "controls.h"
#include "globals.hpp"
#include "display.h"
#include "auto.hpp"

/*
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	intakeLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    intakeRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    pros::Motor leftFront(1,MOTOR_GEARSET_18,false,MOTOR_ENCODER_COUNTS);
	pros::Motor leftBack(2,MOTOR_GEARSET_18,false);
    pros::Motor rightFront(3,MOTOR_GEARSET_18,true,MOTOR_ENCODER_COUNTS);
	pros::Motor rightBack(4,MOTOR_GEARSET_18,true);

	pros::ADIGyro gyro(1,1);
	pros::delay(1300);

	pros::Motor intakeLeft(6,MOTOR_GEARSET_36,false);
	pros::Motor intakeRight(8,MOTOR_GEARSET_36,true);

	pros::Motor arm(7,MOTOR_GEARSET_36,false,MOTOR_ENCODER_COUNTS);
	arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	pros::ADIPotentiometer armPot(2);
	armPot.calibrate();

	pros::ADIDigitalIn liftBtn(3);
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
	//DisplaySetup();
}

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
	//DisplaySetup();
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
	Procedure();
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
	using namespace std;

	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor leftFront(1);
	pros::Motor leftBack(2);
	pros::Motor rightFront(3);
	pros::Motor rightBack(4);

	pros::Motor intakeLeft(5);
	pros::Motor intakeRight(6);

	pros::Motor arm(7);

	pros::ADIPotentiometer armPos(2);
	pros::ADIDigitalIn liftBtn(3);
	//pros::Motor tilter(8);

	bool at90 = true;

	leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

	intakeLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intakeRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	//uint32_t now = pros::millis();
	//pros::Task intakeTask(Intake,NULL,TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"intake Task");
	pros::Motor *driveArr[4] = {&leftFront,&rightFront,&leftBack,&rightBack};
	while (true) {
	
		if (master.get_digital(DIGITAL_R1) == 1 && master.get_digital(DIGITAL_R2) == 0) {
			//SetLiftPos(&arm,&armPos,POT_AT_90,LIFT_MAX_SPEED);
			if (!driveRunning) {
				liftRunning = true;
				if (!at90) {
					TareLift(&arm,&liftBtn);
					at90 = true;
				}
			}
		}
		else if (master.get_digital(DIGITAL_R2) == 1 && master.get_digital(DIGITAL_R1) == 0) {
			//SetLiftPos(&arm,&armPos,POT_AT_45,LIFT_MAX_SPEED);
			if (!driveRunning) {
				liftRunning = true;
				if (at90) {
					ReleaseLift(&arm,-2750);
					at90 = false;
				}
			}
		/*} else if (master.get_digital(DIGITAL_X) == 1 && master.get_digital(DIGITAL_R1) == 0 && master.get_digital(DIGITAL_R2) == 0) {
			if (!driveRunning) {
				liftRunning = true;
				MoveLift(&arm,-200);
			}*/
		} else {
			liftRunning =false;
		}
		ManualArm();

		/*MtrAccel(&leftFront,fwd+rot+side,false);
		MtrAccel(&rightFront,fwd-rot-side,false);
		MtrAccel(&leftBack,fwd+rot-side,false);
		MtrAccel(&rightBack,fwd-rot+side,false);
		leftFront.move(fwd+rot+side);
		rightFront.move(fwd-rot-side);
		leftBack.move(fwd+rot-side);
		rightBack.move(fwd-rot+side);*/

		Drive(driveArr,&master);

		Intake();

		pros::delay(10);
	}
	CleanPointers();
}
