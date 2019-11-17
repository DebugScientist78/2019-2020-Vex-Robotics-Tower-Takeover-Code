#include "main.h"
#include "globals.hpp"
#include "controls.h"
static const int increment = 20;
static const int delta_time = 20;

int SignOf(int x) {
    if (x>0) return 1;
    if (x<0) return -1;
    return 0;
}

void MtrAccel(pros::Motor* mtr,int speed) {
    using namespace std;
    uint32_t now = pros::millis();
    double ratio = 127/mtr->get_voltage_limit();
    int deltaSpd = 0;
    int currentSpd = int(floor(mtr->get_voltage()*ratio));
    while (currentSpd != speed) {
        currentSpd = int(floor(mtr->get_voltage()*ratio));
        deltaSpd = speed - currentSpd;
        if (abs(deltaSpd) > increment) {
            currentSpd += increment * SignOf(deltaSpd);
        } else {
            currentSpd = speed;
        }
        mtr->move(currentSpd);
        pros::Task::delay_until(&now,delta_time);
    }
    if (speed == 0) mtr->move_velocity(0);
}

void SetLiftPos(pros::Motor *mtr, pros::ADIPotentiometer* poti, int target, int speedMax) {
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
        MtrAccel(mtr,speedMax);
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

    MtrAccel(mtr,0);
}

int LogSpeed(int rawSpeed) {
    return (rawSpeed*rawSpeed) / (127*SignOf(rawSpeed));
}