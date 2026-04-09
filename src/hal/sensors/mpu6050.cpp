#include "Arduino.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "helper_3dmath.h"
#include "mpu6050.h"

Mpu6050::Mpu6050(int address = 0x68, bool debug = false) : Gyro::Gyro{address, debug}, _mpu{address} {}

void Mpu6050::init()
{
    _mpu.initialize();

    if (!_mpu.testConnection())
    {
        Serial.println("Gyroscope: MPU6050: NO CONNECTION");
        
    }

    _mpu.dmpInitialize();

    _packet_size = _mpu.dmpGetFIFOPacketSize();

    _mpu.setDMPEnabled(true);
}

void Mpu6050::calibrate()
{
    Serial.println("Gyroscope: MPU6050: CALIBRATING");

    _mpu.setXGyroOffset(0);
    _mpu.setYGyroOffset(0);
    _mpu.setZGyroOffset(0);

    _mpu.CalibrateGyro(100);

    Serial.println();
    _mpu.PrintActiveOffsets();
}

void Mpu6050::read()
{
    if (_mpu.dmpGetCurrentFIFOPacket(_fifo_buffer))
    {
        _mpu.dmpGetQuaternion(&_q, _fifo_buffer);
        _mpu.dmpGetGravity(&_gravity, &_q);
        _mpu.dmpGetYawPitchRoll(_ypr, &_q, &_gravity);

        _yaw = -_ypr[0] * RAD_TO_DEG - _zero_angle;

        if (_debug)
        {
            Serial.print(_yaw);
            Serial.print(" = ");
            Serial.print(-_ypr[0] * RAD_TO_DEG);
            Serial.print(" - ");
            Serial.println(_zero_angle);
        }

        if (_yaw < -180)
        {
            _yaw += 360;
        }
        else if (_yaw > 180)
        {
            _yaw -= 360;
        }
    }
}

float Mpu6050::zero_angle() const noexcept
{
    return _zero_angle;
}

void Mpu6050::set_zero_angle(float new_angle) noexcept
{
    _zero_angle = new_angle;
}

float Mpu6050::yaw() const noexcept
{
    return _yaw;
}

void Mpu6050::debug() const noexcept
{
    Serial.print("Gyroscope:\tMPU6050:\t");
    Serial.print("Current yaw:\t");
    Serial.println(_yaw);
    Serial.println("==============================================");
    delay(100);
}