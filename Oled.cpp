#include "Oled.h"
#include "RPiAudioDisplay.h"

void Oled::send(uint8_t data) {
  OLED_PORT_DATA = data;
  sbi(OLED_PORT_CONTROL, OLED_BIT_EN);
  cbi(OLED_PORT_CONTROL, OLED_BIT_EN);
}

void Oled::wait() {
  uint8_t count = 255;
  uint8_t busy = 1;
  uint8_t backup;

  // Data Bus: input/Hi-Z/no pullup
  OLED_DDR_DATA = 0x00;
  OLED_PORT_DATA = 0x00;

  // Backup RS flag
  backup = OLED_PIN_CONTROL & ~(_BV(OLED_BIT_RS));

  // RS:0(=instruction), RW:1(=read)
  cbi(OLED_PORT_CONTROL, OLED_BIT_RS);
  sbi(OLED_PORT_CONTROL, OLED_BIT_RW);

  while (busy && (count-- > 0)) {
    sbi(OLED_PORT_CONTROL, OLED_BIT_EN);
//    delayMicroseconds(2);
    busy = OLED_PIN_DATA & _BV(OLED_BIT_BUSY);
    cbi(OLED_PORT_CONTROL, OLED_BIT_EN);
  }

  // RS:restore, RW:0(=write)
  OLED_PORT_CONTROL = OLED_PORT_CONTROL & ~(_BV(OLED_BIT_RS)) | backup;
  cbi(OLED_PORT_CONTROL, OLED_BIT_RW);

  // Data Bus: output
  OLED_DDR_DATA = 0xFF;
}

void Oled::displayOn() {
#ifdef DEBUG
  mySerial.println("displayOn()");
#endif

  wait();

  // 00001DCB
  // D(DISPLAY ON/OFF): 1(On)
  // C(CURSOR DISPLAY CONTROL BIT): 0(Off)
  // B(BLINKING CONTROL BIT): 0(Off)
  send(0b00001100);
}

void Oled::displayOff() {
#ifdef DEBUG
  mySerial.println("displayOff()");
#endif

  wait();

  // 00001DCB
  // D(DISPLAY ON/OFF): 1(On)
  // C(CURSOR DISPLAY CONTROL BIT): 0(Off)
  // B(BLINKING CONTROL BIT): 0(Off)
  send(0b00001000);
}

void Oled::displayClear() {
#ifdef DEBUG
  mySerial.println("displayClear()");
#endif

  wait();

  send(0b00000001);
}

void Oled::setGraphicCursor(uint8_t x, uint8_t y) {
  wait();
  send(0b10000000 | x);

  wait();
  send(0b01000000 | y);
}

void Oled::sleep() {
#ifdef DEBUG
  mySerial.println("sleep()");
#endif

  wait();

  // 0001MP11
  // M(Graphic/Character Mode): 1(Graphic Mode)
  // P(Internal Power On/Off): 0(Off)
  send(0b00011011);
}

void Oled::wakeUp() {
#ifdef DEBUG
  mySerial.println("wakeUp()");
#endif
  OLED_PORT_CONTROL &= ~(_BV(OLED_BIT_RS) | _BV(OLED_BIT_RW));

  // Sync
  wait();
  send(0);
  send(0);
  send(0);
  send(0);
  send(0);

  // FunctionSet
  // 001DNFff
  // D(INTERFACE DATA LENGTH CONTROL BIT): 1(8bit)
  // N(NUMBER OF DISPLAY LINE): 1(2lines)
  // F(CHARACTER FONT SET): 0(5x8)
  // ff(FONT TABLE SELECTION): 00(ENGLISH_JAPANESE CHARACTER FONT TABLE)
  wait();
  send(0b00111000);

  // EntryModeSet
  // 000001IS
  // I(INCREMENT/DECREMENT BIT): 1(incremental)
  // S(SHIFT ENTIRE DISPLAY CONTROL BIT): 0(not shifted)
  wait();
  send(0b00000110);

  // GraphicModeSet
  // 0001MP11
  // M(Graphic/Character Mode): 1(Graphic Mode)
  // P(Internal Power On/Off): 1(On)
  wait();
  send(0b00011111);
}

void Oled::begin() {
#ifdef DEBUG
  mySerial.println("begin()");
#endif

  // Data Bus/Control Bus: output
  OLED_DDR_DATA = 0xFF;
  OLED_DDR_CONTROL |= _BV(OLED_BIT_EN) | _BV(OLED_BIT_RS) | 
    _BV(OLED_BIT_RW);

  // Data Bus/Conrtol Bus: All Zero
  OLED_PORT_DATA = 0x00;
  OLED_PORT_CONTROL &= ~(_BV(OLED_BIT_EN) | _BV(OLED_BIT_RS) |
    _BV(OLED_BIT_RW));

  delay(500);
  wakeUp();
}

void Oled::draw(uint8_t x, uint8_t y, uint8_t *data, uint8_t len) {
  if (x + len > OLED_X_SIZE || y >= OLED_Y_SIZE) return;

  cbi(OLED_PORT_CONTROL, OLED_BIT_RS);
  setGraphicCursor(x, y);

  sbi(OLED_PORT_CONTROL, OLED_BIT_RS);
  for (uint8_t i = 0; i < len; i++) {
    send(data[i]);
  }
}

void Oled::test() {
  displayOn();
  uint8_t d = 0;
  uint8_t oled_buf[OLED_Y_SIZE][OLED_X_SIZE];
  for (uint8_t i = 0; i < OLED_Y_SIZE; i++) {
    for (uint8_t j = 0; j < OLED_X_SIZE; j++) {
      oled_buf[i][j] = d++;
    }
  }
  for (uint8_t i = 0; i < OLED_Y_SIZE; i++) {
    if (offset != 0) draw(0, i, oled_buf[i] + (OLED_X_SIZE - offset), offset);
    draw(offset, i, oled_buf[i], OLED_X_SIZE - offset);
  }
  offset--;
  if (offset >= OLED_X_SIZE) offset = OLED_X_SIZE - 1;
  delay(50);  
}

Oled::Oled() {
}

Oled::~Oled() {
}
