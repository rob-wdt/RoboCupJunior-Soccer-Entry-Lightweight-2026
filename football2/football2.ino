#include "I2Cdev.h"
#include "MPU6050.h"
#include "HTInfraredSeeker.h"

#include "gyro.h"
#include "button.h"
#include "IR.h"
#include "motor.h"

#define M1_1 8
#define M1_2 9
#define M2_1 4
#define M2_2 5
#define M4_1 10
#define M4_2 11

Gyro gyro;
Button btn{A3};
IR ir{A14};
Motor m1{60, M1_1, M1_2, 1, 1};
Motor m2{180, M2_1, M2_2, 1, -1};
Motor m3{300, M4_1, M4_2, 1, -1}; //если не будет работать, поменять на -60   СПРОСИТЬ ПРО ЭТО!!!!!!!!!   И ЕЩЕ ПРО СКОБКИ (ВНУТРИ Motor::set_velocity())
PDC pdc{0.8, 1.0, 0.5};

void setup()
{
  //0. Initialization
  Serial.begin(115200);
  Wire.begin();

  gyro.init();
  btn.init();
  ir.init();

  //1. GYRO CALIBRATE
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
  ir.read();

  //4. READ GYRO
  gyro.read();

  //5. IF THE BALL IS FAR
  if (ir.strength() < 180)
  {
    //IF THE BALL IS BEHIND US
    if (abs(ir.angle()) >= 60)
    {
      if (ir.angle() < 0)
      {
        //VELOCITY = LINEAR_SPEED, IR.angle + 30, PDC(GYRO.YAW - ZERO_ANGLE)
        m1.set_velocity(50, ir.angle() - 30, pdc.get(gyro.yaw() - gyro.zero_angle()));
        m2.set_velocity(50, ir.angle() - 30, pdc.get(gyro.yaw() - gyro.zero_angle()));
        m3.set_velocity(50, ir.angle() - 30, pdc.get(gyro.yaw() - gyro.zero_angle()));
      }
      else
      {
        //VELOCITY = LINEAR_SPEED, IR.angle + 30, PDC(GYRO.YAW - ZERO_ANGLE)
        m1.set_velocity(50, ir.angle() + 30, pdc.get(gyro.yaw() - gyro.zero_angle()));
        m2.set_velocity(50, ir.angle() + 30, pdc.get(gyro.yaw() - gyro.zero_angle()));
        m3.set_velocity(50, ir.angle() + 30, pdc.get(gyro.yaw() - gyro.zero_angle()));
      }
    }

    //IF THE BALL IS AHEAD
    else
    {
      //VELOCITY = LINEAR_SPEED, IR.angle, PDC(GYRO.YAW - ZERO_ANGLE)
      m1.set_velocity(50, ir.angle(), pdc.get(gyro.yaw() - gyro.zero_angle()));
      m2.set_velocity(50, ir.angle(), pdc.get(gyro.yaw() - gyro.zero_angle()));
      m3.set_velocity(50, ir.angle(), pdc.get(gyro.yaw() - gyro.zero_angle()));
    }
  //IF WE HAVE THE BALL
  else
  {
    //VELOCITY = LINEAR_SPEED, 0, PDC(GYRO.YAW - ZERO_ANGLE)
    m1.set_velocity(50, 0, pdc.get(gyro.yaw() - gyro.zero_angle()));
    m2.set_velocity(50, 0, pdc.get(gyro.yaw() - gyro.zero_angle()));
    m3.set_velocity(50, 0, pdc.get(gyro.yaw() - gyro.zero_angle()));
  }
}