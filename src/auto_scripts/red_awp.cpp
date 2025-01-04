#include "auto_scripts/red_awp.hpp"


void red_awp(){

    //drop preload
        chassis.move({7, -5}, 60, voss::Flags::NONE | voss::Flags::ASYNC);
        set_lb(20, 600);
        intake.move(127);
        pros::delay(400);
        intake.move(0);
        ladybrown.move(90);
        pros::delay(450);
        ladybrown.move(0);

    //clamp goal
        chassis.move({0, 0}, 100, voss::Flags::REVERSE | voss::Flags::THRU);
        pid->modify_linear_constants(15, 0.02, 190);
        chassis.move({-4, 20}, 100, voss::Flags::REVERSE);
        set_lb(0, 600);
        chassis.move({-2, 24}, 80, voss::Flags::REVERSE);
        clamper.set_value(0);
        pros::delay(100);
        pid->modify_linear_constants(20, 0.02, 190);

    //stack - 2 rings
        chassis.turn(-230, 100);
        intake.move(127);
        chassis.move({-23, 34}, 100, voss::Flags::NONE | voss::Flags::THRU);
        chassis.move({-38, 34}, 90, voss::Flags::NONE);
        chassis.move({-43, 33}, 90, voss::Flags::NONE);

    //3rd ring on mogo
        chassis.move({-25, 30}, 80, voss::Flags::REVERSE | voss::Flags::THRU);
        chassis.turn(190, 100);
        chassis.move({-32, 18}, 100, voss::Flags::NONE | voss::Flags::THRU);
        run_intake(127);

    //4th ring on mogo
        chassis.move({0, 10}, 80, voss::Flags::NONE | voss::Flags::THRU);
        chassis.move({15, 12}, 60, voss::Flags::NONE);
        chassis.move({20, 12}, 100, voss::Flags::NONE);
}
