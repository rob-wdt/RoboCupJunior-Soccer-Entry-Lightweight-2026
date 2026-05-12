#include "IR.h"

IR::IR(int pin, int min_strength, int max_strength, int medium_strength, bool debug = false) : _pin{pin}, _min_strength{min_strength}, _max_strength{max_strength}, _med_strength{medium_strength}, _debug{debug}, _angle{}, _strength{} {}

void IR::_defense()
{
    if (abs(_angle) - abs(_prev_angle) >= 60)
    {
        _angle = _prev_angle;
    }

    if (abs(_angle) <= 90 && _strength - _min_strength <= 30)   //иногда случаются глюки, и он не видя мяч, показывает 60 или 30 градусов
    {
        if (_angle < 0)
        {
            _angle = -180;
        }

        else if (_angle > 0)
        {
            _angle = 180;
        }
    }
}

void IR::init() noexcept
{
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
}

void IR::read()
{
    InfraredResult res{_IR.ReadAC()};
    _angle = (res.Direction - 5) * 30;

    _strength = res.Strength;
    if (_strength > _max_strength)
    {
        _strength = (double)_max_strength;
    }
    else if (_strength < _min_strength)
    {
        _strength = (double)_min_strength;
    }

    _defense();
    _prev_angle = _angle;
}

bool IR::object_is_far() const noexcept
{
    if (_strength < _max_strength)
    {
        return true;
    }

    else if (_strength >= _max_strength)
    {
        return false;
    }
}

bool IR::object_is_behind() const noexcept
{
    if (abs(_angle) <= 60)
    {
        return false;
    }

    else if (abs(_angle) > 60)
    {
        return true;
    }
}

float IR::angle() const noexcept
{
    return _angle;
}

float IR::strength() const noexcept
{
    return _strength;
}

void IR::debug() const noexcept
{
    Serial.print("IR Seeker:\t");
    Serial.print("Angle:\t");
    Serial.print(_angle);
    Serial.print("\tStrength:\t");
    Serial.println(_strength);
    Serial.println("==============================================");
    delay(100);
}
