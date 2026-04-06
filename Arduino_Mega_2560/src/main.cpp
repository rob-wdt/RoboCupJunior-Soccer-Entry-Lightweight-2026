#include <Arduino.h>

#include "include.h"
#include "config.h"
#include ".\robot\robot.h"

Robot robot{
    Gyro{0x68, true},
    Button{A3},
    Button{A5},
    LED{47},
    IR{A14, true},
    Motor{60, M1_1, M1_2, 1, 1, 1, MIN_SPEED},
    Motor{180, M2_1, M2_2, -1, 1, 1, MIN_SPEED},
    Motor{60, M4_1, M4_2, -1, -1, 1, MIN_SPEED},
    PDC{1, 1, 1},
    PDC{0.05, 0.5, 0.00005},
    Camera{},
    true};

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
    robot.gyro()->calibrate();
    robot.signal();

    // 2. SET ZERO_ANGLE
    robot.gyro()->set_zero_angle(robot.gyro()->yaw());
    robot.signal();
}

void loop()
{
    // 3. READING
    robot.read_sensors();

    if (robot.set_btn()->is_pressed())
    {
        robot.stop();
        delay(1000);

        Serial.println("Press A5 btn to set zero angle");
        while (!robot.set_btn()->is_pressed())
        {
            robot.set_btn()->read();
            robot.gyro()->read();
        }
        robot.set_btn()->reset();
        robot.gyro()->set_zero_angle(robot.gyro()->yaw());
        Serial.print("Zero angle set:\t");
        Serial.println(robot.gyro()->zero_angle());
        robot.signal();
    }

    if (robot.start_btn()->is_pressed())
    {
        robot.stop();
        delay(100);

        Serial.println("Press A3 btn to start calibrating");
        while (!robot.start_btn()->is_pressed())
        {
            robot.start_btn()->read();
        }
        robot.start_btn()->reset();
        robot.gyro()->calibrate();
        Serial.println("Finish calibrating");
        robot.signal();

        Serial.println("Press A5 btn to set zero angle");
        while (!robot.set_btn()->is_pressed())
        {
            robot.set_btn()->read();
            robot.gyro()->read();
        }
        robot.set_btn()->reset();
        robot.gyro()->set_zero_angle(robot.gyro()->yaw());
        Serial.print("Zero angle set:\t");
        Serial.println(robot.gyro()->zero_angle());
        robot.signal();
    }

    robot.set_speed(SPEED);
    robot.move();
}