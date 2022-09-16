#include "main.h"

bool flywheelBoolean = false;

void setFlywheelToggle(){
if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            flywheelBoolean = !flywheelBoolean;
            pros::delay(300);
        }
}

void setFlywheel(){
    if (flywheelBoolean){
        if (highAngle){
            flywheel.move_velocity(375);
        }
        else {
            flywheel.move_velocity(535);
        }
    }
    else {
        flywheel = 0;
    }
}