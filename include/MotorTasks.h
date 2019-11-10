#ifndef MOTOR_TASKS_H
#define MOTOR_TASKS_H

typedef enum DriveDirection {
    FOWARD=0x00,
    BACKWARD=0x01,
    TURN_RIGHT=0x02,
    TURN_LEFT=0x03,
    STRAFE_RIGHT=0x04,
    STRAFE_LEFT=0x05
} DriveDirection;

typedef struct {
    pros::Motor* mtrRef[4];
    int mtrTarget[4];
} DriveReference;

typedef struct {
    pros::Motor* mtrRef[2];
    int spd;
} IntakeReference;

void TaskDrive(void* param);
void TaskIntake(void* param);

#endif