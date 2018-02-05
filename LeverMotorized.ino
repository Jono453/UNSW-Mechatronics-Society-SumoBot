#include <Servo.h> //library. contains commands for controlling the servo

Servo steer_servo;  
char buttonPress;// for incoming serial data

void setup() { 
  steer_servo.attach(11);
  Serial.begin(9600);
}

void loop(){
  
 buttonPress = Serial.read();

  if (buttonPress == 'A' || buttonPress == 'a')
    {
        steer();
    }
  if (buttonPress == 'B'|| buttonPress == 'b')
    {
        steer_servo.write(90);  
    }  
}

void steer() 
{
  steer_servo.write(70); //spin lever up
  delay(550);
  steer_servo.write(110); //spin lever down
  delay(550);
}

