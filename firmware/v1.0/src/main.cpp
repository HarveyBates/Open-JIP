#include <Arduino.h>
#include "excitation.h"
#include "detection.h"

Detection::OJIP_Dataset dataset;
Detection::OJIP_Parameters parameters;

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    analogReference(AR_INTERNAL1V2);
    analogReadResolution(10);

    Excitation::begin();
    Detection::begin();
    Detection::enable();
}

void loop() {
    //Serial.println(Detection::test_read());
    if(Serial.available()){
        digitalWrite(LED_BUILTIN, HIGH);
        String command = Serial.readStringUntil('\n');
        if(command.equals("AT+MF")){
            // Measure OJIP fluorescence
            Detection::measureOJIP(&dataset);
        }
        else if(command.equals("AT+CP")){
            // Calculate parameters and print to serial out
            Detection::extractOJIP(&dataset, &parameters);
        }
        else if(command.equals("AT+RAW")){
            // Print out raw data
            Detection::rawOJIP(&dataset);
        }
        else if(command.equals("AT+TEST")){
            Excitation::testRise(Excitation::LED_HIGH, 20, 20);
        }
        digitalWrite(LED_BUILTIN, LOW);
    }
}