#include "detection.h"

void Detection::begin() {
    pinMode(DETECTION_EN, OUTPUT);
}

void Detection::enable(){
    digitalWrite(DETECTION_EN, HIGH);
}

void Detection::disable(){
    digitalWrite(DETECTION_EN, LOW);
}

int Detection::test_read(){
    return analogRead(DETECTION_ANALOG_PIN);
}

void Detection::measureOJIP(OJIP_Dataset* dataset){

    Detection::enable();
    delay(100); // Ensure op-amps are ready

    Excitation::setBrightness(Excitation::LED_VERY_HIGH);
    unsigned long timer = micros();

    for(uint16_t i = 0; i < MICRO_LEN; i++){
        dataset->timestamps[i] = micros() - timer;
        dataset->raw_values[i] = analogRead(DETECTION_ANALOG_PIN);
    }

    for(uint16_t i = MICRO_LEN; i < (MICRO_LEN + MILLI_LEN); i++){
        dataset->timestamps[i] = micros() - timer;
        dataset->raw_values[i] = analogRead(DETECTION_ANALOG_PIN);
        delay(1);
    }

    Excitation::setBrightness(Excitation::LED_OFF);
    Detection::disable();
}

void Detection::extractOJIP(OJIP_Dataset* dataset,
                            OJIP_Parameters* parameters){

    parameters->Fm = 0.0f;

    bool found_fj = false, found_fi = false;
    float time_fj = 0.0f, time_fi = 0.0f, time_fm = 0.0f;
    for(uint16_t i = 0; i < MEASURE_LEN; i++){
        // Extract Fm
        if(dataset->raw_values[i] > parameters->Fm){
            parameters->Fm = dataset->raw_values[i];
            time_fm = (float)dataset->timestamps[i] / 1000.0f;
        }

        float milli_time = (float)dataset->timestamps[i] / 1000.0f;
        double value = (dataset->raw_values[i] * 3.3) / 10.0f;

        // Extract Fj at 2 milliseconds
        if(!found_fj && (int)milli_time == 2){
            parameters->Fj = dataset->raw_values[i];
            time_fj = (float)dataset->timestamps[i] / 1000.0f;
            found_fj = true;
        }

        // Extract Fi at 30 milliseconds
        if(!found_fi && (int)milli_time == 30){
            parameters->Fi = dataset->raw_values[i];
            time_fi = (float)dataset->timestamps[i] / 1000.0f;
            found_fi = true;
        }

        Serial.print(milli_time);
        Serial.print("\t");
        Serial.println(value, 4);
    }

    if(parameters->Fm == 1023){
        Serial.println("ERR: Fluorescence saturated.");
        return;
    }

    parameters->Fo = dataset->raw_values[0];
    parameters->Fv = parameters->Fm - parameters->Fo;
    parameters->FvFm = (float)parameters->Fv /
            (float)parameters->Fm;

    Serial.println();
    Serial.print("Fo: \t");
    Serial.print((parameters->Fo * 3.3) / 10.0f, 4);
    Serial.print(" V @ ");
    Serial.print((float)dataset->timestamps[0] / 1000.0f, 4);
    Serial.println(" ms");
    Serial.print("Fj: \t");
    Serial.print((parameters->Fj * 3.3) / 10.0f, 4);
    Serial.print(" V @ ");
    Serial.print(time_fj);
    Serial.print(" ms\nFi: \t");
    Serial.print((parameters->Fi * 3.3) / 10.0f, 4);
    Serial.print(" V @ ");
    Serial.print(time_fi);
    Serial.print(" ms\nFm: \t");
    Serial.print((parameters->Fm * 3.3) / 10.0f, 4);
    Serial.print(" V @ ");
    Serial.print(time_fm);
    Serial.print(" ms\nFv: \t");
    Serial.print((parameters->Fv * 3.3) / 10.0f, 4);
    Serial.println(" V");
    Serial.print("Quantum yield (Fv/Fm): \t");
    Serial.print(parameters->FvFm, 3);
}