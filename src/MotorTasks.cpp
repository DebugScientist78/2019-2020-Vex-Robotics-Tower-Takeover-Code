#include "main.h"
#include "controls.h"
#include "MotorTasks.h"

void TaskDrive(void* param) {
    std::uint32_t now = pros::millis();
    for (int i = 0; i < 4; i++) {
        SlewRate(((DriveReference*)param)->mtrTarget[i],((DriveReference*)param)->mtrRef[i]);
        pros::Task::delay_until(&now,30);
    }
}

void TaskIntake(void* param) {
    SlewRate(((IntakeReference*)param)->spd,((IntakeReference*)param)->mtrRef[0]);
    SlewRate(((IntakeReference*)param)->spd*-1,((IntakeReference*)param)->mtrRef[1]);
}