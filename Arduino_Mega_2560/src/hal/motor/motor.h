class Motor
{
public:
    Motor(int location_angle, int pin_1, int pin_2, int angle_coef, int angle_speed_coef, int cos_coef, int min_speed, bool debug = false);
    void set_velocity(float linear_speed, float angle, float angular_speed);
    void run();
    void run(int speed);
    void stop();
    void debug();

private:
    int _location_angle;
    int _pin_1;
    int _pin_2;
    int _angle_coef;
    int _angle_speed_coef;
    int _cos_coef;
    int _rotation_speed; // СКОРОСТЬ ВРАЩЕНИЯ САМОГО МОТОРА
    int _min_speed;

    bool _debug{};
};
