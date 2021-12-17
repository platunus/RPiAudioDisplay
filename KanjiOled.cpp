#include "RPiAudioDisplay.h"
#include "KanjiOled.h"

KanjiOled::KanjiOled() {
}

KanjiOled::~KanjiOled() {
}

void KanjiOled::begin() {
  oled = Oled();
  rom = FontRom();
  
  oled.begin();
  rom.begin();
}

void KanjiOled::displayClear() {
  oled.displayClear();
}

void KanjiOled::displayOff() {
  oled.displayOff();
}

void KanjiOled::displayOn() {
  oled.displayOn();
}

void KanjiOled::sleep() {
  suspend = true;
  oled.sleep();
}

void KanjiOled::wakeUp() {
  suspend = false;
  oled.wakeUp();
}

int8_t KanjiOled::start(uint8_t *message, uint8_t len, uint8_t font_type, uint16_t interval) {
  if (len > KANJI_OLED_MAX_STRING_SIZE || interval > KANJI_OLED_MAX_INTERVAL || font_type > FONTROM_TYPE_MAX) return -1;
  memcpy(msg, message, len);
  len_msg = len;
  this->font_type = font_type;
  this->interval = interval;

  int8_t status;
  uint8_t width_half = rom.getHalfGryphWidth(font_type);
  uint8_t len_x = (OLED_X_SIZE + width_half - 1) / width_half;
  len_x = (len_x > len) ? len : len_x;
  width_window = (uint16_t)(rom.getHalfGryphWidth(font_type)) * len;
  pos_vram = 0;
  suspend = false;
  overflow = true;
  pos_gryph = 0;
  oled.displayClear();
  for (pos_msg = 0; pos_msg < len_x;) {
#ifdef DEBUG
  mySerial.print("pos_msg:");
  mySerial.println(pos_msg, DEC);
#endif
    writeVram(true);
  }

#ifdef DEBUG
  mySerial.print("Width:");
  mySerial.println(width_half * len, DEC);
  mySerial.print("pos_vram:");
  mySerial.println(pos_vram, DEC);
#endif
  if (width_half * len > OLED_X_SIZE) {
    len_msg = len + KANJI_OLED_PADDING_SIZE;
    for (uint8_t i = 0; i <KANJI_OLED_PADDING_SIZE; i++) {
      msg[len + i] = 0x00;
    }
  } else {
    len_msg = len;
    for (uint8_t i = pos_vram; i < OLED_X_SIZE; i++) {
      vram[1][i] = 0; 
      vram[0][i] = 0;
      overflow = false;
    }
  }
  
  for (uint8_t i = 0; i < OLED_Y_SIZE; i++) {
    oled.draw(0, i, vram[i], OLED_X_SIZE);
  }
  oled.displayOn();
  delay(KANJI_OLED_PAUSE);
  prev = millis();
  return 0;
}

void KanjiOled::writeVram(bool first) {
  int8_t len_gryph;

  if (pos_gryph == 0) {
    if (msg[pos_msg] <= 0x7f || 0xa1 <= msg[pos_msg] && msg[pos_msg] <= 0xdf) {
      len_gryph = rom.getGryph(font_type, msg[pos_msg], gryph);      
      width_gryph = rom.getHalfGryphWidth(font_type);
      pos_msg++;
    } else {
      len_gryph = rom.getGryph(font_type, (uint16_t)msg[pos_msg] << 8 | msg[pos_msg + 1], gryph);
      width_gryph = rom.getHalfGryphWidth(font_type) * 2;
      pos_msg += 2;
    }    
  }  
  if (first) {
    for (uint8_t i = 0; i < len_gryph / 2 && pos_vram < OLED_X_SIZE; i++, pos_vram++, pos_gryph++) {
      vram[1][pos_vram] = gryph[i * 2];  
      vram[0][pos_vram] = gryph[i * 2 + 1];
    }
  } else if (overflow) {
    pos_vram = pos_vram % OLED_X_SIZE;
    vram[1][pos_vram] = gryph[pos_gryph * 2];
    vram[0][pos_vram] = gryph[pos_gryph * 2 + 1] ;
    pos_gryph++;
    pos_vram++;
  }
  if (pos_gryph == width_gryph) {
    pos_gryph = 0;
    if (pos_msg == len_msg && !first) {
      pos_msg = 0;
    }
  }
}

void KanjiOled::scroll() {
  uint32_t now = millis();
  if (!overflow || suspend) return;
  if (now - prev > interval) {
    if (pos_msg < len_msg || pos_msg == len_msg && pos_gryph < width_gryph) {
      writeVram(false);
      for (uint8_t i = 0; i < OLED_Y_SIZE; i++) {
        oled.draw(0, i, vram[i] + pos_vram, OLED_X_SIZE - pos_vram);
      }
      for (uint8_t i = 0; i < OLED_Y_SIZE; i++) {
        oled.draw(OLED_X_SIZE - pos_vram, i, vram[i], pos_vram);
      }
    }
    prev = now;
  }
}

void KanjiOled::pause() {
  suspend = true;
}

void KanjiOled::resume() {
  suspend = false;
}
