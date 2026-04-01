#pragma once

class Camera
{
public:
  void read();
  float error();  //разница между центральным пикселем камеры и центральным пикселем ворот
  void debug();
private:
  float _error;
};