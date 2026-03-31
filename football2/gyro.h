#include <stdint.h>
#include "MPU6050.h"

class Gyro
{
public:
  Gyro(uint8_t I2C_address = 0x68);
  void init();
  void calibrate();
  void read();
  float yaw();
  float zero_angle();
  void set_zero_angle(float new_angle);
private:
  MPU6050 _mpu;
  float _zero_angle;
  uint8_t _fifo_buffer[64];
  float _yaw;
};