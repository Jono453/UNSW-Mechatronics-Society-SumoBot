//Arduino micro. Use Leonardo board
#include <Servo.h> //library. contains commands for control the servo

unsigned long previousMillis = 0;
const long interval = 1000; 
int rearLine = 10; //digital
int frontLine = 11; //digital


void setup() {
  //pins for IR line trace sensor
  pinMode(rearLine,INPUT);
  pinMode(frontLine,INPUT);
}

int ringDetect()
{
  int IRsensorRear = 0; //variable to store value read by sensor
  int IRsensorFront = 0;

  IRsensorRear = digitalRead(rearLine); //pin 10
  IRsensorFront = digitalRead(frontLine); //pin 11
  Serial.print(IRsensorRear); //debugging

  if (IRsensorRear == 1){
    return 1;
  } else if (IRsensorFront == 1){
    return 2;
  } else {
    return 0;
  }
}

void loop() { 

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

  }
}
