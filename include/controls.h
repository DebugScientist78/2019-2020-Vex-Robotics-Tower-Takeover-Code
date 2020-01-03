#ifndef _CONTROLS_H_
#define _CONTROLS_H_

static const int baseSpeed = 60;
static const float RATIO_FOR_mV_TO_SPEED = 0.010583;
static const int DEADBAND = 50;

static const bool DEBUG = false;

void TareArm(pros::Motor *mtr, pros::ADIDigitalIn *btn);
void ReleaseArm(pros::Motor *mtr, int target);
void ManualArm();
void Intake();
void Drive(pros::Motor *mtrs[4], pros::Controller *ctrlr);
void ManualLift();
void TareLift();
void SetLift(int position);

void Routine();
int LogSpeed(int rawSpeed);
int SignOf(int x);
void MsgTerminal(std::string msg);
#endif