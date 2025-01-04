#include "main.h"
#include "VOSS/utils/flags.hpp"
#include "auto_scripts/blue_awp.hpp"
#include "auto_scripts/red_awp.hpp"
#include "auto_scripts/blue_elims_neg.hpp"
#include "auto_scripts/blue_elims_pos.hpp"
#include "auto_scripts/red_elims_neg.hpp"
#include "auto_scripts/red_elims_pos.hpp"
#include "liblvgl/core/lv_disp.h"
#include "liblvgl/llemu.hpp"
#include "liblvgl/misc/lv_area.h"
#include "ports.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robodash/views/console.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/neutralArm.hpp"
#include "robodash/api.h"
// ============================= INCLUDES  ============================= //
//

LV_IMG_DECLARE(teamLogo)
rd::Selector selector({
    {"red awp", red_awp},
    {"red negative", red_elims_neg},
    {"red positive", red_elims_pos},
    {"blue awp", blue_awp},
    {"blue positive", blue_elims_pos},
});
rd::Console console;

// ============================= Initialize ============================= //
void initialize() {
    //init screen
    selector.focus();

    //init odom
    odom->begin_localization();

    //subsystem
    ladybrown.tare_position();
    clamper.set_value(1);

    //match color
    set_match_color(true);
    colorSort.set_led_pwm(100);

    //print system vals
    pros::Task subTasks([=]{
        while(1){
            intake_with_task();
            console.printf("x: %.2f\n", odom->get_pose().x);
            console.printf("y: %.2f\n", odom->get_pose().y);
            console.printf("z: %.2f\n", odom->get_pose().theta);
            console.printf("disk hue: %.2f\n", colorSort.get_hue());
            pros::delay(50);
            console.clear();
        }
    });
}


void disabled() {
}


void competition_initialize() {
}

// ============================= Autonomous ============================= //
//selector.run_auton();
void autonomous() {
    console.focus();
    //hover preload
    set_lb(40, 200);

    //first ring - hold on
    chassis.move({30, 2}, 100, voss::Flags::NONE | voss::Flags::THRU);
    run_intake(127);
    chassis.move({44, 5}, 100, voss::Flags::NONE);
    pros::delay(300);
    intake.move(20);

    //come back - clamp
    chassis.move({25, -13}, 70, voss::Flags::REVERSE);
    chassis.move({24, -14}, 70, voss::Flags::REVERSE);
    clamper.set_value(0);
    pros::delay(100);

    //second ring
    set_lb(55, 200);
    chassis.turn(90, 100);
    run_intake(127);
    ec->add_thru_smoothness(1);
    chassis.move({24, 3}, 80, voss::Flags::NONE | voss::Flags::THRU);

    //neutral stake
    chassis.move({42, 28}, 80, voss::Flags::NONE);
    chassis.turn(37, 100);
    set_lb(170, 600);




}

// ============================= Driver Control ============================= //
void opcontrol() {
    lv_obj_t *teamimg = lv_img_create(lv_scr_act());
    lv_img_set_src(teamimg, &teamLogo);
    lv_obj_align(teamimg, LV_ALIGN_CENTER, 0,0);

    driver();

}
