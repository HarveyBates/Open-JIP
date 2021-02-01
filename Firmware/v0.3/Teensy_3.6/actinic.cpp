#include "actinic.h"

Actinic::Actinic(){
  Serial.println("[OUTPUT] Actnic LED");
  pinMode(actinicGain1, OUTPUT);
  pinMode(actinicGain2, OUTPUT);
  pinMode(actinicGain3, OUTPUT);
  pinMode(actinicGain4, OUTPUT);
  off();
}

void Actinic::off(){
  Serial.println("[OFF] Actnic LED");
  digitalWrite(actinicGain1, LOW);
  digitalWrite(actinicGain2, LOW);
  digitalWrite(actinicGain3, LOW);
  digitalWrite(actinicGain4, LOW);
}

void Actinic::define(int mag){
  intensity = mag;
}

void Actinic::on(){
  switch(intensity){
    case 1:
      Serial.println("[ON] Actinic LED (Intensity: 1)");
      digitalWrite(actinicGain1, HIGH);
      break;
    case 2:
      Serial.println("[ON] Actinic LED (Intensity: 2)");
      digitalWrite(actinicGain2, HIGH);
      break;
    case 3:
      Serial.println("[ON] Actinic LED (Intensity: 3)");
      digitalWrite(actinicGain3, HIGH);
      break;
    case 4:
      Serial.println("[ON] Actinic LED (Intensity: 4)");
      digitalWrite(actinicGain4, HIGH);
      break;
  }
}
