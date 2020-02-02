#include "main.h"
#include "globals.hpp"

void Blue_Left_Goal() {
    
}

void Procedure() {
    lift.set_brake_mode(MOTOR_BRAKE_HOLD);
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    int x,y;
    //ReleaseLift(&arm,-2750);
    //TareLift(&arm,&liftBtn);
    //TurnIntakeON(false);
    //pros::delay(1000);
    //TurnIntakeOFF();


    if (autoMode == BLUE_LEFT_GOAL) {
        //TurnIntakeON(true);
        //pros::delay(100);
        pidStright(-36,90);
        //TurnIntakeOFF();
        pidStright(24,90);

        
        /*pidTurn(900,80);
        pidStright(25,120);
        pidTurn(-900,80);

        ReleaseLift(&arm,-2000);
        pidStright(-y,120);
        TareLift(&arm,&liftBtn);*/
    } else if (autoMode == RED_RIGHT_GOAL) {
        TurnIntakeON(true);
        pidStright(x,120);
        TurnIntakeOFF();
        pidStright(-x,120);

        pidTurn(900,100);
        pidStright(y,120);
        ReleaseArm(-2000);
        pidStright(-y,120);
        TareArm();
    } else if (autoMode == BLUE_RIGHT_GOAL) {
        
    }
}