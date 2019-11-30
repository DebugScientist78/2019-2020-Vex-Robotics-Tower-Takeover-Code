#include "auto.hpp"

void Procedure() {
    int x,y;
    ReleaseLift(&arm,-2000);
    TareLift(&arm,&liftBtn);

    if (autoMode == BLUE_LEFT_GOAL) {
        TurnIntakeON(true);
        pidStright(x,120);
        TurnIntakeOFF();
        pidStright(-x,120);

        pidTurn(-900,100);
        pidStright(y,120);
        ReleaseLift(&arm,-2000);
        pidStright(-y,120);
        TareLift(&arm,&liftBtn);
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