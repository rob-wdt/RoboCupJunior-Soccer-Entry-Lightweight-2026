#pragma once

class Camera
{
public:
    Camera(bool debug);
    void init();
    void read();
    float error(); // разница между центральным пикселем камеры и центральным пикселем ворот
    void debug();

private:
    float _error;

    bool _debug{};
};