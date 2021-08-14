#include <PS2KeyAdvanced.h>
#include <PS2KeyMap.h>
#include <SoftwareSerial.h>

#define BUS_D0 3
#define BUS_D7 10
#define LATCH 1

#define DATA 0
#define CLOCK 2

PS2KeyAdvanced keyboard;
PS2KeyMap keymap;
SoftwareSerial serial(11, 12); // RX, TX

void setup() {
  serial.begin(9600);

  keyboard.begin(0, 2);
  keyboard.setNoBreak(1);
  keyboard.setNoRepeat(1);
  keyboard.echo();
  delay(6);
  char rx = keyboard.read();  
  keymap.selectMap((char *) "US"); // set which type of keyboard we have

  pinMode(LATCH, OUTPUT);
  digitalWrite(LATCH, HIGH);

  for (int pin = BUS_D0; pin <= BUS_D7; pin += 1) {
    pinMode(pin, OUTPUT);
  }
}

void send(byte rx) {
  digitalWrite(3, (1 << 7) & rx);
  digitalWrite(4, (1 << 6) & rx);
  digitalWrite(5, (1 << 5) & rx);
  digitalWrite(6, (1 << 4) & rx);
  digitalWrite(7, (1 << 3) & rx);
  digitalWrite(8, (1 << 2) & rx);
  digitalWrite(9, (1 << 1) & rx);
  digitalWrite(10, (1 << 0) & rx);
  
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
  delay(5);
  digitalWrite(LATCH, HIGH);
}

uint16_t rx;
byte value;
void loop() {
  if(keyboard.available()) {
    rx = keyboard.read();
    if((rx & 0xFF) > 0) {
      if((value = keymap.remapKey(rx)) > 0) {
        send(value);
      }
    }
  }
  if (serial.available()) {
    rx = serial.read();
    value = byte(rx);
    send(value);
  }
}
