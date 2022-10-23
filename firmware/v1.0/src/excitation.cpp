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

void Excitation::testRise(Brightness brightness, const uint8_t n_rises,
                          const uint16_t pulse_width){

    //Detection::enable();
    //delay(10);

    for(uint8_t i = 0; i < n_rises; i++){
        setBrightness(brightness);
        delay(pulse_width);
        setBrightness(LED_OFF);
        delay(pulse_width);
    }

    //Detection::disable();
}
