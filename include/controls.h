#ifndef _CONTROLS_H_
#define _CONTROLS_H_

static const int baseSpeed = 60;
static const float RATIO_FOR_mV_TO_SPEED = 0.010583f;
static const int DEADBAND = 50;

static const bool DEBUG = false;

typedef struct {
    int target;
    pros::Motor *motor;
} SlewArgs;

typedef struct {
    const char * input;
    pros::Controller *ctrlr;
} lcdArgs;

void initlizeArm();
void initlizeSensors();/*
extern pros::Controller master;
extern pros::Motor leftOne;
extern pros::Motor leftTwo;
extern pros::Motor rightOne;
extern pros::Motor rightTwo;
extern okapi::IntegratedEncoder leftEnc;
extern okapi::IntegratedEncoder RightEnc;*/
pros::motor_pid_s_t SetPID(double gainP, double gainI, double gainD, int port);
void SlewRate(int target, pros::Motor *motor); 
void TaskSlew(void* args);
void TaskUpdate(void* stringArg);
void Maincontrol();
void Routine();
#endif