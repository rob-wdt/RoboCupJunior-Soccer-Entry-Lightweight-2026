#include "IR.h"

IR::IR(int pin = A14, bool debug = false) : _pin{pin}, _debug{debug}, _angle{}, _strength{} {}

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