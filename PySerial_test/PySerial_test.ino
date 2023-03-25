#include "Stepper.h"

/*----- Variables, Pins -----*/
#define STEPS  32   // Number of steps per revolution of Internal shaft
int ROTATION=2040;  // 2048 = 1 Revolution
int LED = 13;
int data;
int fingerAngle=0;
int deltaSteps = 128;

Stepper fingers(STEPS, 8, 10, 9, 11);
Stepper fingers2(STEPS, 4, 6, 5, 7);


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  fingers.setSpeed(800);
  fingers2.setSpeed(800);
}

void loop() {
  while (Serial.available()){
    data = Serial.read();
    Serial.println(fingerAngle);
    if(data == '1'){
      digitalWrite(LED, HIGH);
      Serial.println("LED ON");
      if(fingerAngle < ROTATION/3){
        fingers.step(deltaSteps);
        fingers2.step(-deltaSteps);
        delay(100);
        fingerAngle += deltaSteps;
      }
      
    }
    else if(data == '0'){
     digitalWrite(LED, LOW);
      Serial.println("LED OFF");
      if(fingerAngle > 0){
        fingers.step(-deltaSteps);
        fingers2.step(deltaSteps);
        delay(200);
        fingerAngle -= deltaSteps;
        
      }
    }
  }
}
