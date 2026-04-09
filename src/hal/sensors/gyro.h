#pragma once

class Gyro
{
public:
    Gyro(int address, bool debug = false) : _address{address}, _debug{debug} {}
    virtual void init() {}
    virtual void calibrate() {}
    virtual void read() {}
    virtual float yaw() const noexcept {}
    virtual void set_zero_angle(float new_angle) {}
    virtual float zero_angle() const noexcept {}
    virtual void debug() const noexcept {}

protected:
    int _address{};
    float _yaw{};
    float _zero_angle{};

    bool _debug{};
};