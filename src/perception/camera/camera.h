#pragma once

class Camera
{
public:
    Camera(bool debug);
    void init();
    void read();
    signed char error(); // разница между центральным пикселем камеры и центральным пикселем ворот
    bool sees_gates();
    void debug();

private:
    signed char _error;

    const double _k_error{0.9};

    bool _debug{};
};