#ifndef ACTINIC_H
#define ACTINIC_H

#include <Wire.h>

class Excitation {
public:
    Excitation() = default;
    ~Excitation() = default;

    enum Brightness {
        LED_OFF = 0,
        LED_VERY_LOW = 80,
        LED_LOW = 100,
        LED_MEDIUM = 120,
        LED_HIGH = 140,
        LED_VERY_HIGH = 200,
    };

    static void setBrightness(Brightness brightness);
    static void begin();


private:
    static const byte DAC_ADDRESS = 0x4C;
};

#endif //ACTINIC_H
