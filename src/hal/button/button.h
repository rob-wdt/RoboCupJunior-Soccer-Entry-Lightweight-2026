#pragma once
#include "pins_arduino.h"

class Button
{
public:
    Button(unsigned pin, bool debug);
    void init() noexcept;
    void read() noexcept;
    bool is_pressed() const noexcept;
    void reset();
    void debug() const noexcept;

private:
    unsigned _pin;
    bool _is_pressed{};

    bool _debug{};
};