#pragma once

#include "include.h"
#include "..\gyro.h"

class Bno055 : public Gyro
{
public:
    Bno055(int id = 0, uint8_t address = 0x28, bool debug = false);
    void init() override final;
    void calibrate() override final;
    void read() override final;
    void debug() const noexcept override final;

private:
    int _id;
    Adafruit_BNO055 _bno;
    sensors_event_t _event;
};