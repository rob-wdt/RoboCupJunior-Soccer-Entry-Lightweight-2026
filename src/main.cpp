#include <Arduino.h>

#include "include.h"
#include "config.h"

#include ".\robot\robot.h"
#include ".\robot\objects.h"

Robot robot{
    objects::mpu,
    objects::start_btn,
    objects::set_btn,
    objects::signal,
    objects::ir_seeker,
    objects::motor_1,
    objects::motor_2,
    objects::motor_3,
    objects::controls::cam_cont,
    objects::controls::gyro_cont,
    objects::controls::angle_cont,
    objects::controls::dist_cont,
    objects::camera,
    DEBUG};

void setup()
{
    // 0. Initialization
    Serial.begin(115200);
    Wire.begin();
    Wire.setClock(100000);

    Serial.println("Init");
    robot.init();
    Serial.println("Init complete");
    robot.signal();

    // 1. GYRO CALIBRATE
    Serial.println("Press A3 btn to start calibrating");
    robot.start_btn()->reset();
    while (!robot.start_btn()->is_pressed())
    {
        robot.start_btn()->read();
    }
    robot.start_btn()->reset();
    robot.gyro()->calibrate();
    Serial.println("Finish calibrating");
    robot.signal();

    // 2. SET ZERO_ANGLE
    Serial.println("Press A5 btn to set zero angle");
    robot.set_btn()->reset();
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

    // WAIT FOR BTN TO START THE PROGRAM
    Serial.println("Press A3 btn to start the main code");
    robot.start_btn()->reset();
    while (!robot.start_btn()->is_pressed())
    {
        robot.start_btn()->read();
    }
    robot.start_btn()->reset();

    delay(1000);
}

void loop()
{
    // 3. READING
    robot.read_sensors();

    if (robot.set_btn()->is_pressed())
    {
        robot.set_btn()->reset();
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
        delay(100);
    }

    if (robot.start_btn()->is_pressed())
    {   
        robot.start_btn()->reset();
        robot.set_btn()->reset();
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
        delay(100);
    }

    robot.set_speed(SPEED);
    robot.move();

    //robot.ir_seeker()->debug();
}