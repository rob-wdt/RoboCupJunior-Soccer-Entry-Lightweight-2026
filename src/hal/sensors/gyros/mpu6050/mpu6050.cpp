#include "Arduino.h"
#include "helper_3dmath.h"
#include "include.h"
#include "mpu6050.h"

Mpu6050::Mpu6050(int address = 0x68, bool debug = false) : Gyro::Gyro{address, debug}, _mpu{address} {}

void Mpu6050::init()
{
    if (_debug)
    {
        Serial.println("Gyroscope: MPU6050: INIT");
    }

    _mpu.initialize();

    if (_debug)
    {
        Serial.println("Gyroscope: MPU6050: MPU INIT COMPLETE");
    }

    if (!_mpu.testConnection())
    {
        Serial.println("Gyroscope: MPU6050: NO CONNECTION");
    }
    else
    {
        Serial.println("Gyroscope: MPU6050: TEST CONNECTION SUCCESFUL");
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
            Serial.print("MPU6050:\t");
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

void Mpu6050::debug() const noexcept
{
    Serial.print("Gyroscope:\tMPU6050:\t");
    Serial.print("Current yaw:\t");
    Serial.println(_yaw);
    Serial.println("==============================================");
    delay(100);
}