#pragma once
#include "include.h"

class IR
{
public:
    IR(int pin, int min_strength, int max_strength, int medium_strength, bool debug = false);
    void init() noexcept;
    void read();
    float angle() const noexcept;
    int min_strength() const noexcept;
    int max_strength() const noexcept;
    int med_strength() const noexcept;
    float strength() const noexcept; // если больше 180, мяч у нас
    void debug() const noexcept;

private:
    InfraredSeeker _IR;
    int _pin;
    double _angle;
    double _prev_angle{_angle};
    double _strength;
    const int _min_strength;
    const int _max_strength;
    const int _med_strength;

    bool _debug{};

    void _defense();
};