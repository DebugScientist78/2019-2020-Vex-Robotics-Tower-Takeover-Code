#include "main.h"
#include "controls.h"
#include "test.h"

void init() {
    pros::Motor leftOne(1);
    okapi::IntegratedEncoder leftEnc(leftOne);
    pros::Motor leftTwo(2);
    pros::Motor rightOne(3);
    okapi::IntegratedEncoder rightEnc(rightOne);
    pros::Motor rightTwo(4);

    pros::Motor leftArm(5);
    okapi::IntegratedEncoder leftArm_ENC(leftArm);
    pros::Motor rightArm(6);
    okapi::IntegratedEncoder rightArm_ENC(rightArm);
}

void pid_Drive_Test(int target_distance, bool foward, pros::Motor *motor) {
    okapi::IntegratedEncoder leftEnc(*motor);
    leftEnc.reset();

    int output = 0;
    int current_value = 0;
    int error = 0;
    int prev_error = 0;
    int intergral = 0;
    int derviative = 0;

    std::cout << kP_D_TEST << " "<< kI_D_TEST << " " << kD_D_TEST << std::endl;
    if (foward) {
        SlewRate(80,motor);
        while (leftEnc.get() < target_distance*.8 /*&& rightEnc.get() < target_distance*/) {
            std::cout << "enc: " << current_value << std::endl;
            //std::cout << "Encoder Right: " << rightEnc.get() << std::endl;
            current_value = std::abs(leftEnc.controllerGet()/*+rightEnc.get()/2*/);
            error = target_distance - current_value;
            intergral += error;
            if (error > target_distance) intergral = 0;
            if (intergral > 1000000000) intergral = 0;
            derviative = error - prev_error;
            prev_error = error;
            output = (error*kP_D_TEST) + (intergral*kI_D_TEST) + (derviative*kD_D_TEST);
            if (output > 80) output = 80;
            if (output < -80) output = -80;
            motor->move(output);
            //if(output > target_distance) output = target_distance;
            pros::delay(10);
        }
        SlewRate(0,motor);
        //StopMotor(&leftTwo);
        //StopMotor(&rightOne);
        //StopMotor(&rightTwo);
        std::cout << "Actual distance: " << leftEnc.get() << std::endl;
        std::cout << "Wanted distance: " << target_distance << std::endl;
        std::cout << "ERROR: " << leftEnc.get() - target_distance << std::endl;
    }
    else {}

}

void pid_Lift_Test(int target_change,bool gain, pros::Motor * left, pros::Motor * right, okapi::IntegratedEncoder leftEnc, okapi::IntegratedEncoder rightEnc) {
    leftEnc.reset();
    leftEnc.reset();
    int output = 0;
    int current_value = 0;
    int error = 0;
    int prev_error = 0;
    int intergral = 0;
    int derviative = 0;
    if (gain) {
        SlewRate(LIFT_MAX_SPEED,left);
        SlewRate(-LIFT_MAX_SPEED,right);
        while (leftEnc.controllerGet() < target_change && std::abs(rightEnc.controllerGet()) < target_change) {
            current_value = (leftEnc.controllerGet() + std::abs(rightEnc.controllerGet()))/2;
            error = target_change - current_value;
            intergral += error;
            if (intergral > target_change*1.2 || error > target_change) intergral = 0;
            derviative = error - prev_error;
            prev_error = error;
            output = error*kP_L_TEST + intergral*kI_L_TEST + derviative*kD_L_TEST;
            if (output > LIFT_MAX_SPEED) output = LIFT_MAX_SPEED;
            if (output < -LIFT_MAX_SPEED) output = -LIFT_MAX_SPEED;
            left->move(output);
            right->move(-output);
            pros::delay(10);
        }
    } else {
        SlewRate(-LIFT_MAX_SPEED,left);
        SlewRate(LIFT_MAX_SPEED,right);
        while (std::abs(leftEnc.controllerGet()) < target_change && rightEnc.controllerGet()) {
            current_value = (std::abs(leftEnc.controllerGet()) + rightEnc.controllerGet())/2;
            error = target_change - std::abs(current_value);
            intergral += error;
            if (intergral > target_change*1.2 || error > target_change) intergral = 0;
            derviative = error - prev_error;
            prev_error = error;
            output = error*kP_L_TEST + intergral*kI_L_TEST + derviative*kD_L_TEST;
            if (output > LIFT_MAX_SPEED) output = LIFT_MAX_SPEED;
            if (output < -LIFT_MAX_SPEED) output = -LIFT_MAX_SPEED;            
            left->move(-output);
            right->move(output);
            pros::delay(10);
        }
    }
    SlewRate(0,left);
    SlewRate(0,right);
    return;
}