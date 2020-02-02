#include "main.h"
#include "globals.hpp"

Odom::Odom(bool isRed) {
    relative_angle = 0;
    relative_x = 0;
    relative_y = 0;
    x_axisOpen = true;
    onRed = isRed;
}

void Odom::FlipOut() {
    lift.move_absolute(100,50);
    pros::delay(100);
    lift.move_absolute(-100,-50);
}

int Odom::getAngle() {
    return relative_angle;
}

int Odom::getXposition(void) {
    return relative_x;
}

int Odom::getYposition(void) {
    return relative_y;
}

//movement functionss

void Odom::ResetPosition(void) {
    relative_x = 0;
    relative_y = 0;
}

void Odom::Turn(int degrees, int speed) {
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

    relative_angle = degrees;
    if (onRed) {
        if (degrees == 900) {
            x_axisOpen = false;
            goingPositive = false;
        }
        else if (degrees = 2700) {
            x_axisOpen = false;
            goingPositive = true;
        }
    } else {
        if (degrees == 900) {
            x_axisOpen = false;
            goingPositive = true;
        }
        else if (degrees = 2700) {
            x_axisOpen = false;
            goingPositive = false;
        }
    }
}

void Odom::MoveX(int distance_relative, int speed) {
    if (!x_axisOpen) return;
    if (SignOf(distance_relative) == 1) {
        relative_x += distance_relative;
    } else if (SignOf(distance_relative) == -1) {
        relative_x -= distance_relative;
    }
    leftFront.tare_position();
    rightFront.tare_position();
    leftBack.tare_position();
    rightBack.tare_position();

    leftFront.move_absolute( calculateDistance(distance_relative),speed);
    rightFront.move_absolute( calculateDistance(distance_relative),speed);
    leftBack.move_absolute( calculateDistance(distance_relative),speed);
    rightBack.move_absolute( calculateDistance(distance_relative),speed);
}
