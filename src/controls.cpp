#include "main.h"
#include "globals.hpp"
static const int increment = 20;
static const int delta_time = 20;

int SignOf(int x) {
    if (x>0) return 1;
    if (x<0) return -1;
    return 0;
}

bool IsJoystickActive() {
	if (master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_Y) > DEADBAND) {
		return true;
	} else if (master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_X) > DEADBAND) {
		return true;
	} else if (master.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_RIGHT_X) > DEADBAND) {
		return true;
	} else {
		return false;
	}
}

/*
The function iteratively accelerates the motor's speed to the requested speed
its done it incrments over delta_time ms, creating linear accleration 
Depending on if the bot is in driver or autonomous mode,
it will output voltage, or velocity
*/
void MtrAccel(pros::Motor* mtr,int speed, bool useVel) {
    using namespace std;
    double ratio;
    int deltaSpd;
    int currentSpd;
    int velIncrement;

    if (!useVel) {
        //driver setup
        double ratio = 127/mtr->get_voltage_limit();
        int currentSpd = int(round(mtr->get_voltage()*ratio));
        if(abs(speed - currentSpd) < increment) {mtr->move(speed);return;}
    } else {
        //auton setup
        if (mtr->get_gearing() == MOTOR_GEARSET_06) {
            velIncrement = 100;
        } else if (mtr->get_gearing() == MOTOR_GEARSET_18) {
            velIncrement = 33;
        } else {
            velIncrement = 17;
        }
        int currentSpd = int(round(mtr->get_actual_velocity()));
        if(abs(speed - currentSpd) < velIncrement) {mtr->move_velocity(speed);return;}
    }

    while (currentSpd != speed) {
        if (!useVel) {
            currentSpd = int(round(mtr->get_voltage()*ratio));
        } else {
            currentSpd = int(round(mtr->get_actual_velocity()));
        }
        if (DEBUG) cout << "current Speed of Motor: " << currentSpd << endl;
        deltaSpd = speed - currentSpd;
        if (abs(deltaSpd) > increment) {
            if (!useVel) {
                currentSpd += increment * SignOf(deltaSpd);
            } else {
                currentSpd += velIncrement * SignOf(deltaSpd);
            }
        } else {
            currentSpd = speed;
        }
        if (!useVel) {
            mtr->move(currentSpd);
        } else {
            mtr->move_velocity(currentSpd);
        }
        pros::delay(delta_time);
    }
    if (speed == 0) mtr->move_velocity(0);
}

/*void SetLiftPos(pros::Motor *mtr, pros::ADIPotentiometer* poti, int target, int speedMax) {
    using namespace std;

    uint32_t now = pros::millis();
    bool pass;
    bool gain;
    int deltaPos = 0;
    const double kP = 0.05;
    int currentPos = poti->get_value_calibrated_HR();

    if (currentPos == target) {
        pass = true;
    } else {
        MtrAccel(mtr,speedMax,true);
        pass = false;
        if (currentPos < target) {
            gain = true;
        } else {
            gain = false;
        }
    }
    while (!pass) {
        if (gain) {
            pass = (currentPos >= target);
        } else {
            pass = (currentPos <= target);
        }

        currentPos = poti->get_value_calibrated_HR();
        deltaPos = floor((target - currentPos)*kP);
        if (abs(deltaPos) > speedMax) deltaPos = speedMax*SignOf(deltaPos);
        if (abs(deltaPos) < LIFT_MIN_SPEED) deltaPos = LIFT_MIN_SPEED*SignOf(deltaPos);
        mtr->move(deltaPos);
        pros::Task::delay_until(&now,delta_time);
    }

    MtrAccel(mtr,0,true);
}*/

void Drive(pros::Motor *mtrs[4], pros::Controller *ctrlr) {
    using namespace std;
    //checks if the drive is active and if the lift is active, it will not move the drive
    if (liftRunning) {
        for (int i = 0; i < 4; i++) {
            mtrs[i]->move(0);
        }
        return;
    } 
    double start, end;
    start = mtrs[0]->get_position();

    int fwd, rot, side;
    int reqSpd[4];
    int actSpd[4];
    int deltaSpd[4];
    //pros::Motor *mtrs[4] = {&leftFront,&rightFront,&leftBack,&rightBack};
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    
    int left_y = ctrlr->get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_Y);
    int right_x = ctrlr->get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_RIGHT_X);

      /********************/
     /* Driver Controls  */
    /********************/
    if (LogSpeed(abs(left_y)) > DEADBAND && LogSpeed(abs(right_x)) < DEADBAND) {
        fwd = LogSpeed(left_y)*.8;
    } else {
        fwd = 0;
    }
    if (LogSpeed(abs(right_x)) > DEADBAND && LogSpeed(abs(left_y)) < DEADBAND) {
        rot = LogSpeed(right_x)*.7;
    }
    else {
        rot = 0;
    }
    reqSpd[0] = fwd+rot;
    reqSpd[1] = fwd-rot;
    reqSpd[2] = fwd+rot;
    reqSpd[3] = fwd-rot;

    for (int i = 0; i < 4; i++) {
        if (mtrs[i]->get_voltage() == 0) {
            driveRunning = false;
        } else {
            driveRunning = true;
        }
    }

    for (int i = 0; i < 4; i++) {
        actSpd[i] = round(mtrs[i]->get_voltage()*0.010583);
        deltaSpd[i] = reqSpd[i]-actSpd[i];
        if (abs(deltaSpd[i]) > 15) {
            actSpd[i] += 15 * SignOf(deltaSpd[i]);
        } else {
            actSpd[i] = reqSpd[i];
        }
        mtrs[i]->move(actSpd[i]);
        pros::delay(10);
    }
    end = mtrs[0]->get_position();
    master.print(0,0,"%d",round(end-start));
    pros::lcd::set_text(0,to_string(round(end-start)));
}

void TareArm(pros::Motor *mtr, pros::ADIDigitalIn *btn) {
    //MtrAccel(mtr,50,true);
    mtr->move_velocity(80);
    while (btn->get_value() == 0) {
        pros::delay(10);
    }
    //MtrAccel(mtr,0,true);
    mtr->move_velocity(0);
    mtr->tare_position();
}

void ReleaseArm(pros::Motor *mtr, int target) {
    //MtrAccel(mtr,LIFT_MAX_SPEED,true);
    mtr->move_absolute(target,-60);
    while (mtr->get_position() > target) {
        //std::cout << mtr->get_position() << std::endl;
        pros::delay(10);
    }
    return;
    //MtrAccel(mtr,0,true);
    //mtr->move_velocity(0);
}

void ManualArm() {
    if (!MASTER_OVERRIDE && partner.is_connected()) {
        if (partner.get_digital(DIGITAL_UP) == 1 && arm.get_position() > -2750) {
            arm.move_velocity(-30);
        }
        else if (partner.get_digital(DIGITAL_DOWN) ==1 && liftBtn.get_value() == 0) {
            arm.move_velocity(30);
        } else {
            arm.move_velocity(0);
        }
    } else {
        if (master.get_digital(DIGITAL_UP) == 1 && arm.get_position() > -2750) {
            arm.move_velocity(-30);
        }
        else if (master.get_digital(DIGITAL_DOWN) ==1 && liftBtn.get_value() == 0) {
            arm.move_velocity(30);
        } else {
            arm.move_velocity(0);
        }
    }
}

void Intake() {
    if (partner.is_connected() && !MASTER_OVERRIDE) {
        if (partner.get_digital(DIGITAL_L2) ==1 && partner.get_digital(DIGITAL_L1) ==0) {
            intakeLeft.move_velocity(-100);
            intakeRight.move_velocity(-100);
        }
        else if (partner.get_digital(DIGITAL_L1) ==1 && partner.get_digital(DIGITAL_L2) ==0) {
            intakeLeft.move_velocity(100);
            intakeRight.move_velocity(100);
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

void ManualLift() {
    lift.set_brake_mode(MOTOR_BRAKE_HOLD);
    if (partner.is_connected() && !MASTER_OVERRIDE) {
        if (partner.get_digital(DIGITAL_R1) == 1) {
            lift.move_velocity(80);
        } else if (partner.get_digital(DIGITAL_R2) == 1) {
            lift.move_velocity(-80);
        } else {
            lift.move_velocity(0);
        }
    } else {
        if (master.get_digital(DIGITAL_A) == 1) {
            lift.move_velocity(80);
        } else if (master.get_digital(DIGITAL_Y) == 1) {
            lift.move_velocity(-80);
        } else {
            lift.move_velocity(0);
        }
    }
}

void TareLift() {
    lift.move_velocity(-80);
    while(liftBtn.get_value() == 0) {
        pros::delay(10);
    }
    lift.move_velocity(0);
    lift.tare_position();
}

void SetLift(int position) {
    lift.move_absolute(position,60);
    while (lift.get_position() < position) {
        pros::delay(10);
    }
}