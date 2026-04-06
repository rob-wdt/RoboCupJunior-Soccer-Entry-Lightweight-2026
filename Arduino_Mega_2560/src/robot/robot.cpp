#include "config.h"
#include "HardwareSerial.h"
#include "robot.h"

Robot::Robot(
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
) 
: 
_gyro{gyro}, 
_gyro_btn{start_btn}, 
_set_btn{set_btn},
_signal{signal_led}, 
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
    _signal.init();
    //_cam.init();
}

void Robot::signal()
{
    _signal.on();
    delay(100);
    _signal.off();
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
        if(_ir.strength() > _ir.min_strength())  //ЕСЛИ БЛИЗКО
        {
            if (_angle < 0)
            {
                _angle -= 90;
            }
            else
            {
                _angle += 90;
            }
            if (_angle > -150)
            _angle -= 60;

            else
            _angle -= 30;
        }
        else if (_angle > 0)
        {
            if (_angle < 150)
            _angle += 0;

            else
            _angle += 30;
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

void Robot::stop()
{
    _m1.stop();
    _m2.stop();
    _m3.stop();
}

Gyro *Robot::gyro()
{
    return &_gyro;
}

Button *Robot::start_btn()
{
    return &_gyro_btn;
}

Button *Robot::set_btn()
{
    return &_set_btn;
}

LED *Robot::signal_led()
{
    return &_signal;
}

IR *Robot::ir_seeker()
{
    return &_ir;
}

Motor *Robot::motor_1()
{
    return &_m1;
}

Motor *Robot::motor_2()
{
    return &_m2;
}

Motor *Robot::motor_3()
{
    return &_m3;
}

PDC *Robot::camera_control()
{
    return &_cam_pdc;
}

PDC *Robot::gyro_control()
{
    return &_gyro_pdc;
}

Camera *Robot::camera()
{
    return &_cam;
}