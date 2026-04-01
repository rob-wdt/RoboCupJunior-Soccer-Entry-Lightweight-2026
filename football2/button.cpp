#include "Arduino.h"
#include "button.h"

Button::Button(int pin = A3) : _pin{pin}, _is_pressed{false} {}

void Button::init()
{
    pinMode(_pin, INPUT);
}

void Button::read()
{
    unsigned short _data{analogRead(_pin)};
    if (_data > 200)
    {
        _is_pressed = true;
    }
    else
    {
        _is_pressed = false;
    }
}

bool Button::is_pressed()
{
    return _is_pressed;
}

void Button::debug()
{
    Serial.print("Button \'");
    Serial.print(_pin);
    Serial.print("\':\t");
    Serial.print("Pressed:\t");
    Serial.println(_is_pressed);
    Serial.println("==============================================");
    delay(1000);
}