#ifndef _TEST_H_
#define _TEST_H_ 

#define kP_D_TEST 0.25
#define kI_D_TEST 0.05
#define kD_D_TEST 1.4

#define kP_L_TEST 0.6;
#define kI_L_TEST 0.3;
#define kD_L_TEST 0.2;

#define kP_T_TEST 0.6;
#define kI_T_TEST 0.3;
#define kD_T_TEST 0.3;

#define DRIVE_MAX_SPEED 80
#define LIFT_MAX_SPEED 90
#define TURN_MAX_SPEED 70

/*extern pros::Motor leftOne;
extern okapi::IntegratedEncoder leftEnc;
extern pros::Motor leftTwo;
extern pros::Motor rightOne;
extern okapi::IntegratedEncoder rightEnc;
extern pros::Motor rightTwo;

extern pros::Motor leftArm;
extern okapi::IntegratedEncoder leftArm_ENC;
extern pros::Motor rightArm;
extern okapi::IntegratedEncoder rightArm_ENC;*/

void pid_Drive_Test(int target_distance, bool foward, pros::Motor *motor);
void pid_Lift_Test(int target_change,bool gain, pros::Motor * left, pros::Motor * right, okapi::IntegratedEncoder leftEnc, okapi::IntegratedEncoder rightEnc);
#endif