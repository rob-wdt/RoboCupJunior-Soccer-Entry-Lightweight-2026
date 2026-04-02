#include "pins_arduino.h"
class Button
{
public:
    Button(int pin = A3, bool debug = false);
    void init() noexcept;
    void read() noexcept;
    bool is_pressed() const noexcept;
    void debug() const noexcept;

private:
    int _pin;
    bool _is_pressed{};

    bool _debug{};
};