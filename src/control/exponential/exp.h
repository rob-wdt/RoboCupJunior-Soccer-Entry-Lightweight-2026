#pragma once
#include "..\regulator.h"

class Exp : public Regulator
{
public:
    Exp(double k1, double k2, bool debug);
    double get(double error) override final;
    void debug() override final;

private:
    double _k1;
    double _k2;

    bool _debug;
};