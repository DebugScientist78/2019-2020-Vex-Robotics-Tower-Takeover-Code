#include "main.h"
#include "globals.hpp"


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
void Routine() {
    using namespace okapi;
    
    pros::Motor leftOne(1);
    okapi::IntegratedEncoder leftEnc(leftOne);
    pros::Motor leftTwo(2);
    pros::Motor rightOne(3);
    okapi::IntegratedEncoder rightEnc(rightOne);
    pros::Motor rightTwo(4);

    pros::Motor arm(7);
    okapi::IntegratedEncoder armENC(arm);

    pros::Motor intakeLeft(5);
    pros::Motor intakeRight(6);

    pros::Motor tilter(8);
    pros::ADIGyro gyro(1);
/*
    void pid_Drive(int target_distance, bool foward) {
        int output = 0;
        int current_value = 0;
        int error = 0;
        int prev_error = 0;
        int intergral = 0;
        int derviative = 0;

        if (foward) {
                SlewRate(DRIVE_MAX_SPEED,&leftOne);
                SlewRate(-DRIVE_MAX_SPEED,&rightOne);
            while (leftEnc.get() < target_distance*.8 && std::abs(rightEnc.get() < target_distance*.8)) {
                current_value = (leftEnc.get()+std::abs(rightEnc.get()))/2;
                error = target_distance - current_value;
                intergral += error;
                if (intergral > target_distance*1.2 || error > target_distance) intergral = 0;
                derviative = error - prev_error;
                prev_error = error;
                output = error*kP_D + intergral*kI_D + derviative*kD_D;
                if (output > DRIVE_MAX_SPEED) output = DRIVE_MAX_SPEED;
                if (output < -DRIVE_MAX_SPEED) output = -DRIVE_MAX_SPEED;
                leftOne.move(output);
                rightOne.move(-output);
                pros::delay(10);
            }
        }
        else {
            SlewRate(-DRIVE_MAX_SPEED,&leftOne);
            SlewRate(-DRIVE_MAX_SPEED,&leftTwo);
            SlewRate(DRIVE_MAX_SPEED,&rightOne);
            SlewRate(DRIVE_MAX_SPEED,&rightTwo);
            while (std::abs(leftEnc.get()) < target_distance && rightEnc.get() < target_distance) {
                current_value = (std::abs(leftEnc.controllerGet()) + rightEnc.controllerGet())/2;
                error = target_distance - current_value;
                intergral += error;
                if (intergral > target_distance*1.2 || error > target_distance) intergral = 0;
                derviative = error - prev_error;
                prev_error = error;
                output = error*kP_D + intergral*kI_D + derviative*kD_D;
                if (output > DRIVE_MAX_SPEED) output = DRIVE_MAX_SPEED;
                if (output < -DRIVE_MAX_SPEED) output = -DRIVE_MAX_SPEED;
                leftOne.move(-output);
                leftTwo.move(-output);
                rightOne.move(output);
                rightTwo.move(output); 
                pros::delay(10);
            }
        }
        SlewRate(0,&leftOne);
        SlewRate(0,&leftTwo);
        SlewRate(0,&rightOne);
        SlewRate(0,&rightTwo);
        return;
    }
    void pid_Lift(int target_change,bool gain) {
        armENC.reset();
        int output = 0;
        int current_value = 0;
        int error = 0;
        int prev_error = 0;
        int intergral = 0;
        int derviative = 0;
        if (gain) {
            SlewRate(LIFT_MAX_SPEED,&arm);
            while (armENC.controllerGet() < target_change) {
                current_value = armENC.controllerGet();
                error = target_change - current_value;
                intergral += error;
                if (intergral > target_change*1.2 || error > target_change) intergral = 0;
                derviative = error - prev_error;
                prev_error = error;
                output = error*kP_L + intergral*kI_L + derviative*kD_L;
                if (output > LIFT_MAX_SPEED) output = LIFT_MAX_SPEED;
                if (output < -LIFT_MAX_SPEED) output = -LIFT_MAX_SPEED;
                arm.move(output);
                pros::delay(10);
            }
        } else {
            SlewRate(-LIFT_MAX_SPEED,&arm);
            while (std::abs(armENC.controllerGet()) < target_change) {
                current_value = std::abs(armENC.controllerGet());
                error = target_change - std::abs(current_value);
                intergral += error;
                if (intergral > target_change*1.2 || error > target_change) intergral = 0;
                derviative = error - prev_error;
                prev_error = error;
                output = error*kP_L + intergral*kI_L + derviative*kD_L;
                if (output > LIFT_MAX_SPEED) output = LIFT_MAX_SPEED;
                if (output < -LIFT_MAX_SPEED) output = -LIFT_MAX_SPEED;            
                arm.move(-output);
                pros::delay(10);
            }
        }
        SlewRate(0,&arm);
        return;
    }

    void pid_Turn(int degrees) {
        gyro.reset();
        int output = 0;
        int current_value = 0;
        int error = 0;
        int prev_error = 0;
        int intergral = 0;
        int derviative = 0;
        //check if cw
        if (degrees > 0) {
            SlewRate(TURN_MAX_SPEED,&leftOne);
            SlewRate(TURN_MAX_SPEED,&leftTwo);
            SlewRate(TURN_MAX_SPEED,&rightOne);
            SlewRate(TURN_MAX_SPEED,&rightTwo);
            while (gyro.get_value()/10 < degrees*.9) {
                current_value = gyro.get_value()/10;
                error = degrees - current_value;
                intergral += error;
                if (intergral > degrees*1.2 || error > degrees) intergral = 0;
                derviative = error - prev_error;
                prev_error = error;
                output = error*kP_T + intergral*kI_T + derviative*kD_T;
                if (output > TURN_MAX_SPEED) output = TURN_MAX_SPEED;
                if (output < -TURN_MAX_SPEED) output = -TURN_MAX_SPEED;
                leftOne.move(output);
                leftTwo.move(output);
                rightOne.move(output);
                rightTwo.move(output); 
                pros::delay(10);
            }
        }
        //ccw
        else {
            SlewRate(-TURN_MAX_SPEED,&leftOne);
            SlewRate(-TURN_MAX_SPEED,&leftTwo);
            SlewRate(-TURN_MAX_SPEED,&rightOne);
            SlewRate(-TURN_MAX_SPEED,&rightTwo);
            while (gyro.get_value()/10 > degrees*.9) {
                current_value = gyro.get_value()/10;
                error = degrees - current_value;
                intergral += error;
                if (intergral < degrees*1.2 || error < degrees) intergral = 0;
                derviative = error - prev_error;
                prev_error = error;
                output = error*kP_T + intergral*kI_T + derviative*kD_T;
                if (output > TURN_MAX_SPEED) output = TURN_MAX_SPEED;
                if (output < -TURN_MAX_SPEED) output = -TURN_MAX_SPEED;
                leftOne.move(-output);
                leftTwo.move(-output);
                rightOne.move(-output);
                rightTwo.move(-output); 
                pros::delay(10);
            }
        }
        SlewRate(0,&leftOne);
        SlewRate(0,&leftTwo);
        SlewRate(0,&rightOne);
        SlewRate(0,&rightTwo);
    }

    void pid_strafe(int targetDistance, bool rightDir) {
        if (rightDir) {

        } else {
            
        }
    } */

    leftOne.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	leftTwo.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rightOne.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rightTwo.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

	intakeLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    auto intake = AsyncControllerFactory::velIntegrated({6,-7});
    auto drive = okapi::ChassisControllerFactory::create(
                                                    {1,2},
                                                    {-3,-4},
                                                    okapi::AbstractMotor::gearset::green,
                                                    {4_in,8.5_in});
    
    auto adjuster = okapi::AsyncControllerFactory::posIntegrated(7);

    if (autoMode == 1) {
        intake.setTarget(1000);
        drive.moveDistance(1_ft);
        intake.waitUntilSettled();
        drive.turnAngle(90_deg);
    
    } else if (autoMode == 2) {

    } else if (autoMode == 3) {

    } else if (autoMode == 4) {

    } else {

    }
    return;
}
