#include "bno055.h"

Bno055::Bno055(int id = 0, int address = 0x28, bool debug = false) : Gyro::Gyro(address, debug), _id{id}, _bno{_id, address} {}

void Bno055::init()
{
    if (!_bno.begin())
    {
        Serial.println("Gyroscope: BNO055: NO CONNECTION");
        while (true)
            ;
    }

    _bno.setExtCrystalUse(true);
}

void Bno055::calibrate()
{
    uint8_t _system, _gyro, _accel, _mag = 0;
    _bno.getCalibration(&_system, &_gyro, &_accel, &_mag);

    while (_gyro != 3)
    {
        Serial.print("Gyroscope: BNO055: Calibration state: Gyro:\t");
        Serial.println(_gyro);
    }
}

void Bno055::read()
{
    _bno.getEvent(&_event);
    _yaw = _event.orientation.z - _zero_angle;
}

float Bno055::yaw() const noexcept
{
    return _yaw;
}

void Bno055::set_zero_angle(float new_angle)
{
    _zero_angle = new_angle;
}

float Bno055::zero_angle() const noexcept
{
    return _zero_angle;
}

void Bno055::debug() const noexcept
{
    Serial.print("Gyroscope:\tBNO055:\t");
    Serial.print("Current yaw:\t");
    Serial.println(_yaw);
    Serial.println("==============================================");
    delay(100);
}