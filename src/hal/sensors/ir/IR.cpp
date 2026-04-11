#include "IR.h"

IR::IR(int pin, int min_strength, int max_strength, int medium_strength, bool debug = false) : _pin{pin}, _min_strength{min_strength}, _max_strength{max_strength}, _med_strength{medium_strength}, _debug{debug}, _angle{}, _strength{} {}

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
        _strength = _max_strength;
    }
    else if (_strength < _min_strength)
    {
        _strength = _min_strength;
    }
    _strength = map(_strength, _min_strength, _max_strength, 0, 1);
}

float IR::angle() const noexcept
{
    return _angle;
}

int IR::min_strength() const noexcept
{
    return _min_strength;
}

int IR::max_strength() const noexcept
{
    return _max_strength;
}

int IR::med_strength() const noexcept
{
    return _med_strength;
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