#include <MRETV.h>
#include <textfont.h>
#include <CircularBuffer.h>

#ifndef default_extensions
  #define default_extensions
  #define noaudio
  #define screenscrools
  #define fontheight 8
  #define noserialsend
#endif

#define asciibufsize 21*45

#define LATCH 0

CircularBuffer<byte,32> buffer;

uchar  asciibuf[asciibufsize];
void setup() {
  //attachInterrupt(digitalPinToInterrupt(3), interrupt, RISING);
  pinMode(0, INPUT);
  for (int pin = 4; pin <= 10; pin += 1) {
    pinMode(pin, INPUT);
  }

  pinMode(LATCH, OUTPUT);
  digitalWrite(LATCH, HIGH);
    
  Screen.begin(textfont,asciibuf, 21*fontheight,45,20,25,1); 
  Screenprogstr("This is a test to see what the text looks like.");

}

void interrupt() {
  buffer.push(read());
}

byte read() {
  byte data = 0;

  data = (data << 1) + 0;
  data = (data << 1) + digitalRead(0);
  data = (data << 1) + digitalRead(4);
  data = (data << 1) + digitalRead(5);
  data = (data << 1) + digitalRead(6);
  data = (data << 1) + digitalRead(7);
  data = (data << 1) + digitalRead(8);
  data = (data << 1) + digitalRead(9);

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
      case 27: //escape
        Screen.fill(' ');
        break;
      default:
        Screen.render(value);  
        break;
    }
  } else {
    ready();
  }
}
