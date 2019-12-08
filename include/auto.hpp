#ifndef AUTO_HPP
#define AUTO_HPP
#include "main.h"
#include "controls.h"
#include "globals.hpp"

const static int wheelDiameter = 4;
const static double driveCircumference = 12.6;
const static int ticksPerRev = 900;

void pidStright(double distance, int speed);
void pidTurn(int degrees, int speed);

void pidRelease();
void TurnIntakeON(bool inwards);
void TurnIntakeOFF();

void Procedure();

#endif