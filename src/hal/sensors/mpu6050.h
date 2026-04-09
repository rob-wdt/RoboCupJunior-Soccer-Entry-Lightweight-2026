#pragma once

#include <stdint.h>
// #include "MPU6050.h"
#include "include.h"
#include "gyro.h"

class Mpu6050 : public Gyro
{
public:
    Mpu6050(int address = 0x68, bool debug = false);
    void init() override final;
    void calibrate() override final;
    void read() override final;
    float yaw() const noexcept override final;
    float zero_angle() const noexcept override final;
    void set_zero_angle(float new_angle) noexcept override final;
    void debug() const noexcept override final;

private:
    MPU6050 _mpu;
    uint8_t _fifo_buffer[64];
    uint16_t _packet_size;
    Quaternion _q;
    VectorFloat _gravity;
    float _ypr[3];
};