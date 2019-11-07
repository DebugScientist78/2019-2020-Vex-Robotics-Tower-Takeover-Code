#include "main.h"
#include "controls.h"
const int increment = 20;
const int delta_time = 5;

pros::motor_pid_s_t SetPID(double gainP, double gainI, double gainD, int port) {
    pros::motor_pid_s_t pid = pros::Motor::convert_pid(0,gainP,gainI,gainD);
    return pid;
}

void SlewRate(int target,pros::Motor *motor) {
    using namespace std;
    //if (motor->get_direction() == EACCES) return;
    int speed = int(round(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
    //cout << speed << endl;
    //cout << target << endl;
    //prevent needless calls when joystick is held
    if (speed == target || abs(abs(target)-abs(speed)) < 10) return;

    if (abs(speed) < abs(target)) {//checks if going cw
        if (motor->get_direction() == 1 || target > 0) {
            if (DEBUG) cout << "-----TEST ONE-----" << endl;
            if (DEBUG) cout << "V V V V V V V V V " << endl;
            while (speed < target) {
                if(!motor->is_over_current()) {
                    speed += increment; 
                    motor->move(speed);
                }
                if (DEBUG) printf("voltage of Motor: %dmV \n",motor->get_voltage());
                if (DEBUG) printf("speed of Motor: %d\n",int(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                if (DEBUG) cout << "Current of Motor: " << motor->get_current_draw() << "mA" << endl;
                pros::delay(delta_time);
            }
            if (DEBUG) cout << "-----END OF TEST ONE------" << endl;
            if (DEBUG) cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << endl;
            if (speed > 127) motor->move(127);
            return;
        }
        else {//ccw
            if (DEBUG) cout << "-----TEST TWO-----" << endl;
            if (DEBUG) cout << "V V V V V V V V V " << endl;
            while (speed > target) {
                if (!motor->is_over_current()) {
                    speed -= increment;
                    motor->move(speed);
                }
                if (DEBUG) printf("speed of Motor: %d\n",int(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                if (DEBUG) cout << "Current of Motor: " << motor->get_current_draw() << "mA" << endl;
                pros::delay(delta_time);
            }
            if (DEBUG) cout << "-----END OF TEST TWO------" << endl;
            if (DEBUG) cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << endl;
            if (speed < -127) motor->move(-127);
            return;
        }
    }
    else {
        if (abs(speed) < 30) {
            motor->move(0);
            return;
        } else {  
            if (speed > 0) {
                if (DEBUG) cout << "-----TEST THREE-----" << endl;
                if (DEBUG) cout << "V V V V V V V V V V " << endl;
                while (speed > target) {
                    if (!motor->is_over_current()) {
                        speed -= increment;
                        motor->move(speed);
                    }
                    if (DEBUG) printf("voltage of Motor: %dmV \n",motor->get_voltage());
                    if (DEBUG) printf("speed of Motor: %d\n",int(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                    if (DEBUG) cout << "Current of Motor: " << motor->get_current_draw() << "mA" << endl;
                    pros::delay(delta_time);
                }
                if (abs(round(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED)) < 20) motor->move(0);
                if (DEBUG) cout << "-----END OF TEST THREE------" << endl;
                if (DEBUG) cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << endl;
                return;
            }
            else {
                if (DEBUG) cout << "-----TEST FOUR-----" << endl;
                if (DEBUG) cout << "V V V V V V V V V " << endl;
                while (speed < target) {
                    if (!motor->is_over_current()) {
                        speed += increment;
                        motor->move(speed);
                    }
                    if (DEBUG) printf("speed of Motor: %d\n",int(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                    if (DEBUG) cout << "Current of Motor: " << motor->get_current_draw() << "mA" << endl;
                    pros::delay(delta_time);
                }
                if (abs(round(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED)) < 20) motor->move(0);
                if (DEBUG) cout << "-----END OF TEST FOUR------" << endl;
                if (DEBUG) cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^" << endl;
                return;
            }
        }
    }
    return;
}

void TaskSlew(void* args) {
    using namespace std;
    //if (motor->get_direction() == EACCES) return;
    int speed = int(round(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
    //cout << speed << endl;
    //cout << target << endl;
    //prevent needless calls when joystick is held
    if (speed == ((SlewArgs*)args)->target || abs(abs(((SlewArgs*)args)->target)-abs(speed)) < 10) return;

    if (abs(speed) < abs(((SlewArgs*)args)->target)) {//checks if going cw
        if (((SlewArgs*)args)->motor->get_direction() == 1 || ((SlewArgs*)args)->target > 0) {
            cout << "-----TEST ONE-----" << endl;
            cout << "V V V V V V V V V " << endl;
            while (speed < ((SlewArgs*)args)->target) {
                if(!((SlewArgs*)args)->motor->is_over_current()) {
                    speed += 5; 
                    ((SlewArgs*)args)->motor->move(speed);
                }
                printf("voltage of Motor: %dmV \n",((SlewArgs*)args)->motor->get_voltage());
                printf("speed of Motor: %d\n",int(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                cout << "Current of Motor: " << ((SlewArgs*)args)->motor->get_current_draw() << "mA" << endl;
                pros::Task::delay(5);
            }
            cout << "-----END OF TEST ONE------" << endl;
            cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << endl;
            if (speed > 127) ((SlewArgs*)args)->motor->move(127);
            return;
        }
        else {//ccw
            cout << "-----TEST TWO-----" << endl;
            cout << "V V V V V V V V V " << endl;
            while (speed > ((SlewArgs*)args)->target) {
                if (!((SlewArgs*)args)->motor->is_over_current()) {
                    speed -= 5;
                    ((SlewArgs*)args)->motor->move(speed);
                }
                printf("speed of Motor: %d\n",int(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                cout << "Current of Motor: " << ((SlewArgs*)args)->motor->get_current_draw() << "mA" << endl;
                pros::Task::delay(5);
            }
            cout << "-----END OF TEST TWO------" << endl;
            cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << endl;
            if (speed < -127) ((SlewArgs*)args)->motor->move(-127);
            return;
        }
    }
    else {
        if (abs(speed) < 30) {
            ((SlewArgs*)args)->motor->move(0);
            return;
        } else {  
            if (speed > 0) {
                cout << "-----TEST THREE-----" << endl;
                cout << "V V V V V V V V V V " << endl;
                while (speed > ((SlewArgs*)args)->target) {
                    if (!((SlewArgs*)args)->motor->is_over_current()) {
                        speed -= 5;
                       ((SlewArgs*)args)->motor->move(speed);
                    }
                    printf("voltage of Motor: %dmV \n",((SlewArgs*)args)->motor->get_voltage());
                    printf("speed of Motor: %d\n",int(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                    cout << "Current of Motor: " << ((SlewArgs*)args)->motor->get_current_draw() << "mA" << endl;
                    pros::Task::delay(5);
                }
                if (abs(round(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED)) < 20) ((SlewArgs*)args)->motor->move(0);
                cout << "-----END OF TEST THREE------" << endl;
                cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << endl;
                return;
            }
            else {
                cout << "-----TEST FOUR-----" << endl;
                cout << "V V V V V V V V V " << endl;
                while (speed < ((SlewArgs*)args)->target) {
                    if (!((SlewArgs*)args)->motor->is_over_current()) {
                        speed += 5;
                        ((SlewArgs*)args)->motor->move(speed);
                    }
                    printf("speed of Motor: %d\n",int(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                    cout << "Current of Motor: " << ((SlewArgs*)args)->motor->get_current_draw() << "mA" << endl;
                    pros::Task::delay(5);
                }
                if (abs(round(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED)) < 20) ((SlewArgs*)args)->motor->move(0);
                cout << "-----END OF TEST FOUR------" << endl;
                cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^" << endl;
                return;
            }
        }
    }
    return;
}

int LogSpeed(int rawSpeed) {
    if (rawSpeed >= 0) {
        return round((rawSpeed*rawSpeed)/127.0f);
    } else {
        return round((rawSpeed*rawSpeed)/-127.0f);
    }
}

void MsgTerminal(std::string msg) {
    using namespace std;
    cout << msg << endl;
}