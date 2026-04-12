#pragma once
#include "..\regulator.h"

class PDC : public Regulator
{
public:
    PDC(float kp, float kd, float kc, bool debug);
    float get(float error) override final; // САМ ПДК РЕГУЛЯТОР
    void debug() override final;

private:
    float _kp;
    float _kd;
    float _kc;
    float _error;
    float _prev_error{};

    bool _debug{};
};