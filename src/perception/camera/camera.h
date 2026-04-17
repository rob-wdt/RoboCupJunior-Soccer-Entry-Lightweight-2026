#pragma once

class Camera
{
public:
    Camera(bool debug);
    void init();
    void read();
    int error(); // разница между центральным пикселем камеры и центральным пикселем ворот
    bool sees_gates();
    void debug();

private:
    int _error;

    bool _debug{};
};