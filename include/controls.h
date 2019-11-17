#ifndef _CONTROLS_H_
#define _CONTROLS_H_

static const int baseSpeed = 60;
static const float RATIO_FOR_mV_TO_SPEED = 0.010583;
static const int DEADBAND = 50;
static const int POTENTIOMETER_DEADBAND = 5;

static const bool DEBUG = true;

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
void MtrAccel(pros::Motor* mtr,int speed); 
void SetLiftPos(pros::Motor *mtr, pros::ADIPotentiometer* poti, int target, int speedMax);

void Routine();
int LogSpeed(int rawSpeed);
int SignOf(int x);
void MsgTerminal(std::string msg);
#endif