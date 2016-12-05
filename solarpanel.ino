
#include <Servo.h>
Servo myservo;
int pos = 0;

void setup() {
  
  Serial.begin(9600);
   myservo.attach(9);
   
}


void loop() {
  
  int sensor1 = analogRead(A0);
  Serial.print("1:");
  Serial.println(sensor1);
  int sensor2 = analogRead(A1);
  Serial.print("2:");
  Serial.println(sensor2);
  pos= myservo.read();
  if (sensor1>200 || sensor2>200)
  {
    if (abs(sensor1-sensor2)<=3)
  {
    goto next;
  }
    if (sensor1 > sensor2)
    {
      myservo.write(pos+3);    
    }
    if (sensor1 < sensor2)
    {
      myservo.write(pos-3);    
    }
  }
  next:
  delay(300);       


}