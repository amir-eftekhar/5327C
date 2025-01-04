#pragma once

#include "VOSS/api.hpp"
#include "VOSS/controller/BoomerangControllerBuilder.hpp"
#include "VOSS/controller/PIDControllerBuilder.hpp"
#include "VOSS/controller/SwingControllerBuilder.hpp"
#include "VOSS/localizer/ADILocalizerBuilder.hpp"
#include "VOSS/utils/flags.hpp"
#include "pros/llemu.hpp"
#include "ports.hpp"
#include <vector>

inline auto odom = voss::localizer::TrackingWheelLocalizerBuilder::new_builder()
                .with_middle_rotation(HORZ_TRACKER_PORT)
                .with_right_rotation(FORW_TRACKER_PORT)
                .with_track_width(TRACK_WIDTH)
                .with_left_right_tpi(TRACKER_TPI)
                .with_middle_tpi(TRACKER_TPI)
                .with_imu(IMU_PORT)
                .build();

inline auto pid = voss::controller::PIDControllerBuilder::new_builder(odom)
               .with_linear_constants(20, 0.02, 190)
               .with_angular_constants(300, 0.05, 2435)
               .with_min_error(4)
               .with_min_vel_for_thru(70)
               .build();
inline auto full_mogo_pid = voss::controller::PIDControllerBuilder::new_builder(odom)
               .with_linear_constants(30, 0.02, 190)
               .with_angular_constants(330, 0.05, 2435)
               .with_min_error(4)
               .with_min_vel_for_thru(70)
               .build();
inline auto boomerang = voss::controller::BoomerangControllerBuilder::new_builder(odom)
                     .with_linear_constants(20, 0.02, 190)
                     .with_angular_constants(300, 0.05, 2435)
                     .with_lead_pct(0.5)
                     .with_min_vel_for_thru(70)
                     .with_min_error(4)
                     .build();

inline auto swing = voss::controller::SwingControllerBuilder::new_builder(odom)
                 .with_angular_constants(250, 0.05, 2435)
                 .build();

inline auto arc = voss::controller::ArcPIDControllerBuilder(odom)
               .with_track_width(16)
               .with_linear_constants(20, 0.02, 169)
               .with_angular_constants(250, 0.05, 2435)
               .with_min_error(5)
               .with_slew(8)
               .build();

inline pros::Controller master(pros::E_CONTROLLER_MASTER);
inline auto ec = voss::controller::ExitConditions::new_conditions()
              .add_settle(150, 3, 250)
              .add_tolerance(4, 1, 300)
              .add_timeout(22500)
              .add_thru_smoothness(4)
              .build() -> exit_if([]() {
                  return master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
              });

inline auto chassis = voss::chassis::DiffChassis(LEFT_MOTORS, RIGHT_MOTORS, pid, ec, 8,
                                          pros::E_MOTOR_BRAKE_COAST);
