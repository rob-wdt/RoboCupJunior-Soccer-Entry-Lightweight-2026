#pragma once

class Motor
{
public:
    Motor(
        int location_angle,
        int pin_1,
        int pin_2,
        int direction,
        int angle_coef,
        int angle_speed_coef,
        int cos_coef,
        double min_speed,
        bool debug);
    void set_velocity(double linear_speed, double angle, double angular_speed);
    void run();
    void run(double speed);
    void stop();
    void debug();

private:
    int _location_angle;
    int _pin_1;
    int _pin_2;
    int _direction;
    int _angle_coef;
    int _angle_speed_coef;
    int _cos_coef;
    int _rotation_speed; // СКОРОСТЬ ВРАЩЕНИЯ САМОГО МОТОРА
    double _min_speed;

    bool _debug{};
};
