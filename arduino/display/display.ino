#include <fontALL.h>
#include <video_gen.h>
#include <TVout.h>
#include <CircularBuffer.h>

#define LATCH 10

TVout TV;
CircularBuffer<byte,32> buffer;

void setup() {
  attachInterrupt(digitalPinToInterrupt(3), interrupt, RISING);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(8, INPUT);

  pinMode(LATCH, OUTPUT);
  digitalWrite(LATCH, HIGH);
    
  TV.begin(_NTSC);
  TV.select_font(font6x8);
  TV.clear_screen();
  TV.set_cursor(0,0);
}

void interrupt() {
  buffer.push(read());
}

byte read() {
  byte data = 0;

  data = (data << 1) + 0;
  data = (data << 1) + digitalRead(0);
  data = (data << 1) + digitalRead(1);
  data = (data << 1) + digitalRead(2);
  data = (data << 1) + digitalRead(4);
  data = (data << 1) + digitalRead(5);
  data = (data << 1) + digitalRead(6);
  data = (data << 1) + digitalRead(8);

  return data;
}

void ready() {
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
  delay(5);
  digitalWrite(LATCH, HIGH);  
}

void loop() {
  if (!buffer.isEmpty()) {
    byte value = buffer.shift();
    switch (value) {
      case 07:
        TV.tone(400, 250);
        break;
      case 13: //enter
        TV.println();
        break;
      case 27: //escape
        TV.set_cursor(0,0);
        TV.clear_screen();
        break;
      default:
        TV.print(value);  
        break;
    }
  } else {
    ready();
  }
}
