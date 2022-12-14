
#include <pigpiod_if2.h>

#include "diff_motor.h"
#include <stdio.h>

diff_motor::diff_motor(double h, int motLP, int motLM, int motLEn, int motRP, int motRM, int motREn){
    halfBaseWidth = h;
    leftCon.set_pin(motLP, motLM, motLEn);
    rightCon.set_pin(motRP, motRM, motREn);
}

int diff_motor::init(int pigpiod){
    leftCon.init(pigpiod);
    rightCon.init(pigpiod);
    return 0;
}



int diff_motor::set_speed(double linear, double angular){
    if(linear || angular){
        angular += ANGLE_GAIN;
    }
    leftCon.set_speed((linear - halfBaseWidth*angular)*LEFT_GAIN/RIGHT_GAIN);
    rightCon.set_speed((linear + halfBaseWidth*angular)*RIGHT_GAIN/LEFT_GAIN);
    return 0;
}

int diff_motor::set_pwm(int l, int r){
    leftCon.set_pwm(l);
    rightCon.set_pwm(r);
    return 0;
}

int diff_motor::close(){
    leftCon.close();
    rightCon.close();
    return 0;
}