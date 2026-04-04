#include "HardwareSerial.h"
#include "robot.h"

Robot::Robot(
    Gyro &gyro, 
    Button &gyro_btn, 
    Button &set_btn, 
    IR &ir, 
    Motor &m1, 
    Motor &m2, 
    Motor &m3, 
    PDC &cam_pdc, 
    PDC &gyro_pdc, 
    Camera &cam,
    bool debug = false
) 
: 
_gyro{gyro}, 
_gyro_btn{gyro_btn}, 
_set_btn{set_btn}, 
_ir{ir}, 
_m1{m1}, 
_m2{m2}, 
_m3{m3}, 
_cam_pdc{cam_pdc}, 
_gyro_pdc{gyro_pdc},
_cam{cam},
_debug{debug}
{}

void Robot::init()
{
    _ir.init();
    _gyro.init();
    _gyro_btn.init();
    _set_btn.init();
    //_cam.init();
}

void Robot::calibrate_gyro()
{
    Serial.println("Press A3 btn to start calibrating");
    while (!_gyro_btn.is_pressed())
    {
        _gyro_btn.read();
    }
    _gyro.calibrate();
    Serial.println("Finish calibrating");
}

void Robot::set_gyro_zero_angle()
{
    Serial.println("Press A5 btn to set zero angle");
    while (!_set_btn.is_pressed())
    {
        _set_btn.read();
        _gyro.read();
    }
    _gyro.set_zero_angle(_gyro.yaw());
    Serial.print("Zero angle set:\t");
    Serial.println(_gyro.zero_angle());
}

void Robot::read_sensors()
{
    _gyro.read();
    _gyro_btn.read();
    _set_btn.read();
    _ir.read();
    _cam.read();
}

void Robot::set_angle()
{
    // _prev_angle = _angle;
    
    // if (_ir.strength() > 0)
    // {
    //     if (abs(_ir.angle()) < 30)
    //     {
    //         _angle = _ir.angle();
    //     }

    //     else if (abs(_ir.angle()) >= 30 && abs(_ir.angle()) < 150)
    //     {
    //         if (_ir.angle() > 0)
    //         {
    //             _angle = _ir.angle() + 90;
    //         }

    //         else if (_ir.angle() < 0)
    //         {
    //             _angle = _ir.angle() - 90;
    //         }
    //     }
    // }

    // else if (_ir.strength() <= 0)
    // {
    //     if (abs(_ir.angle()) >= 150)
    //     {
    //         if (_prev_angle < 0)
    //         {
    //             _angle = _prev_angle - 90;
    //             Serial.println("-");
    //         }

    //         else if (_prev_angle > 0)
    //         {
    //             Serial.println("-");
    //             _angle = _prev_angle + 90;
    //         }
    //     }
    // }

    // if (_debug)
    // {
    //     Serial.println();
    //     Serial.print(_angle);
    //     Serial.print('\t');
    //     Serial.println(_prev_angle);
    // }

    _angle = _ir.angle();

    if (_angle)
    {
        if (_angle < 0)
        {
            _angle = -90;
        }
        else if (_angle > 0)
        {
            _angle += 90;
        }
    }
}

void Robot::set_speed(float linear_speed)
{
    set_angle();
    _m1.set_velocity(linear_speed, _angle, _gyro_pdc.get(_gyro.yaw()));
    _m2.set_velocity(linear_speed, _angle, _gyro_pdc.get(_gyro.yaw()));
    _m3.set_velocity(linear_speed, _angle, _gyro_pdc.get(_gyro.yaw()));
}

void Robot::move()
{
    _m1.run();
    _m2.run();
    _m3.run();
}