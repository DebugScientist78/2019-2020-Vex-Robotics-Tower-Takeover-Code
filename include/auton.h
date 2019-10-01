#ifndef _AUTON_H_
#define _AUTON_H_

#define kP_D 0.25
#define kI_D 0.05
#define kD_D 1.4

#define kP_L 0.6;
#define kI_L 0.3;
#define kD_L 0.2;

#define kP_T 0.6;
#define kI_T 0.3;
#define kD_T 0.3;

#define DRIVE_MAX_SPEED 80
#define LIFT_MAX_SPEED 90
#define TURN_MAX_SPEED 70

extern int autoMode;

void pid_Drive(int target_distance, bool foward);
void pid_Lift(int target_change, bool gain);
void pid_Turn(int degrees);
void moveIntake();

#endif 