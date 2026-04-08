#include "Arduino.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "helper_3dmath.h"
#include "gyro.h"

Gyro::Gyro(uint8_t I2C_address = 0x68, bool debug = false) : _mpu{I2C_address}, _debug{debug}, _zero_angle{} {}

void Gyro::init()
{
    _mpu.initialize();

    if (!_mpu.testConnection())
    {
        Serial.println("Gyroscope: NO CONNECTION");
    }

    _mpu.dmpInitialize();

    _packet_size = _mpu.dmpGetFIFOPacketSize();

    _mpu.setDMPEnabled(true);
}

void Gyro::calibrate()
{
    Serial.println("Gyroscope: CALIBRATING");

    _mpu.setXGyroOffset(0);
    _mpu.setYGyroOffset(0);
    _mpu.setZGyroOffset(0);

    _mpu.CalibrateGyro(100);

    Serial.println();
    _mpu.PrintActiveOffsets();
}

void Gyro::read()
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

float Gyro::zero_angle() const noexcept
{
    return _zero_angle;
}

void Gyro::set_zero_angle(float new_angle) noexcept
{
    _zero_angle = new_angle;
}

float Gyro::yaw() const noexcept
{
    return _yaw;
}

void Gyro::debug() const noexcept
{
    Serial.print("Gyro:\t");
    Serial.print("Current yaw:\t");
    Serial.println(_yaw);
    Serial.println("==============================================");
    delay(100);
}