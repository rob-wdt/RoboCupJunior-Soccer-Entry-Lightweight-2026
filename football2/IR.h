#include "HTInfraredSeeker.h"

class IR
{
public:
    IR(int pin = A14, bool debug = false);
    void init() noexcept;
    void read();
    float angle() const noexcept;
    float strength() const noexcept; // если больше 180, мяч у нас
    void debug() const noexcept;

private:
    InfraredSeeker _IR;
    int _pin;
    float _angle;
    float _strength;

    bool _debug{};
};