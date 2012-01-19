#include <Servo.h> 

Servo myservo;
const int  sensorPin = A0;
int pos = 0; 
int sensorValue = 0;
const int queue_length = 5;
int queue [queue_length];
long starttime;
int justClose = 0;
long avg; 

void setup() {
  Serial.begin(9600);
  myservo.attach(11);
  starttime = millis();
  myservo.write(180);
}

void loop() {

  long elapsedtime = millis() - starttime;

  if (elapsedtime > 1000 ) {
    sensorValue = analogRead(sensorPin);
    long sum = 0;
    for (int i = queue_length-1; i > 0; i--) {
       queue[i] = queue[i-1];
       sum += queue[i];
    }
    queue[0] = sensorValue;
    sum += queue[0];
    avg = sum/queue_length; 
    starttime = millis();
     Serial.println(avg);
  }
 
  if (avg > 100) { justClose = 1;}
  if (avg < 60 && justClose) {

    //Serial.println("FLUSH");
                             
      myservo.write(11);               
      delay(15000);
      myservo.write(180);  

    justClose = 0;
  }
}
