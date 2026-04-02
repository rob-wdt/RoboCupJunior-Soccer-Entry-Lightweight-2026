#pragma once
#include <stdint.h>
// #include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"

class Gyro
{
public:
    Gyro(uint8_t I2C_address = 0x68);
    void init();
    void calibrate();
    void read();
    float yaw() const noexcept;
    float zero_angle() const noexcept;
    void set_zero_angle(float new_angle) noexcept;
    void debug() const noexcept;

private:
    MPU6050 _mpu;
    float _zero_angle{};
    uint8_t _fifo_buffer[64];
    uint16_t _packet_size;
    Quaternion _q;
    VectorFloat _gravity;
    float _ypr[3];
    float _yaw;
};