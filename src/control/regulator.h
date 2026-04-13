#pragma once

class Regulator // General control, to be inherited by others
{
public:
    virtual double get(double error) { return 0; }
    virtual void debug() {}

private:
};