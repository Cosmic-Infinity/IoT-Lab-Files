#define trig 13
#define echo 3

float sensorValue;

void setup() {
	Serial.begin(19200);
	pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);

}

void loop() {
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  long pulse = pulseIn(echo, HIGH);

  float distance = pulse/58.31;
  if(distance>2150)
    Serial.println("Out of Range");
  else{
    Serial.print(distance);
    Serial.println(" cm");
  }
}