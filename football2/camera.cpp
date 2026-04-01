#include "Arduino.h"
#include "camera.h"

void Camera::read()
{
    Serial.begin(115200);
    _error = Serial.read();
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
    Serial.println("==============================================")
}