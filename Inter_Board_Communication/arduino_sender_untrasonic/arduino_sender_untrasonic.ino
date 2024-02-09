#include <SoftwareSerial.h>

#define trig 13
#define echo 3


const byte rxPin = 7;
const byte txPin = 8;
// Set up a new SoftwareSerial object
SoftwareSerial mySerial (rxPin, txPin);

float sensorValue;

void setup() {
	Serial.begin(19200);
	pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(19200);

}

void loop() {
  digitalWrite(trig, HIGH);
  delay(500);
  digitalWrite(trig, LOW);
  long pulse = pulseIn(echo, HIGH);

  float distance = pulse/58.31;
  if(distance>2150){
    Serial.println("Out of Range");
    mySerial.write("OOR");
  }
  else{
    Serial.print(distance);
    mySerial.write(distance);
    Serial.println(" cm");
  }
}
