#include "HardwareSerial.h"
#include "config.h"
#include "robot.h"

Robot::Robot(
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
    bool debug)
    : _gyro{gyro},
      _start_btn{start_btn},
      _set_btn{set_btn},
      _signal{signal_led},
      _ir{ir},
      _m1{m1},
      _m2{m2},
      _m3{m3},
      _cam_cont{cam_control},
      _gyro_cont{gyro_control},
      _angle_cont{angle_control},
      _distance_cont{distance_control},
      _cam{cam},
      _debug{debug}
{
}

void Robot::init()
{
    _ir.init();
    _gyro.init();
    _start_btn.init();
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

    _start_btn.reset();
    _start_btn.read();

    _set_btn.reset();
    _set_btn.read();

    _ir.read();
    //_cam.read();
}

void Robot::wait_for_btn(Button &btn, void (*to_do)())
{
    btn.reset();
    while (!btn.is_pressed())
    {
        btn.read();
        to_do();
    }
    btn.reset();
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

    //_angle = _ir.angle();

    // if (abs(_angle) != 150)
    // {
    //     if (_ir.strength() > _ir.med_strength())
    //     {
    //         if (abs(_angle) > 30)
    //         {
    //             if (_angle)
    //             {
    //                 if (_angle < 0)
    //                 {
    //                     _angle -= 90;
    //                 }
    //                 else if (_angle > 0)
    //                 {
    //                     _angle += 90;
    //                 }
    //             }
    //         }
    //     }
    // }

    //----------------------ГОШИНА ФОРМУЛА-------------------
    _angle = _ir.angle();

    // if (_ir.strength() >= 0)
    {
        float _angle_koef{_angle_cont.get(_ir.angle())};
        float _dist_koef{_distance_cont.get(-_ir.strength())};

        float _res;
        if (_ir.angle() > 0)
        {
            _res = _angle_koef * _dist_koef;
        }
        else
        {
            _res = _angle_koef * _dist_koef;
        }

        _angle += _res;
    }

    if (_debug)
    {
        Serial.print("Angle:\t");
        Serial.println(_angle);
    }
}

void Robot::set_angle(int new_angle)
{
    _angle = new_angle;
}

void Robot::set_speed(float linear_speed)
{
    //_angle = ANGLE;
    float _angular_speed{_gyro_cont.get(_gyro.yaw())};
    // float _angular_speed{};
    _m1.set_velocity(linear_speed, _angle, _angular_speed);
    _m2.set_velocity(linear_speed, _angle, _angular_speed);
    _m3.set_velocity(linear_speed, _angle, _angular_speed);
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
    return &_start_btn;
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

Regulator *Robot::camera_control()
{
    return &_cam_cont;
}

Regulator *Robot::gyro_control()
{
    return &_gyro_cont;
}

Regulator *Robot::angle_control()
{
    return &_angle_cont;
}

Regulator *Robot::distance_control()
{
    return &_distance_cont;
}

Camera *Robot::camera()
{
    return &_cam;
}