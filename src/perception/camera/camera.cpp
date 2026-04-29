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

    Serial1.begin(230400);

    // // Test connection
    // if (_debug)
    // {
    //     int _val{};
    //     while (_val != 0xFF)
    //     {
    //         _val = Serial1.read();

    //         if (_debug)
    //         {
    //             Serial.println("Camera: WAIT FOR SIGNAL");
    //         }
    //     }
    //     for (int i{}; i < 10; i++)
    //     {
    //         Serial1.write(0xFF);
    //         delay(100);
    //     }
    //     Serial.println("Camera: TEST CONNECTION SUCCEED");
    // }
}

void Camera::read()
{
    if (Serial1.available())
    {
        _error = Serial1.read();

        if (_debug)
        {
            Serial.print("Camera:\tREAD ERROR:\t");
            Serial.println(_error);
        }
    }
}

signed char Camera::error()
{
    return _error;
}

bool Camera::sees_gates()
{
    if (abs(_error) == 0) // не видим ворота
    {
        if (_debug)
        {
            Serial.println("Camera: NOT DETECTED GATES");
        }
        return false;
    }
    else
    {
        if (_debug)
        {
            Serial.println("Camera: DETECTED GATES");
        }
        return true;
    }
}

void Camera::debug()
{
    Serial.print("Camera:\t");
    Serial.print("Error:\t");
    Serial.println(_error);
    Serial.println("==============================================");
    // delay(500);
}