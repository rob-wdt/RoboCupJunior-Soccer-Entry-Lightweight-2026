#include "include.h"
#include "LED.h"

LED::LED(int pin) : _pin{pin} {}

void LED::init()
{
    pinMode(_pin, OUTPUT);
}

void LED::on()
{
    digitalWrite(_pin, HIGH);
}

void LED::off()
{
    digitalWrite(_pin, LOW);
}