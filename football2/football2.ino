#include "I2Cdev.h"
// #include "MPU6050.h"
#include "HTInfraredSeeker.h"

#include "config.h"
#include "robot.h"

#define M1_1 8
#define M1_2 9
#define M2_1 4
#define M2_2 5
#define M4_1 10
#define M4_2 11

Gyro gyro{0x68, true};
Button gyro_btn{A3}; //GYRO START CALIBRATING BUTTON
Button set_btn{A5}; //GYRO SET ZERO ANGLE BUTTON
IR ir{A14, true}; 
Motor m1{60, M1_1, M1_2, 1, 1, 1, MIN_SPEED};     //M1
Motor m2{180, M2_1, M2_2, -1, 1, 1, MIN_SPEED};    //M2
Motor m3{60, M4_1, M4_2, -1, -1, 1, MIN_SPEED};    //M3 
PDC cam_pdc{1, 1, 1};               //CAMERA REGULATOR
PDC gyro_pdc{0.07, 0.5, 0.0001};    //GYRO REGULATOR
Camera cam{};

Robot robot{gyro, gyro_btn, set_btn, ir, m1, m2, m3, cam_pdc, gyro_pdc, cam, true};

void setup()
{
    // 0. Initialization
    Serial.begin(115200);
    Wire.begin();

    pinMode(49, OUTPUT);    //SIGNAL LED

    Serial.println("Init");
    robot.init();
    Serial.println("Init complete");

    // 1. GYRO CALIBRATE
    robot.calibrate_gyro();
    digitalWrite(49, HIGH); //СВЕТОДИОД, СИГНАЛИЗАЦИЯ ОКОНЧАНИЯ КАЛИБРОВКИ
    delay(100);
    digitalWrite(49, LOW);

    // 2. SET ZERO_ANGLE
    robot.set_gyro_zero_angle();
    digitalWrite(49, HIGH); //СВЕТОДИОД, СИГНАЛИЗАЦИЯ ОКОНЧАНИЯ КАЛИБРОВКИ
    delay(100);
    digitalWrite(49, LOW);
}

void loop()
{
    // 3. READING
    robot.read_sensors();

    //-----------------------------------------------------------MAIN CODE--------------------------------------------------
    robot.set_speed(SPEED);
    robot.move();
    robot._ir.debug();  
}