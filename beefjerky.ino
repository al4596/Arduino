#include <NewPing.h> //ultrasonic sensor
#include <Servo.h> //servo 

//Qti pins
#define leftMost 11
#define midLeft 10 
#define midRight 9 
#define rightMost 8 

long leftMostQTI, midLeftQTI, midRightQTI, rightMostQTI; 

//servo pins
#define leftServoPin 6
#define rightServoPin 5

//ultrasonic sensor pins
#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

Servo leftServo; 
Servo rightServo; 

long RCTime(int sensorIn)
{
  long duration = 0;
  pinMode(sensorIn, OUTPUT);     // Make pin OUTPUT
  digitalWrite(sensorIn, HIGH);  // Pin HIGH (discharge capacitor)
  delay(1);                      // Wait 1ms
  pinMode(sensorIn, INPUT);      // Make pin INPUT
  digitalWrite(sensorIn, LOW);   // Turn off internal pullups
  while(digitalRead(sensorIn)){  // Wait for pin to go LOW
     duration++;
  }
  return duration;
}

void goStraight(){
  leftServo.write(180); 
  rightServo.write(0); 
}

void goBackward(){
  leftServo.write(0); 
  rightServo.write(180); 
}

void turnLeft(){
  leftServo.write(0); 
  rightServo.write(0);
}

void turnRight(){
  leftServo.write(180); 
  rightServo.write(180);
}

void turnSlightLeft(){
  leftServo.write(50);
  rightServo.write(50);
}

void turnSlightRight(){
  leftServo.write(110);
  rightServo.write(110);
}

void stopMotor(){
  leftServo.write(90); 
  rightServo.write(90);
}

void setup() {
  //initialize servo 
  leftServo.attach(leftServoPin); 
  rightServo.attach(rightServoPin); 
  Serial.begin(9600);
}

void loop() {

  Serial.print(RCTime(11)); 
  Serial.print("\t");
  Serial.print(RCTime(10)); 
  Serial.print("\t");
  Serial.print(RCTime(9)); 
  Serial.print("\t");
  Serial.print(RCTime(8)); 
  Serial.println("\t"); 
  
  leftMostQTI = RCTime(leftMost); 
  midLeftQTI = RCTime(midLeft);
  midRightQTI = RCTime(midRight); 
  rightMostQTI = RCTime(rightMost);

  if(midLeftQTI > 120 && midRightQTI >120){ //bigger than 120 means black tape
      goStraight();
    }
    else{stopMotor();}
  //if(sonar.ping_cm()> 4 && sonar.ping_cm() < 500){
    if(midLeftQTI > 120 && midRightQTI >120){ //bigger than 120 means black tape
      if (leftMostQTI < 120 && rightMostQTI < 120){
        goStraight();
      }
      else if (rightMostQTI > 120){
        turnRight();
      }
      else if (leftMostQTI > 120){
        turnLeft();
      }
    }
    else if(midLeftQTI <120){
      turnRight(); 
    }
    else if(midRightQTI < 120){
      turnLeft(); 
    }
    else if(midRightQTI <120 && midLeftQTI < 120){
      if(leftMostQTI > 120){
        turnLeft(); 
      }
      else if(rightMostQTI > 120){
        turnRight(); 
      }
      else if (midLeftQTI >120 && midRightQTI > 120 && rightMostQTI > 120 && leftMostQTI > 120){
        goStraight();  
      }
      else{
        turnLeft();
      }
    }
  
  //}
//  else{
//    stopMotor();
//  }
  
}
