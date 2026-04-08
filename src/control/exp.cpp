#include "Arduino.h"
#include "config.h"
#include "exp.h"

Exp::Exp(float k1, float k2, bool debug = false) : _k1{k1}, _k2{k2}, _debug{debug} {}

float Exp::get(float error)
{
    float u{_k1 * pow(E, _k2 * error)};
    return u;
}