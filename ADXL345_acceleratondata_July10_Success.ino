#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup(void) {
  Serial.begin(115200);
  if (!accel.begin()) {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }
  /* Set the range to whatever is appropriate for your project */
  // accel.setRange(ADXL345_RANGE_16_G);
  // accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
  accel.setRange(ADXL345_RANGE_2_G);
  /* Set the data rate to a value between 0.10 Hz and 800 Hz */
  accel.setDataRate(ADXL345_DATARATE_3200_HZ);
}

void loop(void) {
  sensors_event_t event;
  accel.getEvent(&event);
  
  Serial.print(millis());
  Serial.print(",");
  Serial.print(event.acceleration.x, 4);
  Serial.print(",");
  Serial.print(event.acceleration.y, 4);
  Serial.print(",");
  Serial.println(event.acceleration.z, 4);

 
}
