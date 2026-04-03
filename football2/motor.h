class Motor
{
public:
    Motor(int location_angle, int pin_1, int pin_2, int direction, int angle_coef, bool debug = false);
    void set_velocity(float linear_speed, float angle, float angular_speed);
    void run();
    void debug();

private:
    int _location_angle;
    int _pin_1;
    int _pin_2;
    int _direction;
    int _angle_coef;
    int _rotation_speed; // СКОРОСТЬ ВРАЩЕНИЯ САМОГО МОТОРА

    bool _debug{};
};
