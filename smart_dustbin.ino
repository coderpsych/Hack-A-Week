#include <Servo.h>
#include <SoftwareSerial.h>


int TRIGGER_PIN_1=2;
 int ECHO_PIN_1=3;
int TRIGGER_PIN_2=4;
int ECHO_PIN_2=5;
int SERVO_PIN=6;
Servo servo;

SoftwareSerial gsmSerial(7, 8); 

const int distanceThreshold = 10; 

void setup() {
  pinMode(TRIGGER_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);

  servo.attach(SERVO_PIN);

  
  gsmSerial.begin(9600);
  delay(1000);
  sendSMS("Smart Dustbin initialized.");
}

void loop() {
 
  long duration1, distance1;
  digitalWrite(TRIGGER_PIN_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_1, LOW);
  duration1 = pulseIn(ECHO_PIN_1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  
  long duration2, distance2;
  digitalWrite(TRIGGER_PIN_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_2, LOW);
  duration2 = pulseIn(ECHO_PIN_2, HIGH);
  distance2 = duration2 * 0.034 / 2;

 
  if (distance1 < distanceThreshold) {
    servo.write(90); 
    delay(2000); 
  }

  
  if (distance2 < distanceThreshold) {
    servo.write(0); 
    delay(2000); 
  }

  
  if (distance1 > distanceThreshold && distance2 > distanceThreshold) {
    sendSMS("Dustbin is empty.");
  }

  delay(1000); 
}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1"); 
  delay(1000);
  gsmSerial.println("AT+CMGS=\"+1234567890\"");
  delay(1000);
  gsmSerial.println(message);
  delay(1000);
  gsmSerial.println((char)26); 
  delay(1000);
}
