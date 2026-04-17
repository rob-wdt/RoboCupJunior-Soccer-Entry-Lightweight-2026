#pragma once

#include "include.h"
#include "config.h"

#include "..\hal\sensors\gyros\mpu6050\mpu6050.h"
#include "..\hal\sensors\gyros\bno055\bno055.h"

#include "..\hal\motor\motor.h"

#include "..\hal\sensors\ir\IR.h"

#include "..\perception\camera\camera.h"

#include "..\control\regulator.h"
#include "..\control\exponential\exp.h"
#include "..\control\pdc\PDC.h"

#include "..\hal\button\button.h"

#include "..\hal\led\LED.h"

namespace objects
{
    Mpu6050 mpu{MPU_ADDRESS, MPU_DEBUG};
    Bno055 bno{BNO_ID, BNO_ADDRESS, BNO_DEBUG};

    Motor motor_1{
        M1_ANGLE,
        M1_1,
        M1_2,
        M1_DIRECTION,
        M1_PLUSMINUS_ANGLE,
        M1_PLUSMINUS_ANGULAR_SPEED,
        M1_PLUSMINUS_COS,
        MIN_SPEED,
        M1_DEBUG};

    Motor motor_2{
        M2_ANGLE,
        M2_1, M2_2,
        M2_DIRECTION,
        M2_PLUSMINUS_ANGLE,
        M2_PLUSMINUS_ANGULAR_SPEED,
        M2_PLUSMINUS_COS,
        MIN_SPEED,
        M2_DEBUG};

    Motor motor_3{
        M3_ANGLE,
        M3_1,
        M3_2,
        M3_DIRECTION,
        M3_PLUSMINUS_ANGLE,
        M3_PLUSMINUS_ANGULAR_SPEED,
        M3_PLUSMINUS_COS,
        MIN_SPEED,
        M3_DEBUG};

    IR ir_seeker{IR_PIN, MIN_STRENGTH, MAX_STRENGTH, MED_STRENGTH, IR_DEBUG};

    Camera camera{CAM_DEBUG};

    namespace controls
    {
        Regulator cam_cont{};
        PDC gyro_cont{GYRO_CONT_KP, GYRO_CONT_KD, GYRO_CONT_KC, GYRO_CONT_DEBUG};
        Exp angle_cont{ANGLE_CONT_K1, ANGLE_CONT_K2, ANGLE_CONT_DEBUG};
        Exp dist_cont{DIST_CONT_K1, DIST_CONT_K2, DIST_CONT_DEBUG};
    };

    Button start_btn{START_BTN_PIN, START_BTN_DEBUG};
    Button set_btn{SET_BTN_PIN, SET_BTN_DEBUG};

    LED signal{SIGNAL_LED_PIN};
};