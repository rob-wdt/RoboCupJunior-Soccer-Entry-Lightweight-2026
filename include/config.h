#pragma once

//---------------MATH-----------------
#define E 2.71828

//------------------SPEED-------------
#define MIN_SPEED 55
#define SPEED 60

//-----------------MPU6050----------------
#define MPU_ADDRESS 0x68
#define MPU_DEBUG false

//----------------BNO055----------------
#define BNO_ID 0
#define BNO_ADDRESS 0x28
#define BNO_DEBUG false

//-----------------MOTORS-------------
//Motor 1:
#define M1_ANGLE 60
#define M1_1 8
#define M1_2 9
#define M1_PLUSMINUS_ANGLE 1
#define M1_PLUSMINUS_ANGULAR_SPEED 1
#define M1_PLUSMINUS_COS 1
#define M1_DEBUG false

//Motor 2:
#define M2_ANGLE 180
#define M2_1 4
#define M2_2 5
#define M2_PLUSMINUS_ANGLE -1
#define M2_PLUSMINUS_ANGULAR_SPEED 1
#define M2_PLUSMINUS_COS 1
#define M2_DEBUG false

//Motor 3:
#define M3_ANGLE 60
#define M3_1 10
#define M3_2 11
#define M3_PLUSMINUS_ANGLE -1
#define M3_PLUSMINUS_ANGULAR_SPEED 1
#define M3_PLUSMINUS_COS 1
#define M3_DEBUG false

//---------------IR-------------------
//#define IR_PIN A4
#define IR_PIN A14
#define MIN_STRENGTH 50
#define IR_DEBUG true

//--------------CAMERA---------------
#define CAM_DEBUG false

//-------------CONTROL------------
//Camera:

//Gyro:
#define GYRO_CONT_KP 0.07
#define GYRO_CONT_KD 0.3
#define GYRO_CONT_KC 0.0001
#define GYRO_CONT_DEBUG false

//Angle:
#define ANGLE_CONT_K1 0.45
#define ANGLE_CONT_K2 0.4
#define ANGLE_CONT_DEBUG false

//Distance:
#define DIST_CONT_K1 0.35
#define DIST_CONT_K2 0.7
#define DIST_CONT_DEBUG false

//--------------BUTTON-------------
//Start button:
#define START_BTN_PIN A3
#define START_BTN_DEBUG false

//Set button:
#define SET_BTN_PIN A5
#define SET_BTN_DEBUG false

//--------------LED---------------
#define SIGNAL_LED_PIN 47
