#include "main.h"

void toggleShotAngle(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            highAngle = !highAngle;
            pros::delay(200);
        }
}

void setShotAngle(){
    if (highAngle){
        leftFlywheel.set_value(true);
        rightFlywheel.set_value(true);
    }
    else {
        leftFlywheel.set_value(false);
        rightFlywheel.set_value(false);
    }
}