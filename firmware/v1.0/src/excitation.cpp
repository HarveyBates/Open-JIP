#include "excitation.h"

void Excitation::begin(){
    Wire.begin();
    Excitation::setBrightness(LED_OFF);
}

void Excitation::setBrightness(Brightness brightness){
    Wire.beginTransmission(DAC_ADDRESS);
    Wire.write(brightness >> 4);
    Wire.write(brightness & 0x0F);
    Wire.endTransmission();
}
