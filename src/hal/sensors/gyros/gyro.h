#pragma once
#include "Arduino.h"

#include "..\..\led\LED.h"

class Gyro
{
public:
    Gyro(int address, bool debug) : _address{address}, _debug{debug} {}
    virtual void init(LED signal_led) {}
    virtual void calibrate(LED signal_led) {}
    virtual void read() {}
    float yaw() const noexcept { return _yaw; }
    void set_zero_angle(float new_angle) { _zero_angle = new_angle; }
    float zero_angle() const noexcept { return _zero_angle; }
    virtual void debug() const noexcept {}

protected:
    int _address{};
    float _yaw{};
    float _zero_angle{};

    bool _debug{};
};