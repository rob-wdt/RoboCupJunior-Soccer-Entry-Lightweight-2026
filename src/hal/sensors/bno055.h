#pragma once

#include "include.h"
#include "gyro.h"

class Bno055 : public Gyro
{
public:
    Bno055(int id = 0, int address = 0x28, bool debug = false);
    void init() override final;
    void calibrate() override final;
    void read() override final;
    float yaw() const noexcept override final;
    void set_zero_angle(float new_ange) override final;
    float zero_angle() const noexcept override final;
    void debug() const noexcept override final;

private:
    Adafruit_BNO055 _bno;
    int _id;
    sensors_event_t _event;
};