#include "main.h"

bool holdingIndex;

void setIntake() {
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            intake = 127;
            holdingIndex = false;
        }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            intake.move_velocity(-500);
            holdingIndex = true;
        }
    else {
            intake = 0;
            holdingIndex = false;
        }
}
