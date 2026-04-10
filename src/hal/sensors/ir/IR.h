#pragma once
#include "include.h"

class IR
{
public:
    IR(int pin, int min_strength, bool debug = false);
    void init() noexcept;
    void read();
    float angle() const noexcept;
    int min_strength() const noexcept;
    float strength() const noexcept; // если больше 180, мяч у нас
    void debug() const noexcept;

private:
    InfraredSeeker _IR;
    int _pin;
    float _angle;
    float _strength;
    int _min_strength;

    bool _debug{};
};