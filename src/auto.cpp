#include "main.h"
#include "globals.hpp"

//inches to one decimal place
int calculateDistance(double inches) {
    return std::round( (inches/driveCircumference) * ticksPerRev );
}

void driveAccel(int speed[4]) {
    int reqSpd[4];
    int actSpd[4];
    int deltaSpd[4];
    pros::Motor mtrs[4] = {leftFront,rightFront,leftBack,rightBack};
    reqSpd[0] = speed[0];
    reqSpd[1] = speed[1];
    reqSpd[2] = speed[2];
    reqSpd[3] = speed[3];

    for (int i = 0; i < 4; i++) {
        actSpd[i] = round(mtrs[i].get_actual_velocity());
        deltaSpd[i] = reqSpd[i] - actSpd[i];
        if (abs(deltaSpd[i]) > 20) {
            actSpd[i] += 20 * SignOf(deltaSpd[i]);
        } else {
            actSpd[i] = reqSpd[i];
        }
        mtrs[i].move_velocity(actSpd[i]);
        pros::delay(10);
    }
}

void pidStright(double distance, int speed) {
    using namespace std;

    leftFront.tare_position();
    rightFront.tare_position();
    leftBack.tare_position();
    rightBack.tare_position();

    //int spd[4] = {speed,speed,speed,speed};
    //driveAccel(spd);

    leftFront.move_absolute( calculateDistance(distance),speed);
    rightFront.move_absolute( calculateDistance(distance),speed);
    leftBack.move_absolute( calculateDistance(distance),speed);
    rightBack.move_absolute( calculateDistance(distance),speed);

    while(/*abs(leftFront.get_position()) < abs(distance) && abs(rightFront.get_position()) < abs(distance)
        && */abs(leftBack.get_position()) < calculateDistance(abs(distance)) && abs(rightBack.get_position()) < calculateDistance(abs(distance))) {
            /*if (abs(leftFront.get_position()) < abs(rightFront.get_position())) {
                rightFront.move_velocity(speed*.9);
                rightBack.move_velocity(speed*.9);
            } else if (abs(leftFront.get_position()) > abs(rightFront.get_position())) {
                leftFront.move_velocity(speed*.9);
                leftBack.move_velocity(speed*.9);
            }*/
            pros::delay(10);
        }
    
    //driveAccel(0);
}

void pidTurn(int degrees, int speed) {
    using namespace std;
    int error, prevError, integral, derivative,output = 0;
    double kP = 0.6;
    double kI = 0.0;
    double kD = 0.0;
    //int spd[4];
    gyro.reset();
    pros::delay(1300);

    if (SignOf(degrees) > 0) { 
        while ( gyro.get_value() < degrees) {
            error = degrees - gyro.get_value();
            //if (error < 40) error = 40;
            integral += error;
            if (error == 0 || error > degrees) {
                integral = 0;
            }
            derivative = error -prevError;
            output = error *kP + integral *kI + derivative *kD; 
            if (output > speed) output = speed;
            leftFront.move_velocity(output);
            rightFront.move_velocity(-output);
            leftBack.move_velocity(output);
            rightBack.move_velocity(-output);
            prevError = error;
            pros::delay(10);
        }
        /*
        spd[0] = 0;
        spd[1] = 0;
        spd[2] = 0;
        spd[3] = 0;
        driveAccel(spd);
        */
       leftFront.move_velocity(0);
       rightFront.move_velocity(0);
       leftBack.move_velocity(0);
       rightBack.move_velocity(0);

    } else if (SignOf(degrees) < 0) {
        /*spd[0] = -speed;
        spd[1] = speed;
        spd[2] = -speed;
        spd[3] = speed;
        driveAccel(spd);*/
        while ( gyro.get_value() > degrees) {
            error = abs(degrees - gyro.get_value());
            integral += error;
            if (error == 0 || error > abs(degrees)) {
                integral = 0;
            }
            derivative = error -prevError;
            output = error *kP + integral *kI + derivative *kD; 
            if (output > speed) output = speed;
            leftFront.move_velocity(-output);
            rightFront.move_velocity(output);
            leftBack.move_velocity(-output);
            rightBack.move_velocity(output);
            pros::delay(10);
        }
       leftFront.move_velocity(0);
       rightFront.move_velocity(0);
       leftBack.move_velocity(0);
       rightBack.move_velocity(0);
    }
}

void TurnIntakeON(bool inwards) {
    if (inwards) {
        intakeLeft.move_velocity(100);
        intakeRight.move_velocity(100);
    } else {
        intakeLeft.move_velocity(-100);
        intakeRight.move_velocity(-100);
    }
}

void TurnIntakeOFF() {
    intakeLeft.move_velocity(0);
    intakeRight.move_velocity(0);
}

void pidLift(double distance, int speed) {
    lift.tare_position();
    if (SignOf(distance) == 1){
        lift.move_absolute(calculateDistance(distance),speed);
        while (lift.get_target_position() > lift.get_position()) {
            pros::delay(10);
        }
    } else if (SignOf(distance) == -1) {
        lift.move_absolute(calculateDistance(distance),-speed);
        while (lift.get_target_position() < lift.get_position()) {
            pros::delay(10);
        }
    }
}