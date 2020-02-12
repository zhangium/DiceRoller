/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control
For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

// start 
int buttonPin1 = 2;
int buttonStatus1 = 0;
int lastButtonStatus1 = 0;

// mode
int buttonPin2 = 3;
int buttonStatus2 = 0;
int lastButtonStatus2 = 0;

int mode = 1; // mode 1 is normal, mode 2 on for other one
int start = 0; // 0 is stop, 1 is go
unsigned long timer;
int vel=150;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
}

void loop() {
  buttonStatus1 = digitalRead(buttonPin1);
  buttonStatus2 = digitalRead(buttonPin2);
  
  // start/stop timer
  if (buttonStatus1 != lastButtonStatus1){
    if (buttonStatus1 == HIGH){
          startMachine();
          Serial.println("start: ");
          Serial.println(start);
    }
    else{
    }
    delay(50);
  }
  lastButtonStatus1 = buttonStatus1;

  if (buttonStatus2 != lastButtonStatus2){
    if (buttonStatus2 == HIGH){
          changeMode();
          Serial.print("mode: ");
          Serial.println(mode);
    }
    else{
    }
    delay(50);
  }
  lastButtonStatus2 = buttonStatus2;
  
  if (mode == 1){
    vel = 80; 
  }
  if (mode == 2){
    vel = 255;
  }

  if (start == 1){
    myMotor->run(FORWARD);
    for (int i=30; i<vel; i+=mode) {
      myMotor->setSpeed(i);
      Serial.println(i);
      if (mode == 1){
        delay(100);
      }
    }
    for (int i=vel-1; i!=0; i-=mode) {
      myMotor->setSpeed(i);  
      Serial.println(i);
    }
    startMachine();
    Serial.println("tech");
    myMotor->run(RELEASE);
    delay(1000);
  }
}

void startMachine(){
  if (start == 0){
    start = 1;
  }
  else{
    start = 0;
  }
}

void changeMode(){
  if (mode == 1){
    mode = 2;
  }
  else{
    mode = 1;
  }
}
