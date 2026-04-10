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
    Mpu6050 mpu;
    Bno055 bno;

    Motor motor_1{60, M1_1, M1_2, 1, 1, 1, MIN_SPEED};
    Motor motor_2{180, M2_1, M2_2, -1, 1, 1, MIN_SPEED};
    Motor motor_3{60, M4_1, M4_2, -1, -1, 1, MIN_SPEED};

    IR ir_seeker{A4, MIN_STRENGTH};

    Camera camera{};

    namespace controls
    {
        Regulator cam_cont{};
        PDC gyro_cont{0.05, 0.5, 0.00005};
        Exp angle_cont{0.45, 0.4};
        Exp dist_cont{0.35, 0.7};
    };

    Button start_btn{A3};
    Button set_btn{A5};

    LED signal{47};
};