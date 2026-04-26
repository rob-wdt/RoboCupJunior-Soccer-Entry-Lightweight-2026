#include "Arduino.h"
#include "motor.h"
#include "config.h"

Motor::Motor(
    int location_angle,
    int pin_1,
    int pin_2,
    int direction,
    int angle_coef,
    int angle_speed_coef,
    int cos_coef,
    double min_speed,
    bool debug) : _location_angle{location_angle},
                  _pin_1{pin_1},
                  _pin_2{pin_2},
                  _direction{direction},
                  _angle_coef{angle_coef},
                  _angle_speed_coef{angle_speed_coef},
                  _cos_coef{cos_coef},
                  _min_speed{min_speed},
                  _debug{debug},
                  _rotation_speed{} {}

int Motor::_protect_speed(int speed, int min_speed)
{
    if (speed < 0)
    {
        if (speed > min_speed)
        {
            speed = min_speed;
        }
    }
    else if (speed > 0)
    {
        if (speed < min_speed)
        {
            speed = min_speed;
        }
    }

    return speed;
}

void Motor::set_velocity(double linear_speed, double angle, double angular_speed)
{
    float _move_speed{(double)_cos_coef * linear_speed * cos(_location_angle / 2 * DEG_TO_RAD + _angle_coef * angle * DEG_TO_RAD)};
    float _angular_speed{(double)_angle_speed_coef * angular_speed};

    _rotation_speed = _direction * round(_move_speed + _angular_speed);

    _rotation_speed = _protect_speed(_rotation_speed, _min_speed);

    if (_debug)
    {
        Serial.print("Motor:\t");
        Serial.print(_rotation_speed);
        Serial.print(" = ");
        Serial.print(_cos_coef * linear_speed);
        Serial.print(" * ");
        Serial.print("cos(");
        Serial.print(_location_angle / 2);
        Serial.print(" + ");
        Serial.print((double)_angle_coef * angle);
        Serial.print(") + ");
        Serial.println(_angular_speed);
    }
}

void Motor::run()
{
    if (_rotation_speed > 0)
    {
        digitalWrite(_pin_1, LOW);
        analogWrite(_pin_2, min(_rotation_speed, 255));
    }
    else
    {
        digitalWrite(_pin_2, LOW);
        analogWrite(_pin_1, min(-_rotation_speed, 255));
    }
}

void Motor::run(double speed)
{
    if (speed > 0)
    {
        digitalWrite(_pin_1, LOW);
        analogWrite(_pin_2, min(speed, 255));
    }
    else
    {
        digitalWrite(_pin_2, LOW);
        analogWrite(_pin_1, min(-speed, 255));
    }
}

void Motor::stop()
{
    digitalWrite(_pin_1, HIGH);
    digitalWrite(_pin_2, HIGH);
}

void Motor::debug()
{
    Serial.print("Motor \'");
    Serial.print(_location_angle);
    Serial.print("\':\t");
    Serial.print("PIN1:\t");
    Serial.print(_pin_1);
    Serial.print("\tPIN2:\t");
    Serial.print(_pin_2);
    Serial.print("\tSpeed:\t");
    Serial.println(_rotation_speed);
    Serial.println("==============================================");
    delay(100);
}