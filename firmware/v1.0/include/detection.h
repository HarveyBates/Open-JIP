#ifndef DETECTION_H
#define DETECTION_H

#include <Arduino.h>
#include "excitation.h"

#define DETECTION_EN D10
#define DETECTION_ANALOG_PIN A3

class Detection {
public:
    Detection() = default;
    ~Detection() = default;
    static void begin();
    static void enable();
    static void disable();
    static int test_read();

    static constexpr uint16_t MICRO_LEN     =   1000;
    static constexpr uint16_t MILLI_LEN     =   1000;
    static constexpr uint16_t MEASURE_LEN   =   MICRO_LEN + MILLI_LEN;

    struct OJIP_Dataset {
        unsigned long timestamps[MEASURE_LEN];
        int raw_values[MEASURE_LEN];
    };

    struct OJIP_Parameters {
        int Fo;
        int Fj;
        int Fi;
        int Fm;
        int Fv;
        float FvFm;
    };

    static void measureOJIP(OJIP_Dataset* dataset);
    static void extractOJIP(OJIP_Dataset* dataset,
                            OJIP_Parameters* parameters);

};

#endif //DETECTION_H
