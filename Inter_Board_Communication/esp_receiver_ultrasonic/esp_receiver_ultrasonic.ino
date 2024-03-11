#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include "AdafruitIO_WiFi.h"
 
#define WIFI_SSID       "SSID NAME"
#define WIFI_PASS       "PASSWORD"
 
#define IO_USERNAME  "USERNAME"
#define IO_KEY       "APIKEY"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *sending_data = io.feed("Event");

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

    io.connect();
 
  // wait for a connection
    while(io.status() < AIO_CONNECTED) 
    {
      Serial.print(".");
      delay(500);
    }


}

void loop() {

  io.run();
  mySerial.listen();
    if (mySerial.available() > 0) {
      int data = mySerial.read();

      sending_data->save((float)(data));
      Serial.print("Data Sent : ");
      Serial.print((data/58.31));
      Serial.print(" cm");
      Serial.print("\n");
    }
}
