#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

const int us_1 = 7;  //ultrasonic sensor 1
const int us_2 = 8;  //ultrasonic sensor 2
const int motor_left1 = 3;
const int motor_left2 = 5;
const int motor_right1 = 6;
const int motor_right2 = 9;
const int distance = 15;  //distance to the ground in cm
bool complete = false;
long cm;  //the distance from the sensor in cm
int state = 0;  //what state the rover is in; 0=prelaunch, 1=flight, 2=recovery, 3=landed, 4=forward, 5=turn, 6=stop
int leg = 1;  //which leg to the ground traversal is the rover on

void setup() {
  pinMode(motor_left1, OUTPUT);
  pinMode(motor_left2, OUTPUT);
  pinMode(motor_right1, OUTPUT);
  pinMode(motor_right2, OUTPUT);
  Serial.begin(9600);
}

void loop() { 
  if(state == 0){
    // TODO: look for launch (spike on acceleration)
    delay(100);
  } else if(state == 1) {
    // TODO: check for apogee
  } else if(state == 2) {    //check distance from the ground for parachute release
    // TODO add code to release the drouge
    //send the pings from each sensor
    int d1 = (int)ping(us_1);
    int d2 = (int)ping(us_2);
    if(d1 < distance || d2 < distance){
      // TODO: code for releasing the parachute
      state = 3;
    }
  } else if(state == 3) {  // wait a few seconds to make sure that were on the ground
    delay(5000000);  // wait 5 seconds
    state = 4;
  } else if(state == 4) {  // Drive the specified distance forward
    drive();
    
    // TODO check distance traveled
    
    if(complete){
      if(leg == 1){
        state = 5;
      } else {
        state = 6;
      }
    }
  } else if(state == 5) {  // turn 90 degrees
    turn();
    
    // TODO add code to check distance turned
    
    if(complete){
      leg = 2;
      state = 4;
    }
  } else {  //the program is complete, stop the rover
    delay(100);
  }
  
}

long ping(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);
  
  pinMode(pin, INPUT);
  long duration = pulseIn(pin, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

void drive(){
  analogWrite(motor_left1, 255);
  analogWrite(motor_left2, 255);
  analogWrite(motor_right1, 255);
  analogWrite(motor_right2, 255);
}

void stop(){
  analogWrite(motor_left1, 128);
  analogWrite(motor_left2, 128);
  analogWrite(motor_right1, 128);
  analogWrite(motor_right2, 128);
}

void turn(){
  analogWrite(motor_left1, 0);
  analogWrite(motor_left2, 0);
  analogWrite(motor_right1, 255);
  analogWrite(motor_right2, 255);
}
