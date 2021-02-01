#include "sensitivity.h"

Sensitivity::Sensitivity(){
  pinMode(fluoroGain1, OUTPUT);
  pinMode(fluoroGain2, OUTPUT);
  pinMode(fluoroGain3, OUTPUT);
  pinMode(fluoroGain4, OUTPUT);
}

void Sensitivity::refresh(){
  digitalWrite(fluoroGain1, LOW);
  digitalWrite(fluoroGain2, LOW);
  digitalWrite(fluoroGain3, LOW);
  digitalWrite(fluoroGain4, LOW);
}

void Sensitivity::define(int _gain){
  switch(_gain){
    case 1:
      digitalWrite(fluoroGain1, HIGH);
      break;
    case 2:
      digitalWrite(fluoroGain2, HIGH);
      break;
    case 3:
      digitalWrite(fluoroGain3, HIGH);
      break;
    case 4:
      digitalWrite(fluoroGain4, HIGH);
      break;
  }
}
