#include "Arduino.h"
#include "button.h"

Button::Button(unsigned pin, bool debug) : _pin{pin}, _is_pressed{false}, _debug{debug} {}

void Button::init() noexcept
{
    pinMode(_pin, INPUT);
}

void Button::read() noexcept
{
    int _data{analogRead(_pin)};
    if (_data > 200)
    {
        _is_pressed = true;
    }
    else
    {
        _is_pressed = false;
    }

    if (_debug)
    {
        Serial.print("Button \'");
        Serial.print(_pin);
        Serial.print("\':\t");
        Serial.print("Pressed:\t");
        Serial.println(_is_pressed);
        Serial.println("==============================================");
    }
}

bool Button::is_pressed() const noexcept
{
    return _is_pressed;
}

void Button::reset()
{
    _is_pressed = false;
}

void Button::debug() const noexcept
{
    Serial.print("Button \'");
    Serial.print(_pin);
    Serial.print("\':\t");
    Serial.print("Pressed:\t");
    Serial.println(_is_pressed);
    Serial.println("==============================================");
    // delay(1000);
}