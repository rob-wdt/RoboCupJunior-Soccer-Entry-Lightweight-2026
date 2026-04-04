#include "Arduino.h"
#include "motor.h"
#include "config.h"

Motor::Motor(int location_angle, int pin_1, int pin_2, int direction, int angle_coef, bool debug = false) : _location_angle{location_angle}, _pin_1{pin_1}, _pin_2{pin_2}, _direction{direction}, _angle_coef{angle_coef}, _debug{debug}, _rotation_speed{} {}

void Motor::set_velocity(float linear_speed, float angle, float angular_speed)
{
    _rotation_speed = _direction * (linear_speed * cosf(_location_angle / 2 * DEG_TO_RAD + _angle_coef * angle * DEG_TO_RAD) + round(angular_speed));

    if (_debug)
    {
        Serial.print(_rotation_speed);
        Serial.print(" = ");
        Serial.print((_direction));
        Serial.print(" * ");
        Serial.print(" (");
        Serial.print(linear_speed);
        Serial.print(" * ");
        Serial.print("cos(");
        Serial.print(_location_angle / 2);
        Serial.print(" + ");
        Serial.print(_angle_coef * angle);
        Serial.print(") + ");
        Serial.print(angular_speed);
        Serial.println(")");
    }

    if (abs(_rotation_speed) < MIN_SPEED)
    {
        if(_rotation_speed > 0)
        {
            _rotation_speed = map(_rotation_speed, 0, 255, MIN_SPEED, 255);
        }
        else if(_rotation_speed < 0)
        {
            _rotation_speed = map(_rotation_speed, -255, 0, -255, -MIN_SPEED);
        }
    }
}

void Motor::run()
{
    float _speed = _direction * _rotation_speed;

    if (_speed > 0)
    {
        digitalWrite(_pin_1, LOW);
        analogWrite(_pin_2, min(_speed, 255));
    }
    else
    {
        digitalWrite(_pin_2, LOW);
        analogWrite(_pin_1, min(-_speed, 255));
    }
}

void Motor::run(int speed)
{
    speed *= _direction;

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