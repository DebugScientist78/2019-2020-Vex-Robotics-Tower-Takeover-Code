#ifndef ODOM_HPP
#define ODOM_HPP

class Odom {
private:
    int relative_x,relative_y, relative_angle;
    bool x_axisOpen, onRed, goingPositive;
public:
    Odom(bool isRed);

    void Turn(int degrees, int speed);
    void MoveX(int distance_relative, int speed);
    void MoveY(int distance_relative, int speed);
    void ResetPosition(void);
    void FlipOut();

    int getXposition(void);
    int getYposition(void);
    int getAngle(void);
};

#endif