#pragma once

#include "..\hal\sensors\gyro.h"
#include "..\hal\button\button.h"
#include "..\hal\sensors\IR.h"
#include "..\hal\motor\motor.h"
#include "..\hal\led\LED.h"
#include "..\control\PDC.h"
#include "..\perception\camera\camera.h"

class Robot
{
public:
    Robot
    (
        Gyro gyro, 
        Button start_btn, 
        Button set_btn, 
        LED signal_led, 
        IR ir, 
        Motor m1, 
        Motor m2, 
        Motor m3, 
        PDC cam_pdc, 
        PDC gyro_pdc, 
        Camera cam, 
        bool debug = false
    );
    void init();
    void signal();
    void read_sensors();
    void set_angle();
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
    PDC *camera_control();
    PDC *gyro_control();
    Camera *camera();

private:
    Gyro _gyro;
    Button _gyro_btn;
    Button _set_btn;
    LED _signal;
    IR _ir;
    Motor _m1;
    Motor _m2;
    Motor _m3;
    PDC _cam_pdc;
    PDC _gyro_pdc;
    Camera _cam;

    float _angle{};
    //float _prev_angle{};

    bool _debug{};
};