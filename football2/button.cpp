#include "Arduino.h"
#include "button.h"

Button::Button(int pin = A3) : _pin{pin}, _is_pressed{false} {}

void Button::init() noexcept
{
    pinMode(_pin, INPUT);
}

void Button::read() noexcept
{
    unsigned int _data{analogRead(_pin)};
    if (_data > 200)
    {
        _is_pressed = true;
    }
    else
    {
        _is_pressed = false;
    }
}

bool Button::is_pressed() const noexcept
{
    return _is_pressed;
}

void Button::debug() const noexcept
{
    Serial.print("Button \'");
    Serial.print(_pin);
    Serial.print("\':\t");
    Serial.print("Pressed:\t");
    Serial.println(_is_pressed);
    Serial.println("==============================================");
    delay(1000);
}