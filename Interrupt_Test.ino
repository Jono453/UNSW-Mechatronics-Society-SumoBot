//Using Arduino Micro for Test
#include <Servo.h> 

#define speedSoundMicro 0.034 
Servo drive_servo;

int leftEnableDC = 6; //pwm
int rightEnableDC = 9; //pwm
int in1 = 2; //digital
int in2 = 3; //digital
int in3 = 4; //digital
int in4 = 5; //digital
volatile int rearInterrupt = 0; 
volatile int frontInterrupt= 1; 

int pos = 0;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
long interval_charge = 3000; //charge for 3 seconds

void setup() {
 

  //interrupts
  pinMode(rearInterrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(rearInterrupt),goForward, RISING); //LOW to HIGH on pin 2
  pinMode(frontInterrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(frontInterrupt),goBackward, RISING); //LOW to HIGH on pin 3
  
  pinMode(13, OUTPUT); //built in LED for debugging
  Serial.begin(9600); //debugging
}

void loop()
{ //main function during battle!!

}

void goForward()
{
   Serial.println("Forward!");
}

void goBackward()
{
   Serial.println("Back!");
}


