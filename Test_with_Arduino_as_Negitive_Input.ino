#include <digitalWriteFast.h> //used for fast turning ON and OFF of digitalpins

#define readPin 0 //which analogpin pin will be used
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) //used for <20us data acquisition
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit)) //used for <20us data acquisition

int baseRead[5]; //baseline pin readings
int microRead [200]; //microsecond pin readings
int milliRead[900]; //millisecond pin readings

int baseCycles = 5; //amount of baseline data points
int microCycles = 200; //amount of microsecond data points
int milliCycles = 900; //amount of millisecond data points

int h[5]; //array size for baseline data points
unsigned long t[200]; //array size for microsecond data points 
unsigned long p[900]; //array size for millisecond data points

void setup() {
  Serial.begin(74880); //intalises arduino with a baud rate of 74880
  pinMode(5, OUTPUT); //defines the output for switching on and off LED (slow arduino response without this)
  analogReference(INTERNAL2V56); //defines which reference voltage to use for analogRead (lower the value, Higher the sensitivity)
  sbi(ADCSRA, ADPS2); //used for 20us data acquisition
  cbi(ADCSRA, ADPS1); // used for 20us data acquisition
  cbi(ADCSRA, ADPS0); // used for 20us data acquisition
}

void loop() {
  delay(10000); //preliminary delay to ensure arduino is ready
  long timer = micros(); //creates an offset for the timer (takes it to zero);
  micros(); //starts timer
  
  for (int y = 0; y < baseCycles; y++) //first array loop for baseline (stores analogRead values in an array)
  {
    baseRead[y] = analogRead(readPin);
    h[y] = micros() - timer;
  }
  
  digitalWriteFast(5, HIGH); //switches ON the light (125ns response time)
  
  for (int i = 0; i < microCycles; i++) //second array loop for microsecond values
  {
    microRead[i] = analogRead (readPin);
    t[i] = micros() - timer;
  }
  
  for (int o = 0; o < milliCycles; o++) //third array loop for microsecond values
  {
    milliRead[o] = analogRead(readPin);
    p[o] = micros() - timer;
    delay(1);
  }
  
  digitalWriteFast(5, LOW); //switches OFF the light
  
  int microMax = microRead[1]; //finds the maximum of the microsecond array values
    for (int u = 1; u < microCycles; u++){
      if(microRead[u] > microMax){
        microMax = microRead[u];
      }
    }
    
  int milliMax = milliRead[0]; //finds the maximum of the millisecond array values
    for (int i = 0; i < milliCycles; i++){
      if(milliRead[i] > milliMax){
        milliMax = milliRead[i];
      }
    }
    
  for (int k = 0; k < baseCycles; k++) //prints the values of the ojip curve for baseline array values
  { 
    float baseTime = h[k]; //converts timeseries into a float
    float basetimeConverted = baseTime/1000; //converts microseconds into milliseconds
    Serial.print(basetimeConverted, 3);
    Serial.print("\t");
    Serial.println(baseRead[k]);
  }
  
  for (int q = 0; q < microCycles; q++) //prints the values of the ojip curve for microsecond array values
  {
   float millCounts = t[q]; //converts timeseries into a float (this allows math to be used)
   float realCounts = millCounts/1000; //converts microseconds inot milliseconds
   Serial.print(realCounts, 3); 
   Serial.print("\t");
   Serial.println(microRead[q]);
  }
  
  for (int l = 0; l < milliCycles; l++) //prints the values of the ojip curve for millisecond array values
  {
   float milliTime = p[l];
   float millitimeConverted = milliTime/1000;
   Serial.print(millitimeConverted, 3); 
   Serial.print("\t");
   Serial.println(milliRead[l]);
  }
  
  Serial.println();
  Serial.print("Fo = ");
  Serial.println(microRead[1]); //prints the value of F corresponding to a timeseries of 40us (this is used for Fo)
  
  if (milliMax >= microMax){ //checks to see if Fm is in the microseconds or milliseconds
    Serial.print("Fm = ");
    Serial.println(milliMax); //if maximum value is in the microseconds time scale
    float Fo = microRead[1]; //defines Fo as a float for use in math
    float Fm = milliMax; //converts max value to float for use in math
    float FvoverFm = (Fm-Fo)/Fm; //calculates Fv/Fm
    Serial.print("Fv/Fm = ");
    Serial.println(FvoverFm); //prints Fv/Fm value
    Serial.println();
  } 
  else { //either this part of the part above will be done to calculate max F and Fv/Fm (as max F can occur in the microsecond or millisecond range)
    Serial.print("Fm = ");
    Serial.println(microMax); //if Fm is in the microseconds then this value is used for Fm
    float Fo = microRead[1]; //defines Fo as a float for use in math
    float Fm = microMax; //converts max value to float for use in math
    float FvoverFm = (Fm-Fo)/Fm; //calculates Fv/Fm
    Serial.print("Fv/Fm = ");
    Serial.println(FvoverFm); //prints Fv/Fm value
    Serial.println();
  }
}
