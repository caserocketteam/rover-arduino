const int us_1 = 7;  //ultrasonic sensor 1
const int us_2 = 8;  //ultrasonic sensor 2
const int distance = 100;  //distance to the ground in cm
long cm;  //the distance from the sensor in cm
int state = 0;  //what state the rover is in; 0=prelaunch, 1=flight, 2=recovery, 3=landed, 4=forward, 5=turn, 6=stop

void setup() {
  Serial.begin(9600);
}

void loop() { 
  if(state == 0){
    // TODO: look for launch (spike on acceleration)
    delay(100);
  } else if(state == 1) {
    // TODO: check for apogee
  } else if(state == 2) {    //check distance from the ground for parachute release
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
    // TODO: Drive forward (signals to motor controllers, measure distance)
  } else if(state == 5) {  // turn 90 degrees
    // TODO: Turn (signals to motor controllers, measure rotation)
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
