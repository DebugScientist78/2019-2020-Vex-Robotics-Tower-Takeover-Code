#ifndef _CONTROLS_H_
#define _CONTROLS_H_

static const int baseSpeed = 60;
static const float RATIO_FOR_mV_TO_SPEED = 0.010583;
static const int DEADBAND = 20;

static const bool DEBUG = false;

void TareTilter();
void ReleaseTilter(int target);
void ManualTilter();
void Intake();
void Drive();
void ManualArm();
void TareArm();
void SetArm(int position);

void TilterSystem();
void ArmSystem();

int LogSpeed(int rawSpeed);
int SignOf(int x);

void masterSwitch();
#endif