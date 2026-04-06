#include "include.h"
class IR
{
public:
    IR(int pin = A14, float min_strength, bool debug = false);
    void init() noexcept;
    void read();
    float angle() const noexcept;
    float strength() const noexcept;
    float min_strength() const noexcept;
    void debug() const noexcept;

private:
    InfraredSeeker _IR;
    int _pin;
    float _angle;
    float _strength;

    float _min_strength;

    bool _debug{};
};