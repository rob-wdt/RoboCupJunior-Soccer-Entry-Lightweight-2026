class PDC
{
public:
    PDC(float kp, float kd, float kc);
    float get(float error); // САМ ПДК РЕГУЛЯТОР
    void debug();

private:
    float _kp;
    float _kd;
    float _kc;
    float _error;
    float _prev_error{};
};