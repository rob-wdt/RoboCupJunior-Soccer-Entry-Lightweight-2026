#include "Arduino.h"
#include "config.h"
#include "exp.h"

Exp::Exp(float k1, float k2, bool debug = false) : _k1{k1}, _k2{k2}, _debug{debug} {}

float Exp::get(float error)
{
    float _u{_k1 * pow(E, _k2 * error)};

    if(_debug)
    {
        Serial.print("Exp:\t");
        Serial.print(_u);
        Serial.print(" = ");
        Serial.print(_k1);
        Serial.print(" * ");
        Serial.print(E);
        Serial.print("^");
        Serial.print("( ");
        Serial.print(_k2);
        Serial.print(" * ");
        Serial.print(error);
        Serial.println(")");
    }

    return _u;
}

void Exp::debug()
{
    Serial.print("Exponential control:\tk1:\t");
    Serial.print(_k1);
    Serial.print("\tk2:\t");
    Serial.print(_k2);
    Serial.println("============================================");
}