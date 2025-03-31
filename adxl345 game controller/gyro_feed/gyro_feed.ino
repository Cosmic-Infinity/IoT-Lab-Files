#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); //assign an id to the sensor


void setup(void) {
#ifndef ESP8266
  while (!Serial)
    ;  // for Leonardo/Micro/Zero
#endif
  Serial.begin(115200);

  /* Initialize the sensor */
  if (!accel.begin()) {
    Serial.println("No ADXL345 detected... Check wiring!");
    while (1)
      ;
  }
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop(void) {
    sensors_event_t event;
    accel.getEvent(&event);
    Serial.printf("%f %f\n", event.acceleration.x * 100, event.acceleration.y * 100);

    delay(100);
}

