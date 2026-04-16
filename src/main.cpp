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
#if DEBUG == false || DEBUG_MODE != 1
    Serial.println("Press A3 btn to start calibrating");
    robot.wait_for_btn(*(robot.start_btn()), []() {});
    robot.gyro()->calibrate();
    Serial.println("Finish calibrating");
    robot.signal();

    // 2. SET ZERO_ANGLE
    Serial.println("Press A5 btn to set zero angle");
    robot.wait_for_btn(*(robot.set_btn()), []()
                       { robot.gyro()->read(); });
    robot.gyro()->set_zero_angle(robot.gyro()->yaw());
    Serial.print("Zero angle set:\t");
    Serial.println(robot.gyro()->zero_angle());
    robot.signal();
#endif

    // WAIT FOR BTN TO START THE PROGRAM
    Serial.println("Press A3 btn to start the main code");
    robot.wait_for_btn(*(robot.start_btn()), []() {});

    delay(1000);
}

void loop()
{
    // 3. READING
    robot.read_sensors();

    if (robot.set_btn()->is_pressed())
    {
        robot.stop();
        delay(100);

        Serial.println("Press A5 btn to set zero angle");
        robot.wait_for_btn(*(robot.set_btn()), []()
                           { robot.gyro()->read(); });
        robot.gyro()->set_zero_angle(robot.gyro()->yaw());
        Serial.print("Zero angle set:\t");
        Serial.println(robot.gyro()->zero_angle());
        robot.signal();
        delay(100);
    }

    if (robot.start_btn()->is_pressed())
    {
        robot.stop();
        delay(100);

        Serial.println("Press A3 btn to start calibrating");
        robot.wait_for_btn(*(robot.start_btn()), []() {});
        robot.gyro()->calibrate();
        Serial.println("Finish calibrating");
        robot.signal();

        Serial.println("Press A5 btn to set zero angle");
        robot.wait_for_btn(*(robot.set_btn()), []()
                           { robot.gyro()->read(); });
        robot.gyro()->set_zero_angle(robot.gyro()->yaw());
        Serial.print("Zero angle set:\t");
        Serial.println(robot.gyro()->zero_angle());
        robot.signal();
        delay(100);
    }

#if DEBUG == false
    robot.set_angle();
    robot.set_speed(SPEED);
    robot.move();
#else
#if DEBUG_MODE == 0
    robot.set_angle();
    robot.set_speed(SPEED);
    robot.move();
#elif DEBUG_MODE == 1
    robot.ir_seeker()->debug();
#elif DEBUG_MODE == 2
    robot.move();
#elif DEBUG_MODE == 3
    robot.set_angle(ANGLE);
    robot.set_speed(SPEED);
    robot.move();
#elif DEBUG_MODE == 4
    robot.set_speed(SPEED);
    robot.move();
    robot.camera()->debug();
#elif DEBUG_MODE == 5
    robot.set_angle();
    robot.set_speed(SPEED);
    robot.move();
    robot.angle_control()->debug();
    robot.angle_control()->debug();
#endif
#endif
}