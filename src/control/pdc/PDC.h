#pragma once
#include "..\regulator.h"

class PDC : public Regulator
{
public:
    PDC(double kp, double kd, double kc, bool debug);
    double get(double error) override final; // САМ ПДК РЕГУЛЯТОР
    void debug() override final;

private:
    double _kp;
    double _kd;
    double _kc;
    double _error;
    double _prev_error{};

    bool _debug{};
};