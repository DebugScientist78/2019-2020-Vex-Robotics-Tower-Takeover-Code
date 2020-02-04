#include "main.h"
#include "globals.hpp"

void Procedure() {
    using namespace okapi;
    auto drive = ChassisControllerBuilder()
        .withMotors({1,2},{-3,-4})
        .withDimensions(AbstractMotor::gearset::green,{{3.25_in,10.5_in},okapi::imev5GreenTPR})
        .withOdometry()
        .buildOdometry();
    
    auto tilter = AsyncPosControllerBuilder()
        .withMotor(11)
        .build();

    auto arm = AsyncPosControllerBuilder()
        .withMotor(7)
        .build();

    auto intake = AsyncVelControllerBuilder()
        .withMotor({6,-8})
        .build();

    if (autoMode == BLUE_LEFT_GOAL) {
        drive->setMaxVelocity(100);
        drive->moveDistanceAsync(30_in);
        intake->setTarget(200);
        drive->waitUntilSettled();
        intake->waitUntilSettled();

        drive->moveDistance(-24_in);
        drive->turnAngle(135_deg);
        drive->moveDistance(10_in);

        tilter->setTarget(-2000);


    } else if (autoMode == RED_RIGHT_GOAL) {

    } else if (autoMode == BLUE_RIGHT_GOAL) {
        
    }
}