#pragma once

#include "api.h"
#include "ports.hpp"
#include "pros/motors.h"

inline pros::Motor ladybrown(LADYBROWN_PORT, LADYBROWN_GEARSET,LADYBROWN_ENCODER);

inline void set_lb(double target, double speed){
    ladybrown.move_absolute(target, speed);
}
