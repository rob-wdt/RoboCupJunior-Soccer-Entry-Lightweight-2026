#pragma once

#include "gyro.h"
#include "button.h"
#include "IR.h"
#include "motor.h"
#include "PDC.h"
#include "camera.h"

class Robot
{
public:
    Robot(Gyro &gyro, Button &gyro_btn, Button &set_btn, IR &ir, Motor &m1, Motor &m2, Motor &m3, PDC &cam_pdc, PDC &gyro_pdc, Camera &cam, bool debug = false);
    void init();
    void calibrate_gyro();
    void set_gyro_zero_angle();
    void read_sensors();
    void set_angle();
    void set_speed(float linear_speed);
    void move();

    Gyro _gyro;
    Button _gyro_btn;
    Button _set_btn;
    IR _ir;
    Motor _m1;
    Motor _m2;
    Motor _m3;
    PDC _cam_pdc;
    PDC _gyro_pdc;
    Camera _cam;

private:
    float _angle{};
    //float _prev_angle{};

    bool _debug{};
};