#include "main.h"
#include "globals.hpp"

int AUTO_LIMIT = 4;

void MoveAutoUp() {
    autoMode += 1;
    if (autoMode > AUTO_LIMIT) autoMode = AUTO_LIMIT;
}

void MoveAutoDown() {
    autoMode -= 1;
    if (autoMode < 0) autoMode = 0;
}

void ConfirmAuto() {
    choosingAuto = false;
}

void ChooseAutoLEGACY() {
    using namespace pros::lcd;
    set_text(1,"left btn, move the auto value up");
    set_text(2,"middle btn, move the auto value down");
    set_text(3,"right btn, confirm and exit auton selection");
    while (!choosingAuto) {
        switch (autoMode)
        {
            case 0:
                set_text(0,"Blue Left Goal");
                break;
            case 1:
                set_text(0,"Blue Right Goal");
                break;
            case 2:
                set_text(0,"Red Left Goal");
                break;
            case 3:
                set_text(0,"Red Right Goal");
                break;
            case 4:
                set_text(0,"Skills Run");
                break;

            default:
                break;
        }
        pros::delay(10);
    }
    clear();
}