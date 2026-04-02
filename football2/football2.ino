#include "I2Cdev.h"
// #include "MPU6050.h"
#include "HTInfraredSeeker.h"

#include "gyro.h"
#include "button.h"
#include "IR.h"
#include "motor.h"
#include "PDC.h"
#include "camera.h"

#define M1_1 8
#define M1_2 9
#define M2_1 4
#define M2_2 5
#define M4_1 10
#define M4_2 11

//------------------------------------------SPEED------------------------------------------
#define SPEED 50

Gyro gyro;
Button btn{A3};
Button set_btn{A5};
IR ir{A14};
Motor m1{60, M1_1, M1_2, 1, 1};
Motor m2{180, M2_1, M2_2, 1, -1};
Motor m3{-60, M4_1, M4_2, 1, -1}; // если не будет работать, поменять на -60   СПРОСИТЬ ПРО ЭТО!!!!!!!!!   И ЕЩЕ ПРО СКОБКИ (ВНУТРИ Motor::set_velocity())
PDC pdc{0.05, 0.5, 0.00005};
Camera cam;

void setup()
{
    // 0. Initialization
    Serial.begin(115200);
    Wire.begin();

    Serial.println("Init");
    ir.init();
    gyro.init();
    btn.init();
    cam.init();
    Serial.println("Init complete");

    // 1. GYRO CALIBRATE
    Serial.println("Press A3 btn to start calibrating");
    while (!btn.is_pressed())
    {
        btn.read();
    }
    gyro.calibrate();
    Serial.println("Finish calibrating");

    // 2. SET ZERO_ANGLE
    Serial.println("Press A5 btn to set zero angle");
    while (!set_btn.is_pressed())
    {
        set_btn.read();
        gyro.read();
    }
    gyro.set_zero_angle(gyro.yaw());
    Serial.print("Zero angle set:\t");
    Serial.println(gyro.zero_angle());
    delay(1000);
}

void loop()
{
    // 3. READING
    ir.read();
    gyro.read();
    cam.read();
    set_btn.read();

    if (set_btn.is_pressed())
    {
        gyro.set_zero_angle(gyro.yaw());
    }

    //-----------------------------------------------------------MAIN CODE--------------------------------------------------
    if (ir.strength() > 0) // МЫ ВИДИМ МЯЧ
    {
        if (ir.angle() == 0) // ОН ПРЯМО ПЕРЕД НАМИ
        {
            m1.set_velocity(SPEED, ir.angle(), pdc.get(cam.error()));
            m2.set_velocity(SPEED, ir.angle(), pdc.get(cam.error()));
            m3.set_velocity(SPEED, ir.angle(), pdc.get(cam.error()));
        }
        else // ОН СБОКУ ИЛИ СЗАДИ
        {
            if (ir.strength() >= 10) // ОН БЛИЗКО
            {
                m1.set_velocity(SPEED, ir.angle() + 40, pdc.get(cam.error()));
                m2.set_velocity(SPEED, ir.angle() + 40, pdc.get(cam.error()));
                m3.set_velocity(SPEED, ir.angle() + 40, pdc.get(cam.error()));
            }
            else // ОН ДАЛЕКО
            {
                m1.set_velocity(SPEED, ir.angle() + 10, pdc.get(cam.error()));
                m2.set_velocity(SPEED, ir.angle() + 10, pdc.get(cam.error()));
                m3.set_velocity(SPEED, ir.angle() + 10, pdc.get(cam.error()));
            }
        }
    }
    else // МЫ НЕ ВИДИМ МЯЧ
    {
        m1.set_velocity(SPEED, 150, pdc.get(cam.error()));
        m2.set_velocity(SPEED, 150, pdc.get(cam.error()));
        m3.set_velocity(SPEED, 150, pdc.get(cam.error()));
    }
}