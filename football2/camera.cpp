#include "HardwareSerial.h"
#include "Arduino.h"
#include "camera.h"

Camera::Camera(bool debug = false) : _debug{debug} {}

void Camera::init()
{
    if (_debug)
    {
        Serial.println("Camera: INIT BEGIN");
    }

    Serial1.begin(115200);

    int _val{};
    while (_val != 0xFF)
    {
        if (Serial1.available())
        {
            _val = Serial1.read();
        }
        Serial1.write(0xFF);

        if (_debug)
        {
            Serial.println("Camera: WAIT FOR SIGNAL");
        }
    }
    Serial.println("Camera: TEST CONNECTION SUCCEED");
}

void Camera::read()
{
    if (Serial1.available())
    {
        _error = Serial1.read();
    }
}

float Camera::error()
{
    return _error;
}

void Camera::debug()
{
    Serial.print("Camera:\t");
    Serial.print("Error:\t");
    Serial.println(_error);
    Serial.println("==============================================");
}