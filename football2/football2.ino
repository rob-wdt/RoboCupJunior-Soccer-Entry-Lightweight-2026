#include "include.h"
#include "config.h"
#include "robot.h"

Gyro gyro{0x68, true};
Button gyro_btn{A3}; //GYRO START CALIBRATING BUTTON
Button set_btn{A5}; //GYRO SET ZERO ANGLE BUTTON
IR ir{A14, true}; 
Motor m1{60, M1_1, M1_2, 1, 1, 1, MIN_SPEED};     //M1
Motor m2{180, M2_1, M2_2, -1, 1, 1, MIN_SPEED};    //M2
Motor m3{60, M4_1, M4_2, -1, -1, 1, MIN_SPEED};    //M3 
PDC cam_pdc{1, 1, 1};               //CAMERA REGULATOR
PDC gyro_pdc{0.05, 0.5, 0.00005};    //GYRO REGULATOR
Camera cam{};
LED signal{47};

Robot robot{gyro, gyro_btn, set_btn, signal, ir, m1, m2, m3, cam_pdc, gyro_pdc, cam, true};

void setup()
{
    // 0. Initialization
    Serial.begin(115200);
    Wire.begin();

    Serial.println("Init");
    robot.init();
    Serial.println("Init complete");
    robot.signal();

    // 1. GYRO CALIBRATE
    robot.calibrate_gyro();
    robot.signal();

    // 2. SET ZERO_ANGLE
    robot.set_gyro_zero_angle();
    robot.signal();
}

void loop()
{
    // 3. READING
    robot.read_sensors(); 

    if (robot._set_btn.is_pressed())
    {
        robot.stop();
        delay(1000);
        robot.set_gyro_zero_angle();
        robot.signal();
    }

    if (robot._gyro_btn.is_pressed())
    {
        robot.stop();
        delay(100);
        robot.calibrate_gyro();
        robot.signal();
        robot.set_gyro_zero_angle();
        robot.signal();
    }

    robot.set_speed(SPEED);
    robot.move();
}