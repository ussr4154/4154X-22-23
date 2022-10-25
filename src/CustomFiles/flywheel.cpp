#include "main.h"

bool flywheelBoolean = false;
int error = 0;
int integral = 0;
int kI = 0.3;

void setFlywheelToggle(){
if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            flywheelBoolean = !flywheelBoolean;
            pros::delay(300);
        }
}

void setFlywheelPower(int target){

    while(flywheel.get_actual_velocity() < target){

        error = target - flywheel.get_actual_velocity();
        integral = integral + error;
        flywheel = integral*kI;
        
    }
}

void setFlywheel(){
    if (flywheelBoolean){
        if(holdingIndex){
            flywheel = -127;
        }
        else {
            flywheel.move_velocity(-340);
        }
    }

    else {
        flywheel = 0;
    }
}