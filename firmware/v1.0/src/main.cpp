#include <Arduino.h>
#include "excitation.h"
#include "detection.h"

Detection::OJIP_Dataset dataset;
Detection::OJIP_Parameters parameters;


void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Excitation::begin();
    Detection::begin();
    Detection::enable();
}

void loop() {
    Detection::test_read();
    //if(Serial.available()){
    //    digitalWrite(LED_BUILTIN, HIGH);
    //    String command = Serial.readStringUntil('\n');
    //    if(command.equals("MF")){
    //        // Measure OJIP fluorescence
    //        Detection::measureOJIP(&dataset);
    //    }
    //    else if(command.equals("CP")){
    //        // Calculate parameters and print to serial out
    //        Detection::extractOJIP(&dataset, &parameters);
    //    }
    //    digitalWrite(LED_BUILTIN, LOW);
    //}
    delay(1);
}