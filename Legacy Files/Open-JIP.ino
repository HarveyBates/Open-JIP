#include <digitalWriteFast.h>

#define readPin 2                                   
int actinicPin = 7;                                 
int batteryPin = 8;                                 
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

int baseRead[5];
int microRead[200];
int milliRead[900];

int baseCycles = 5;
int microCycles = 200;
int milliCycles = 900;

int h[5];             
unsigned long t[200]; 
unsigned long p[900]; 
String command;

void setup()
{
    Serial.begin(74880);         
    pinMode(actinicPin, OUTPUT); 
    analogReference(DEFAULT); 
    pinMode(batteryPin, OUTPUT);
    digitalWrite(batteryPin, HIGH);
    sbi(ADCSRA, ADPS2);
    cbi(ADCSRA, ADPS1);
    cbi(ADCSRA, ADPS0);
}

void measureFluoro()
{
    long timer = micros();               
    micros();                        
    for (int y = 0; y < baseCycles; y++) 
    {
        baseRead[y] = analogRead(readPin);
        h[y] = micros() - timer;
    }

    digitalWriteFast(actinicPin, HIGH); 

    for (int i = 0; i < microCycles; i++) 
    {
        microRead[i] = analogRead(readPin);
        t[i] = micros() - timer;
    }

    for (int o = 0; o < milliCycles; o++) 
    {
        milliRead[o] = analogRead(readPin);
        p[o] = micros() - timer;
        delay(1);
    }

    digitalWriteFast(actinicPin, LOW);

    int microMax = microRead[1]; 
    for (int u = 1; u < microCycles; u++)
    {
        if (microRead[u] > microMax)
        {
            microMax = microRead[u];
        }
    }

    int milliMax = milliRead[0]; 
    for (int i = 0; i < milliCycles; i++)
    {
        if (milliRead[i] > milliMax)
        {
            milliMax = milliRead[i];
        }
    }

    for (int k = 0; k < baseCycles; k++) 
    {
        float baseTime = h[k];                     
        float basetimeConverted = baseTime / 1000; 
        Serial.print(basetimeConverted, 3);
        Serial.print("\t");
        Serial.println(baseRead[k]);
        delay(1);
    }

    for (int q = 0; q < microCycles; q++) 
    {
        float millCounts = t[q];             
        float realCounts = millCounts / 1000; 
        Serial.print(realCounts, 3);
        Serial.print("\t");
        Serial.println(microRead[q]);
        delay(1);
    }

    for (int l = 0; l < milliCycles; l++)
    {
        float milliTime = p[l];
        float millitimeConverted = milliTime / 1000;
        Serial.print(millitimeConverted, 3);
        Serial.print("\t");
        Serial.println(milliRead[l]);
        delay(1);
    }

    Serial.println();
    Serial.print("Fo = ");
    Serial.println(microRead[1]); 

    if (milliMax >= microMax)
    { 
        Serial.print("Fm = ");
        Serial.println(milliMax);        
        float Fo = microRead[1];         
        float Fm = milliMax;             
        float FvoverFm = (Fm - Fo) / Fm; 
        Serial.print("Fv/Fm = ");
        Serial.println(FvoverFm); 
        Serial.println();
    }
    else
    { 
        Serial.print("Fm = ");
        Serial.println(microMax);        
        float Fo = microRead[1];         
        float Fm = microMax;             
        float FvoverFm = (Fm - Fo) / Fm; 
        Serial.print("Fv/Fm = ");
        Serial.println(FvoverFm); 
        Serial.println();
    }
}

void measureLight()
{
    digitalWrite(actinicPin, HIGH);
    delay(4000);
    digitalWrite(actinicPin, LOW);
    delay(20);
    return;
}

void loop()
{
    if (Serial.available())
    { 
        command = Serial.readStringUntil('\n');
        if (command.equals("Measure Fluorescence"))
        {
            measureFluoro();
        }
        else if (command.equals("MF"))
        {
            measureFluoro();
        }
        else if (command.equals("Measure Light"))
        {
            measureFluoro();
        }
        else if (command.equals("ML"))
        {
            measureLight();
        }
        else
        {
            Serial.println("Invalid Command");
        }
    }
}
