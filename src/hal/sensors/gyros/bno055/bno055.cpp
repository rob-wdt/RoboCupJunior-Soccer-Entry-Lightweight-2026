#include "bno055.h"

Bno055::Bno055(int id = 0, uint8_t address = 0x28, bool debug = false) : Gyro::Gyro(address, debug), _id{id}, _bno{_id, address} {}

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

    if (_yaw < -180)
    {
        _yaw += 360;
    }
    else if (_yaw > 180)
    {
        _yaw -= 360;
    }
}

void Bno055::debug() const noexcept
{
    Serial.print("Gyroscope:\tBNO055:\t");
    Serial.print("Current yaw:\t");
    Serial.println(_yaw);
    Serial.println("==============================================");
    delay(100);
}