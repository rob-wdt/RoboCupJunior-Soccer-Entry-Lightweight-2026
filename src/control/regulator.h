#pragma once

class Regulator // General control, to be inherited by others
{
public:
    virtual float get(float error) {}
    virtual void debug() {}

private:
};