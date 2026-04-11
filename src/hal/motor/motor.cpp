#include "Arduino.h"
#include "motor.h"
#include "config.h"

Motor::Motor(int location_angle, int pin_1, int pin_2, int angle_coef, int angle_speed_coef, int cos_coef, int min_speed, bool debug = false) : _location_angle{location_angle}, _pin_1{pin_1}, _pin_2{pin_2}, _angle_coef{angle_coef}, _angle_speed_coef{angle_speed_coef}, _cos_coef{cos_coef}, _min_speed{min_speed}, _debug{debug}, _rotation_speed{} {}

void Motor::set_velocity(float linear_speed, float angle, float angular_speed)
{
    if (angle < -180)
    {
        angle += 360;
    }

    else if (angle > 180)
    {
        angle -= 360;
    }

    float _move_speed{(float)_cos_coef * linear_speed * cos(_location_angle / 2 * DEG_TO_RAD + _angle_coef * angle * DEG_TO_RAD)};
    float _angular_speed{(float)_angle_speed_coef * angular_speed};

    _rotation_speed = round(_move_speed + _angular_speed);

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

    if (_rotation_speed < 0)
    {
        _rotation_speed = map(_rotation_speed, -255, 0, -255, -_min_speed);
    }
    else if (_rotation_speed > 0)
    {
        _rotation_speed = map(_rotation_speed, 0, 255, _min_speed, 255);
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

void Motor::run(int speed)
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