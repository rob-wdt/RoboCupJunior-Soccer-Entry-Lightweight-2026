#include "HardwareSerial.h"
#include "Arduino.h"
#include "camera.h"

Camera::Camera(bool debug) : _debug{debug} {}

void Camera::init()
{
    if (_debug)
    {
        Serial.println("Camera: INIT BEGIN");
    }

    Serial1.begin(115200);

    // Test connection
    int _val{};
    while (_val != 0xFF)
    {
        _val = Serial1.read();

        if (_debug)
        {
            Serial.println("Camera: WAIT FOR SIGNAL");
        }
    }
    for (int i{}; i < 10; i++)
    {
        Serial1.write(0xFF);
        delay(100);
    }
    Serial.println("Camera: TEST CONNECTION SUCCEED");
}

void Camera::read()
{
    if (Serial1.available() == 1)
    {
        _error = Serial1.read();
    }
}

int Camera::error()
{
    return _error;
}

bool Camera::sees_gates()
{
    if (_error < 255) // видим ворота
    {
        if (_debug)
        {
            Serial.println("Camera:\tDETECTED GATES");
        }

        return true;
    }

    else if (_error == 255) // невидим ворота
    {
        if (_debug)
        {
            Serial.println("Camera:\tNOT DETECTED GATES");
        }

        return false;
    }
}

void Camera::debug()
{
    Serial.print("Camera:\t");
    Serial.print("Error:\t");
    Serial.println(_error);
    Serial.println("==============================================");
}