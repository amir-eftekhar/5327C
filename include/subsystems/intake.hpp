#pragma once

#include "ports.hpp"
#include "api.h"
#include "pros/adi.h"

#define COLOR_SORT_ACTIVE true
#define RED_HUE 8
#define BLUE_HUE 220

inline pros::Motor intake(INTAKE_PORT);
inline pros::Optical colorSort(COLOR_SORT);

inline int intakeState = 0;
inline bool color;
inline bool redDetected = false;
inline bool blueDetected = false;

inline void run_intake(float speed){
    intake.move(speed);
    intakeState = speed;
}

inline int get_intake_state(){
    return intakeState;
}

inline void intake_with_task(){
    double get_hue = colorSort.get_hue();
    if((get_hue <= RED_HUE + 10) && (get_hue >= RED_HUE - 10))redDetected = true; else{redDetected = false;}
    if((get_hue <= BLUE_HUE + 10) && (get_hue >= BLUE_HUE - 10))blueDetected = true; else{blueDetected = false;}
    if(COLOR_SORT_ACTIVE){
        if(redDetected){
            if(!color){
                pros::delay(40);
                intake.move(-127);
                pros::delay(150);
                intake.move(intakeState);
            }
        }
        if(blueDetected){
            if(color){
                pros::delay(40);
                intake.move(-127);
                pros::delay(150);
                intake.move(intakeState);
            }
        }
    }
}

inline void set_match_color(bool isred){
    color = isred;
}

inline pros::ADIDigitalOut clamper(CLAMPER_PORT);
