#include "main.h"

void setIntake() {
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            intake.move_velocity(600);
        }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            intake.move_velocity(-500);
        }
    else {
            intake = 0;
        }
}
