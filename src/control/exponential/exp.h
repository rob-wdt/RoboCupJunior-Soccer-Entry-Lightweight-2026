#pragma once
#include "..\regulator.h"

class Exp : public Regulator
{
public:
    Exp(float k1, float k2, bool debug);
    float get(float error) override final;
    void debug() override final;

private:
    float _k1;
    float _k2;

    bool _debug;
};