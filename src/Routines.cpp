#include "auto.hpp"

void Procedure() {
    int x,y;
    //ReleaseLift(&arm,-2750);
    //TareLift(&arm,&liftBtn);
    //TurnIntakeON(false);
    //pros::delay(1000);
    //TurnIntakeOFF();


    if (autoMode == BLUE_LEFT_GOAL) {
        //TurnIntakeON(true);
        //pros::delay(100);
        pidStright(-36,90);
        //TurnIntakeOFF();
        pidStright(24,90);

        
        /*pidTurn(900,80);
        pidStright(25,120);
        pidTurn(-900,80);

        ReleaseLift(&arm,-2000);
        pidStright(-y,120);
        TareLift(&arm,&liftBtn);*/
    } else if (autoMode == RED_RIGHT_GOAL) {
        TurnIntakeON(true);
        pidStright(x,120);
        TurnIntakeOFF();
        pidStright(-x,120);

        pidTurn(900,100);
        pidStright(y,120);
        ReleaseLift(&arm,-2000);
        pidStright(-y,120);
        TareLift(&arm,&liftBtn);
    } else if (autoMode == BLUE_RIGHT_GOAL) {
        
    }
}