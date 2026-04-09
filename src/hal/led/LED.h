#pragma once

class LED
{
public:
    LED(int pin);
    void init();
    void on();
    void off();
private:
    int _pin;
};