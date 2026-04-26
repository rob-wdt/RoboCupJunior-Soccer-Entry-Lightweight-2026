#include "bno055.h"

Bno055::Bno055(int id, uint8_t address = 0x28, bool debug = false) : Gyro::Gyro(address, debug), _id{id}, _bno{_id, address, &Wire} {}

void Bno055::init(LED signal_led)
{
    if (!_bno.begin())
    {
        Serial.println("Gyroscope: BNO055: NO CONNECTION");

        signal_led.on();
        delay(1000);
        signal_led.off();

        while (true)
            ;
    }

    _bno.setExtCrystalUse(true);
}

void Bno055::calibrate(LED signal_led)
{
    uint8_t _system, _gyro, _accel, _mag = 0;
    _bno.getCalibration(&_system, &_gyro, &_accel, &_mag);

    int _timer{millis()};
    while (_gyro != 3)
    {
        Serial.print("Gyroscope: BNO055: Calibration state: Gyro:\t");
        Serial.println(_gyro);

        if (millis() - _timer <= 100)
        {
            signal_led.on();
        }
        else
        {
            signal_led.off();
            _timer = millis();
        }
    }
}

void Bno055::read()
{
    _bno.getEvent(&_event);
    _yaw = _event.orientation.x - _zero_angle; // у bno055 (по крайней мере у этого) оси расположены по другому, поэтому берем x, а не z

    _yaw = _protect_angle(_yaw);

    if (_debug)
    {
        Serial.print("Gyroscope:\tBNO055:\t");
        Serial.print(_yaw);
        Serial.print(" = ");
        Serial.print(_protect_angle(_event.orientation.x));
        Serial.print(" - ");
        Serial.println(_zero_angle);
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