#include <SoftwareSerial.h>

const byte rxPin = D6;
const byte txPin = D5;
// Set up a new SoftwareSerial object
SoftwareSerial mySerial (rxPin, txPin);

void setup() {
    Serial.begin(19200);
    mySerial.begin(19200);
    Serial.println("Ready");
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);


}

void loop() {
  mySerial.listen();
  if (mySerial.available() > 0) {
      Serial.print(mySerial.read());         // Print as an ASCII-encoded decimal
      Serial.print("\n");
    }
}
