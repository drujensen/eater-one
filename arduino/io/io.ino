#include <SoftwareSerial.h>

SoftwareSerial serial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  serial.begin(9600);

  Serial.print(">");
}

char rx;
void loop() {
  if (Serial.available()) {
    rx = Serial.read();
    Serial.write(rx);
    serial.write(rx);
  }
}
