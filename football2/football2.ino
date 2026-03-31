#include "I2Cdev.h"
#include "MPU6050.h"
#include "HTInfraredSeeker.h"

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  //1. GYRO CALIBRATE
  //2. SET ZERO_ANGLE
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