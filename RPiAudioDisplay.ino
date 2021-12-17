#include "RPiAudioDisplay.h"
#include "KanjiOled.h"
#include "TwoWire.h"
#include "IRSend.h"
#include <avr/wdt.h>

#ifdef DEBUG
#define SERIAL_BAURATE  4800U
SendOnlySoftwareSerial mySerial(8); //TX:PB0
#endif

KanjiOled ko = KanjiOled();
IRSend ir = IRSend();
volatile bool stored;
uint8_t instrument;
uint8_t message[KANJI_OLED_MAX_STRING_SIZE];
uint8_t len_message;

void setup() {
#ifdef DEBUG
  mySerial.begin(SERIAL_BAURATE);
#endif

  Wire.begin(51);
  Wire.onReceive(wireHandler);
  stored = false;

  ko.begin();
  ir.begin(IRSEND_FREQ);
#ifdef DEBUG
  mySerial.println(TCCR1A, BIN);
  mySerial.println(TCCR1B, BIN);
  mySerial.println(ICR1);
  mySerial.println(OCR1A);
#endif

  wdt_enable(WDTO_1S);
}

void loop() {
  wdt_reset();
  if (stored) {
#ifdef DEBUG
    mySerial.print("instrument:");
    mySerial.println(instrument, HEX);
#endif
    if (instrument >> 4 == 0) {
#ifdef DEBUG
      mySerial.print("length:");
      mySerial.println(len_message);
#endif
      ko.start(message, len_message, instrument & 0x0f, 20);
    } else {
      switch(instrument) {
        case I2C_OPCODE_PAUSE:
          ko.pause();
          break;
        case I2C_OPCODE_RESUME:
          ko.resume();
          break;
        case I2C_OPCODE_DISPLAY_CLEAR:
          ko.displayClear();
          break;
        case I2C_OPCODE_DISPLAY_ON:
          ko.displayOn();
          break;
        case I2C_OPCODE_DISPLAY_OFF:
          ko.displayOff();
          break;
        case I2C_OPCODE_SLEEP:
          ko.sleep();
          break;
        case I2C_OPCODE_WAKEUP:
          ko.wakeUp();
          break;
        case I2C_OPCODE_VOL_UP:
          ir.send(IRSEND_VOL_UP);
          break;
        case I2C_OPCODE_VOL_DOWN:
          ir.send(IRSEND_VOL_DOWN);
          break;
        case I2C_OPCODE_MUTE:
#ifdef DEBUG
          mySerial.println("MUTE");
#endif
          ir.send(IRSEND_MUTE);
          break;
      }
    }
    stored = false;
  } else {
    ko.scroll();
  }
}

void wireHandler(int n) {
  if (n > KANJI_OLED_MAX_STRING_SIZE + 1 || stored) {
    while(Wire.available()) {
      Wire.read();
    }
    return;
  }
  if (Wire.available()) {
    instrument = Wire.read();
  }
  uint8_t i = 0;
  while(Wire.available()) {
    message[i] = Wire.read();
    i++;
  }
  len_message = i;
  stored = true;
}
