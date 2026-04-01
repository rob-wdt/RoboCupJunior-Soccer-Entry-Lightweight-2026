#include "I2Cdev.h"
#include "MPU6050.h"
#include "HTInfraredSeeker.h"

Gyro gyro;
Button btn(A3);

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  //1. GYRO CALIBRATE
  gyro.init();
  gyro.calibrate();

  //2. SET ZERO_ANGLE
  while (!btn.is_pressed())
  {
    btn.read();
    gyro.read();
  }
  gyro.set_zero_angle(gyro.yaw());
}

void loop()
{
  //3. READ IR
  //4. READ GYRO
  //5. IF THE BALL IS FAR
    //IF THE BALL IS BEHIND US
      //VELOCITY = LINEAR_SPEED, IR.angle + 30, PDC(GYRO.YAW - ZERO_ANGLE)
    //IF THE BALL IS AHEAD
      //VELOCITY = LINEAR_SPEED, IR.angle, PDC(GYRO.YAW - ZERO_ANGLE)
  //IF WE HAVE THE BALL
    //VELOCITY = LINEAR_SPEED, 0, PDC(GYRO.YAW - ZERO_ANGLE)
}