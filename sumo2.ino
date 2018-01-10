#define speedSoundMicro 0.034 
#include <Servo.h> //library. contains commands for controlling the servo
Servo lever_servo; 

int trigPin = 7; //digital trigger pin *
int echoPin = 8; //digital echo pin *
int leftEnableDC = 6; //pwm
int rightEnableDC = 9; //pwm *
int in1 = 2; //digital
int in2 = 3; //digital
int in3 = 4; //digital
int in4 = 5; //digital
int pos = 0; // variable to control servo position
int updateInterval = 15;
int increment = 1;
int servoPin = 10;

volatile int rearInterrupt = 0; 
volatile int frontInterrupt = 1;
volatile int wentForward = 0;
volatile int wentBackward = 0; 

unsigned long currentMillis;
unsigned long UDetectMillis;
unsigned long interval_charge = 3000; //charge for 3 seconds
int motorstate = 0;

void setup() {

  //pins for ultrasonic sensor
  pinMode(trigPin,OUTPUT); 
  pinMode(echoPin,INPUT);

  //pins for motor controller
  pinMode(leftEnableDC,OUTPUT);
  pinMode(rightEnableDC,OUTPUT);
 
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  //interrupts
  pinMode(frontInterrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(frontInterrupt),goBackward, RISING); //pin 1 IR
  
  pinMode(rearInterrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(rearInterrupt),goForward, RISING); //pin 0 IR

  //servo
  lever_servo.attach(10);
  
  //debugging
  pinMode(13, OUTPUT); //built in LED
  Serial.begin(9600); //serial communication

  //delay(3000); //3 seconds at start of battle
  //at start move arm from starting position to battle position
  lever_servo.write(110); //rotates arm down
  delay(200); //time to reach parallel to ramp
  
}

//Ultrasonic sensor function
int ultrasonicFunction()
{
  
  long duration;
  int distance; //robot distance ~10cm
  
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10); //creates the sound wave to hit other robot
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH); //timing of pulse. from sending ping to getting echo off object
  distance = duration*speedSoundMicro/2; //in cm
  
  return distance;  
}

//IR line tracer sensor function. 0 = white. 1 = black
void ringDetect()
{
  int IRsensorRear = digitalRead(rearInterrupt); //interrupt pin 0
  int IRsensorFront = digitalRead(frontInterrupt); //interrupt pin 1
}

//function for the motor controller
void motor(int pin1,int pin2,int rightSpeed, int leftSpeed)
{  
  if (pin1 == 1) {
    analogWrite(leftEnableDC,leftSpeed);
    digitalWrite(in1,HIGH); //forward 
    digitalWrite(in2,LOW);  
  }
  else
  {
    analogWrite(leftEnableDC,leftSpeed);
    digitalWrite(in1,LOW); 
    digitalWrite(in2,HIGH);
  }

  if (pin2 == 1) {
    analogWrite(rightEnableDC,rightSpeed);
    digitalWrite(in3,HIGH); 
    digitalWrite(in4,LOW);  
  }
  else
  {
    analogWrite(rightEnableDC,rightSpeed);
    digitalWrite(in3,LOW); 
    digitalWrite(in4,HIGH);  
  }
}

//main function during battle!!
void loop() { 

  lever_servo.write(110); //rotates arm down
  delay(50); //time to reach parallel to ramp
  lever_servo.write(70); //rotates arm down
  delay(50); //time to reach parallel to ramp
  lever_servo.write(90);
           
  motor(1,1,240,240);//normal speed. when inside ring
   
    if (wentBackward == 1) {
        wentBackward = 0; 
        motor(1,0,180,180);
        delay(550);        
    }
      
    if (wentForward == 1) {
        wentForward = 0;
        motor(1,0,180,180);
        delay(550);       
    }
        
    if (ultrasonicFunction() <= 15) { //Detects another robot near
      UDetectMillis = millis(); //snapshot of time
      motorstate = 1;
      //steer(); //motorized lever lifts up and resets
      motor(1,1,250,250);
      delay(3000);
    }   
    if (motorstate == 1) {
      if ((millis() - UDetectMillis) > interval_charge) {          
        motor(1,1,170,170); //return back to normal speed                
        motorstate = 0;
      } else {
        motor(1,1,200,200);
      }
   }   
}

void goForward()
{
   motor(1,1,160,160);
   delayMicroseconds(2000);
   wentForward = 1;
}

void goBackward()
{
   motor(0,0,160,160);   
   delayMicroseconds(2000);
   wentBackward = 1;
}

void steer() 
{
  lever_servo.write(70); //spin lever up
  delay(600);
  //lever_servo.write(110); //spin lever down
  //delay(550);
}

