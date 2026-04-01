#include "helper_3dmath.h"
#include "Arduino.h"
#include "gyro.h"

Gyro::Gyro(uint8_t I2C_address = 0x68) : _mpu{I2C_address} {}

void Gyro::init()
{
  _mpu.initialize();

  if (!_mpu.testConnection())
  {
    Serial.println("Gyroscope: NO CONNECTION");
  }

  _mpu.setDMPEnabled(true);   
}

void Gyro::calibrate()
{
  Serial.println("Gyroscope: CALIBRATING");

  _mpu.setXGyroOffset(0);
  _mpu.setYGyroOffset(0);
  _mpu.setZGyroOffset(0);

  _mpu.CalibrateGyro();
  _mpu.PrintActiveOffsets();
}

void Gyro::read()
{
  if(_mpu.dmpGetCurrentFIFOPacket(_fifo_buffer))
  {
    Quaternion q;
    VectorFloat gravity;
    float ypr[3];

    _mpu.dmpGetQuaternion(&q, _fifo_buffer);
    _mpu.dmpGetGravity(&gravity, &q);
    _mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    _yaw = ypr[0];
  }
}

float Gyro::yaw()
{
  return _yaw;
}

float Gyro::zero_angle()
{
  return _zero_angle;
}

void Gyro::set_zero_angle(float new_angle)
{
  _zero_angle = new_angle;
}

void Gyro::debug()
{
  Serial.print("Gyro:\t");
  Serial.print("Zero angle:\t");
  Serial.print(_zero_angle);
  Serial.print('\t');
  Serial.print("Current yaw:\t");
  Serial.println(_yaw);
  Serial.println("==============================================");
}