#include "main.h"
#include "controls.h"
const int increment = 20;
const int delta_time = 5;

pros::motor_pid_s_t SetPID(double gainP, double gainI, double gainD, int port) {
    pros::motor_pid_s_t pid = pros::Motor::convert_pid(0,gainP,gainI,gainD);
    return pid;
}

void SlewRate(int target,pros::Motor *motor) {
    //if (motor->get_direction() == EACCES) return;
    int speed = int(std::round(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
    //std::cout << speed << std::endl;
    //std::cout << target << std::endl;
    //prevent needless calls when joystick is held
    if (speed == target || std::abs(std::abs(target)-std::abs(speed)) < 10) return;

    if (std::abs(speed) < std::abs(target)) {//checks if going cw
        if (motor->get_direction() == 1 || target > 0) {
            std::cout << "-----TEST ONE-----" << std::endl;
            std::cout << "V V V V V V V V V " << std::endl;
            while (speed < target) {
                if(!motor->is_over_current()) {
                    speed += increment; 
                    motor->move(speed);
                }
                std::printf("voltage of Motor: %dmV \n",motor->get_voltage());
                std::printf("speed of Motor: %d\n",int(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                std::cout << "Current of Motor: " << motor->get_current_draw() << "mA" << std::endl;
                pros::delay(delta_time);
            }
            std::cout << "-----END OF TEST ONE------" << std::endl;
            std::cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << std::endl;
            if (speed > 127) motor->move(127);
            return;
        }
        else {//ccw
            //std::cout << "-----TEST TWO-----" << std::endl;
            //std::cout << "V V V V V V V V V " << std::endl;
            while (speed > target) {
                if (!motor->is_over_current()) {
                    speed -= increment;
                    motor->move(speed);
                }
                //std::printf("speed of Motor: %d\n",int(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                //std::cout << "Current of Motor: " << motor->get_current_draw() << "mA" << std::endl;
                pros::delay(delta_time);
            }
            //std::cout << "-----END OF TEST TWO------" << std::endl;
            //std::cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << std::endl;
            if (speed < -127) motor->move(-127);
            return;
        }
    }
    else {
        if (std::abs(speed) < 30) {
            motor->move(0);
            return;
        } else {  
            if (speed > 0) {
                std::cout << "-----TEST THREE-----" << std::endl;
                std::cout << "V V V V V V V V V V " << std::endl;
                while (speed > target) {
                    if (!motor->is_over_current()) {
                        speed -= increment;
                        motor->move(speed);
                    }
                    std::printf("voltage of Motor: %dmV \n",motor->get_voltage());
                    std::printf("speed of Motor: %d\n",int(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                    std::cout << "Current of Motor: " << motor->get_current_draw() << "mA" << std::endl;
                    pros::delay(delta_time);
                }
                if (std::abs(std::round(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED)) < 20) motor->move(0);
                std::cout << "-----END OF TEST THREE------" << std::endl;
                std::cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << std::endl;
                return;
            }
            else {
                std::cout << "-----TEST FOUR-----" << std::endl;
                std::cout << "V V V V V V V V V " << std::endl;
                while (speed < target) {
                    if (!motor->is_over_current()) {
                        speed += increment;
                        motor->move(speed);
                    }
                    //std::printf("speed of Motor: %d\n",int(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                    //std::cout << "Current of Motor: " << motor->get_current_draw() << "mA" << std::endl;
                    pros::delay(delta_time);
                }
                if (std::abs(std::round(motor->get_voltage()*RATIO_FOR_mV_TO_SPEED)) < 20) motor->move(0);
                //std::cout << "-----END OF TEST FOUR------" << std::endl;
                //std::cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^" << std::endl;
                return;
            }
        }
    }
    return;
}

void TaskSlew(void* args) {
    //if (motor->get_direction() == EACCES) return;
    int speed = int(std::round(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
    //std::cout << speed << std::endl;
    //std::cout << target << std::endl;
    //prevent needless calls when joystick is held
    if (speed == ((SlewArgs*)args)->target || std::abs(std::abs(((SlewArgs*)args)->target)-std::abs(speed)) < 10) return;

    if (std::abs(speed) < std::abs(((SlewArgs*)args)->target)) {//checks if going cw
        if (((SlewArgs*)args)->motor->get_direction() == 1 || ((SlewArgs*)args)->target > 0) {
            std::cout << "-----TEST ONE-----" << std::endl;
            std::cout << "V V V V V V V V V " << std::endl;
            while (speed < ((SlewArgs*)args)->target) {
                if(!((SlewArgs*)args)->motor->is_over_current()) {
                    speed += 5; 
                    ((SlewArgs*)args)->motor->move(speed);
                }
                std::printf("voltage of Motor: %dmV \n",((SlewArgs*)args)->motor->get_voltage());
                std::printf("speed of Motor: %d\n",int(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                std::cout << "Current of Motor: " << ((SlewArgs*)args)->motor->get_current_draw() << "mA" << std::endl;
                pros::Task::delay(5);
            }
            std::cout << "-----END OF TEST ONE------" << std::endl;
            std::cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << std::endl;
            if (speed > 127) ((SlewArgs*)args)->motor->move(127);
            return;
        }
        else {//ccw
            std::cout << "-----TEST TWO-----" << std::endl;
            std::cout << "V V V V V V V V V " << std::endl;
            while (speed > ((SlewArgs*)args)->target) {
                if (!((SlewArgs*)args)->motor->is_over_current()) {
                    speed -= 5;
                    ((SlewArgs*)args)->motor->move(speed);
                }
                std::printf("speed of Motor: %d\n",int(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                std::cout << "Current of Motor: " << ((SlewArgs*)args)->motor->get_current_draw() << "mA" << std::endl;
                pros::Task::delay(5);
            }
            std::cout << "-----END OF TEST TWO------" << std::endl;
            std::cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << std::endl;
            if (speed < -127) ((SlewArgs*)args)->motor->move(-127);
            return;
        }
    }
    else {
        if (std::abs(speed) < 30) {
            ((SlewArgs*)args)->motor->move(0);
            return;
        } else {  
            if (speed > 0) {
                std::cout << "-----TEST THREE-----" << std::endl;
                std::cout << "V V V V V V V V V V " << std::endl;
                while (speed > ((SlewArgs*)args)->target) {
                    if (!((SlewArgs*)args)->motor->is_over_current()) {
                        speed -= 5;
                       ((SlewArgs*)args)->motor->move(speed);
                    }
                    std::printf("voltage of Motor: %dmV \n",((SlewArgs*)args)->motor->get_voltage());
                    std::printf("speed of Motor: %d\n",int(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                    std::cout << "Current of Motor: " << ((SlewArgs*)args)->motor->get_current_draw() << "mA" << std::endl;
                    pros::Task::delay(5);
                }
                if (std::abs(std::round(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED)) < 20) ((SlewArgs*)args)->motor->move(0);
                std::cout << "-----END OF TEST THREE------" << std::endl;
                std::cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ " << std::endl;
                return;
            }
            else {
                std::cout << "-----TEST FOUR-----" << std::endl;
                std::cout << "V V V V V V V V V " << std::endl;
                while (speed < ((SlewArgs*)args)->target) {
                    if (!((SlewArgs*)args)->motor->is_over_current()) {
                        speed += 5;
                        ((SlewArgs*)args)->motor->move(speed);
                    }
                    std::printf("speed of Motor: %d\n",int(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED));
                    std::cout << "Current of Motor: " << ((SlewArgs*)args)->motor->get_current_draw() << "mA" << std::endl;
                    pros::Task::delay(5);
                }
                if (std::abs(std::round(((SlewArgs*)args)->motor->get_voltage()*RATIO_FOR_mV_TO_SPEED)) < 20) ((SlewArgs*)args)->motor->move(0);
                std::cout << "-----END OF TEST FOUR------" << std::endl;
                std::cout << "^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^" << std::endl;
                return;
            }
        }
    }
    return;
}

void TaskUpdate(void* stringArg) {
    std::uint32_t time = pros::millis();
        ((lcdArgs*)stringArg)->ctrlr->print(0,0,((lcdArgs*)stringArg)->input);
        pros::Task::delay_until(&time,50);
}