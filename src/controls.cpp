#include "main.h"
#include "globals.hpp"
static const int increment = 20;
static const int delta_time = 20;

int SignOf(int x) {
    if (x>0) return 1;
    if (x<0) return -1;
    return 0;
}

void Drive() {
    using namespace std;
    pros::Motor mtrs[4] = {leftFront,rightFront,leftBack,rightBack};
    //checks if the drive is active and if the lift is active, it will not move the drive
    if (liftRunning) {
        for (int i = 0; i < 4; i++) {
            mtrs[i].move(0);
        }
        return;
    } 
    //double start, end;
    //start = mtrs[0].get_position();

    int fwd, rot, side;
    int accel_Speed;
    int reqSpd[4];
    int actSpd[4];
    int deltaSpd[4];
    //pros::Motor *mtrs[4] = {&leftFront,&rightFront,&leftBack,&rightBack};
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    
    int left_y = master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_Y);
    int right_x = master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_RIGHT_X);

      /********************/
     /* Driver Controls  */
    /********************/
    if (LogSpeed(abs(left_y)) > DEADBAND && LogSpeed(abs(right_x)) < DEADBAND) {
        fwd = LogSpeed(left_y)*.8;
        accel_Speed = 20;
    } else {
        fwd = 0;
    }
    if (LogSpeed(abs(right_x)) > DEADBAND && LogSpeed(abs(left_y)) < DEADBAND) {
        rot = LogSpeed(right_x)*.6;
        accel_Speed = 10;
    }
    else {
        rot = 0;
    }
    reqSpd[0] = fwd+rot;
    reqSpd[1] = fwd-rot;
    reqSpd[2] = fwd+rot;
    reqSpd[3] = fwd-rot;

    for (int i = 0; i < 4; i++) {
        if (mtrs[i].get_voltage() == 0) {
            driveRunning = false;
        } else {
            driveRunning = true;
        }
    }

    for (int i = 0; i < 4; i++) {
        actSpd[i] = round(mtrs[i].get_voltage()*0.010583);
        deltaSpd[i] = reqSpd[i]-actSpd[i];
        if (abs(deltaSpd[i]) > accel_Speed) {
            actSpd[i] += accel_Speed * SignOf(deltaSpd[i]);
        } else {
            actSpd[i] = reqSpd[i];
        }
        mtrs[i].move(actSpd[i]);
        pros::delay(10);
    }
    //end = mtrs[0].get_position();
    //master.print(0,0,"%d",round(end-start));
   // pros::lcd::set_text(0,to_string(round(end-start)));
}

void TareTilter() {
    //MtrAccel(mtr,50,true);
    titler.move_velocity(100);
    while (tilterBtn.get_value() == 0) {
        pros::delay(10);
    }
    //MtrAccel(mtr,0,true);
    titler.move_velocity(0);
    titler.tare_position();
}

void ReleaseTilter(int target) {
    //MtrAccel(mtr,LIFT_MAX_SPEED,true);
    if (target > titler.get_position()) {
        titler.move_absolute(target,60);
        while (titler.get_position() < target) {
            pros::delay(10);
        }
    } else if (target < titler.get_position()) {
        titler.move_absolute(target,-60);
        while (titler.get_position() > target) {
            //std::cout << mtr->get_position() << std::endl;
            pros::delay(10);
        }
    }
    return;
    //MtrAccel(mtr,0,true);
    //mtr->move_velocity(0);
}

void ManualTilter() {
    if (master.get_digital(DIGITAL_R2) == 1) {
        arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
        titler.move_velocity(-100);
    }
    else if (master.get_digital(DIGITAL_R1) ==1) {
        arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
        titler.move_velocity(100);
    } else {
        arm.set_brake_mode(MOTOR_BRAKE_HOLD);
        titler.move_velocity(0);
    }
}

void Intake() {
    //std::cout << (partner.is_connected() && !MASTER_OVERRIDE) << std::endl;
    if (partner.is_connected()) {
        if (partner.get_digital(DIGITAL_L2) ==1 && partner.get_digital(DIGITAL_L1) ==0) {
            intakeLeft.move_velocity(-200);
            intakeRight.move_velocity(-200);
        }
        else if (partner.get_digital(DIGITAL_L1) ==1 && partner.get_digital(DIGITAL_L2) ==0) {
            intakeLeft.move_velocity(200);
            intakeRight.move_velocity(200);
        }
        else if (master.get_digital(DIGITAL_L2) ==1) {
            intakeLeft.move_velocity(-40);
            intakeRight.move_velocity(-40);
        } else {
            intakeLeft.move_velocity(0);
            intakeRight.move_velocity(0);
        }
    } else {
        if (master.get_digital(DIGITAL_L2) ==1 && master.get_digital(DIGITAL_L1) ==0) {
            intakeLeft.move_velocity(-100);
            intakeRight.move_velocity(-100);
        }
        else if (master.get_digital(DIGITAL_L1) ==1 && master.get_digital(DIGITAL_L2) ==0) {
            intakeLeft.move_velocity(100);
            intakeRight.move_velocity(100);
        } else {
            intakeLeft.move_velocity(0);
            intakeRight.move_velocity(0);
        }
    }
}

int LogSpeed(int rawSpeed) {
    return (rawSpeed*rawSpeed) / (127*SignOf(rawSpeed));
}

void ManualArm() {
    if (partner.is_connected()) {
        if (partner.get_digital(DIGITAL_R1) == 1) {
            titler.move_velocity(100);
            arm.move_velocity(80);
        } else if (partner.get_digital(DIGITAL_R2) == 1) {
            titler.move_velocity(-100);
            arm.move_velocity(-80);
        } else {
            arm.move_velocity(0);
        }
    } else {
        if (master.get_digital(DIGITAL_A) == 1) {
            titler.set_brake_mode(MOTOR_BRAKE_BRAKE);
            titler.move_velocity(80);
            arm.move_velocity(100);
        } else if (master.get_digital(DIGITAL_Y) == 1) {
            titler.set_brake_mode(MOTOR_BRAKE_BRAKE);
            titler.move_velocity(-80);
            arm.move_velocity(-100);
        } else {
            titler.set_brake_mode(MOTOR_BRAKE_HOLD);
            arm.move_velocity(0);
        }
    }
}

void TareArm() {
    arm.move_velocity(-80);
    while(armBtn.get_value() == 0) {
        pros::delay(10);
    }
    arm.move_velocity(0);
    arm.tare_position();
}

void SetArm(int position) {
    if (position > arm.get_position()) {
        arm.move_absolute(position,60);
        while (arm.get_position() < position) {
            pros::delay(10);
        }
    } else if (position < arm.get_position()) {
        arm.move_absolute(position,-60);
        while (arm.get_position() > position) {
            pros::delay(10);
        }
    }
}

void TilterSystem() {
    //Main controller will be used when override is off and/or when the controller is not connect
    if (MASTER_OVERRIDE || !partner.is_connected()) {
        if (master.get_digital(DIGITAL_R1) == 1 && master.get_digital(DIGITAL_R2) == 0) {
            //SetLiftPos(&arm,&armPos,POT_AT_90,LIFT_MAX_SPEED);
            arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
            if (!driveRunning) {
                liftRunning = true;
                if (!at90) {
                    TareTilter();
                    at90 = true;
                }
            }
        }
        /*else if (master.get_digital(DIGITAL_R2) == 1 && master.get_digital(DIGITAL_R1) == 0) {
            //SetLiftPos(&arm,&armPos,POT_AT_45,LIFT_MAX_SPEED);
            arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
            if (!driveRunning) {
                liftRunning = true;
                if (at90) {
                    ReleaseTilter(-2750);
                    at90 = false;
                }
            }*/
        /*} else if (master.get_digital(DIGITAL_X) == 1 && master.get_digital(DIGITAL_R1) == 0 && master.get_digital(DIGITAL_R2) == 0) {
            if (!driveRunning) {
                liftRunning = true;
                MoveLift(&arm,-200);
            }
        }*/ else {
            liftRunning =false;
        }
    //partner controls
    } else {
        if (partner.get_digital(DIGITAL_R1) == 1 && partner.get_digital(DIGITAL_R2) == 0) {
            //SetLiftPos(&arm,&armPos,POT_AT_90,LIFT_MAX_SPEED);
            arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
            if (!driveRunning) {
                liftRunning = true;
                if (!at90) {
                    TareArm();
                    at90 = true;
                }
            }
        }
        /*else if (partner.get_digital(DIGITAL_R2) == 1 && partner.get_digital(DIGITAL_R1) == 0) {
            //SetLiftPos(&arm,&armPos,POT_AT_45,LIFT_MAX_SPEED);
            arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
            if (!driveRunning) {
                liftRunning = true;
                if (at90) {
                    ReleaseTilter(-2750);
                    at90 = false;
                }
            }
        /*} else if (master.get_digital(DIGITAL_X) == 1 && master.get_digital(DIGITAL_R1) == 0 && master.get_digital(DIGITAL_R2) == 0) {
            if (!driveRunning) {
                liftRunning = true;
                MoveLift(&arm,-200);
            }*/
         else {
            liftRunning =false;
        }
    }
    ManualTilter();
}

void ArmSystem() {
    //main controls
    if (MASTER_OVERRIDE || !partner.is_connected()) {
        if (master.get_digital(DIGITAL_A) == 1 && master.get_digital(DIGITAL_Y) == 0) {
            //reset lift
            TareArm();
        //} else if (master.get_digital(DIGITAL_Y) == 1 && master.get_digital(DIGITAL_A) == 0) {
          //  SetArm(400);
        } 
    }
    //partner controls 
    else {
        if (partner.get_digital(DIGITAL_L1) == 1 && partner.get_digital(DIGITAL_L2) == 0) {
            //reset lift
            TareArm();
        } //else if (partner.get_digital(DIGITAL_L2) == 1 && partner.get_digital(DIGITAL_L2) == 0) {
           // SetArm(400);
        //}
    }
    ManualArm();
}

void masterSwitch() {
    if (master.get_digital(DIGITAL_A) == 1 && master.get_digital(DIGITAL_B) == 1 && master.get_digital(DIGITAL_X) == 1 && master.get_digital(DIGITAL_Y) == 1) {
        MASTER_OVERRIDE = !MASTER_OVERRIDE;
        //std::cout << "y" << std::endl;
    }
}