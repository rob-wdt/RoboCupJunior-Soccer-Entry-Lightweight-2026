#pragma once

//---------------MATH-----------------
#define E 2.71828

//----------------ROBOT---------------
#define DEBUG 1

#if DEBUG == true
#define DEBUG_MODE 4
/*
0 - Debug gyro (align on zero_angle)
1 - Debug IR (print out the angle and strength)
2 - Check motors
3 - Drive on an angle (0, 60, 90 ...)
4 - Debug camera control
5 - Debug exp coef
*/

#if DEBUG_MODE == 3
#define ANGLE 0
#endif
#endif

//------------------SPEED-------------
#define MIN_SPEED 55 // 0 - 255

#if DEBUG == true && (DEBUG_MODE == 0 || DEBUG_MODE == 4)
#define SPEED 0 // 0 - 255
#else
#define SPEED 80
#endif

//-----------------MPU6050----------------
#define MPU_ADDRESS 0x68

#if DEBUG == true && DEBUG_MODE == 0
#define MPU_DEBUG true
#else
#define MPU_DEBUG false
#endif

//----------------BNO055----------------
#define BNO_ID 0
#define BNO_ADDRESS 0x28

#if DEBUG == true && DEBUG_MODE == 0
#define BNO_DEBUG true
#else
#define BNO_DEBUG false
#endif

//-----------------MOTORS-------------
// Motor 1:
#define M1_ANGLE 60
#define M1_1 8
#define M1_2 9
#define M1_PLUSMINUS_ANGLE 1
#define M1_PLUSMINUS_ANGULAR_SPEED 1
#define M1_PLUSMINUS_COS 1

#if DEBUG == true && (DEBUG_MODE == 2 || DEBUG_MODE == 3)
#define M1_DEBUG true
#else
#define M1_DEBUG false
#endif

// Motor 2:
#define M2_ANGLE 180
#define M2_1 4
#define M2_2 5
#define M2_PLUSMINUS_ANGLE -1
#define M2_PLUSMINUS_ANGULAR_SPEED 1
#define M2_PLUSMINUS_COS 1

#if DEBUG == true && (DEBUG_MODE == 2 || DEBUG_MODE == 3)
#define M2_DEBUG true
#else
#define M2_DEBUG false
#endif

// Motor 3:
#define M3_ANGLE 60
#define M3_1 10
#define M3_2 11
#define M3_PLUSMINUS_ANGLE -1
#define M3_PLUSMINUS_ANGULAR_SPEED 1
#define M3_PLUSMINUS_COS -1

#if DEBUG == true && (DEBUG_MODE == 2 || DEBUG_MODE == 3)
#define M3_DEBUG true
#else
#define M3_DEBUG false
#endif

//---------------IR-------------------
#define IR_PIN A14
#define MIN_STRENGTH 30
#define MAX_STRENGTH 255
#define MED_STRENGTH 90 // Расстояние на котором надо объезжать под большим углом

#if DEBUG == true && DEBUG_MODE == 1
#define IR_DEBUG true
#else
#define IR_DEBUG false
#endif

//--------------CAMERA---------------
#if DEBUG == true && DEBUG_MODE == 4
#define CAM_DEBUG true
#else
#define CAM_DEBUG false
#endif

//-------------CONTROL------------
// Camera:
#define CAM_CONT_KP 0
#define CAM_CONT_KD 0
#define CAM_CONT_KC 0

#if DEbug == true && DEBUG_MODE == 4
#define CAM_CONT_DEBUG true
#else
#define CAM_CONT_DEBUG false
#endif

// Gyro:
#define GYRO_CONT_KP 0.25
#define GYRO_CONT_KD 0.1            // 0.05
#define GYRO_CONT_KC (double)0.0005 // 0.0001

#if DEBUG == true && DEBUG_MODE == 0
#define GYRO_CONT_DEBUG true
#else
#define GYRO_CONT_DEBUG false
#endif

// Angle:
#define ANGLE_CONT_K1 0.45
#define ANGLE_CONT_K2 0.03

#if DEBUG == true && DEBUG_MODE == 5
#define ANGLE_CONT_DEBUG true
#else
#define ANGLE_CONT_DEBUG false
#endif

// Distance:
#define DIST_CONT_K1 0.35
#define DIST_CONT_K2 0.7

#if DEBUG == true && DEBUG_MODE == 5
#define DIST_CONT_DEBUG true
#else
#define DIST_CONT_DEBUG false
#endif

//--------------BUTTON-------------
// Start button:
#define START_BTN_PIN A3
#define START_BTN_DEBUG false

// Set button:
#define SET_BTN_PIN A5
#define SET_BTN_DEBUG false

//--------------LED---------------
#define SIGNAL_LED_PIN 47
