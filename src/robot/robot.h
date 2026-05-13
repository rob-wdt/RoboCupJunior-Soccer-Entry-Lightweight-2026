#pragma once

#include "..\hal\sensors\gyros\gyro.h"
#include "..\hal\sensors\ir\IR.h"
#include "..\hal\motor\motor.h"
#include "..\control\regulator.h"
#include "..\perception\camera\camera.h"
#include "..\hal\button\button.h"
#include "..\hal\led\LED.h"

class Robot
{
public:
    Robot(
        Gyro &gyro,
        Button start_btn,
        Button set_btn,
        LED signal_led,
        IR ir,
        Motor m1,
        Motor m2,
        Motor m3,
        Regulator &cam_control,
        Regulator &gyro_control,
        Regulator &angle_control,
        Regulator &distance_control,
        Camera cam,
        int debug_mode,
        int game_mode);

    void init();
    void signal();
    void read_sensors();
    void wait_for_btn(Button *btn, void (*to_do)());
    void update_state();
    void set_angle();
    void set_angle(int new_angle);
    void set_speed(float linear_speed);
    void move();
    void stop();

    Gyro *gyro();
    Button *start_btn();
    Button *set_btn();
    LED *signal_led();
    IR *ir_seeker();
    Motor *motor_1();
    Motor *motor_2();
    Motor *motor_3();
    Regulator *camera_control();
    Regulator *gyro_control();
    Regulator *angle_control();
    Regulator *distance_control();
    Camera *camera();

private:
    Gyro &_gyro;
    Button _start_btn;
    Button _set_btn;
    LED _signal;
    IR _ir;
    Motor _m1;
    Motor _m2;
    Motor _m3;
    Regulator &_cam_cont;
    Regulator &_gyro_cont;
    Regulator &_angle_cont;
    Regulator &_distance_cont;
    Camera _cam;

    unsigned char _state{};
    
    float _angle{};
    // float _prev_angle{};

    int _debug_mode{};
    int _game_mode{};
};