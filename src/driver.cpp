#include "driver.hpp"
#include "ports.hpp"
#include "pros/misc.h"
#include "subsystems/neutralArm.hpp"

void driver(){
    bool l1Pressed;
    bool l2Pressed;
    bool r1Pressed;
    bool r2Pressed;
    bool bPressed;
    while (true) {
        chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
                     master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        //intake
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
            r1Pressed = !r1Pressed;
            if(r1Pressed){run_intake(-127);} else{ run_intake(0);}
        }
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
            r2Pressed = !r2Pressed;
            if(r2Pressed){run_intake(127);} else{ run_intake(0);}
        }
        //clamp
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
            bPressed = !bPressed;
            if(bPressed){clamper.set_value(1);} else{clamper.set_value(0);}
        }
        //lady brown
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
            l1Pressed = !l1Pressed;
            if(l1Pressed){set_lb(LB_LOAD_HEIGHT, 600);} else{ set_lb(0, 600);;}
        }
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
            l2Pressed = !l2Pressed;
            if(l2Pressed){set_lb(LB_SCORE, 600);} else{ set_lb(LB_LOAD_HEIGHT,600);}
        }

        pros::delay(10);
    }
}
