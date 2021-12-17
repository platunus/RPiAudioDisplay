#include "RPiAudioDisplay.h"
#include "FontRom.h"

PROGMEM const uint8_t FontRom_half_gryph_width[] = {
  FONTROM_GRYPH_WIDTH_HALF_MINCHO_12X, 
  FONTROM_GRYPH_WIDTH_HALF_MINCHO_14X, 
  FONTROM_GRYPH_WIDTH_HALF_MINCHO_16X, 
  FONTROM_GRYPH_WIDTH_HALF_MINCHO_12,  
  FONTROM_GRYPH_WIDTH_HALF_MINCHO_14,  
  FONTROM_GRYPH_WIDTH_HALF_MINCHO_16,  
  FONTROM_GRYPH_WIDTH_HALF_GOTHIC_12X, 
  FONTROM_GRYPH_WIDTH_HALF_GOTHIC_14X, 
  FONTROM_GRYPH_WIDTH_HALF_GOTHIC_16X, 
  FONTROM_GRYPH_WIDTH_HALF_GOTHIC_12,  
  FONTROM_GRYPH_WIDTH_HALF_GOTHIC_14,  
  FONTROM_GRYPH_WIDTH_HALF_GOTHIC_16
};

PROGMEM const uint8_t FontRom_half_gryph_size[] = {
  FONTROM_GRYPH_SIZE_HALF_12X, 
  FONTROM_GRYPH_SIZE_HALF_14X, 
  FONTROM_GRYPH_SIZE_HALF_16X, 
  FONTROM_GRYPH_SIZE_HALF_12,  
  FONTROM_GRYPH_SIZE_HALF_14,  
  FONTROM_GRYPH_SIZE_HALF_16,  
  FONTROM_GRYPH_SIZE_HALF_12X, 
  FONTROM_GRYPH_SIZE_HALF_14X, 
  FONTROM_GRYPH_SIZE_HALF_16X, 
  FONTROM_GRYPH_SIZE_HALF_12,  
  FONTROM_GRYPH_SIZE_HALF_14,  
  FONTROM_GRYPH_SIZE_HALF_16
};

PROGMEM const uint8_t FontRom_full_gryph_size[] = {
  FONTROM_GRYPH_SIZE_MINCHO_12X,
  FONTROM_GRYPH_SIZE_MINCHO_14X,
  FONTROM_GRYPH_SIZE_MINCHO_16X,
  FONTROM_GRYPH_SIZE_MINCHO_12X,
  FONTROM_GRYPH_SIZE_MINCHO_14X,
  FONTROM_GRYPH_SIZE_MINCHO_16X,
  FONTROM_GRYPH_SIZE_GOTHIC_12X,
  FONTROM_GRYPH_SIZE_GOTHIC_14X,
  FONTROM_GRYPH_SIZE_GOTHIC_16X,
  FONTROM_GRYPH_SIZE_GOTHIC_12X,
  FONTROM_GRYPH_SIZE_GOTHIC_14X,
  FONTROM_GRYPH_SIZE_GOTHIC_16X
};

PROGMEM const uint8_t FontRom_half_font_ids[] = {
  FONTROM_ID_HALF_12X, 
  FONTROM_ID_HALF_14X, 
  FONTROM_ID_HALF_16X, 
  FONTROM_ID_HALF_12,  
  FONTROM_ID_HALF_14,  
  FONTROM_ID_HALF_16,  
  FONTROM_ID_HALF_12X, 
  FONTROM_ID_HALF_14X, 
  FONTROM_ID_HALF_16X, 
  FONTROM_ID_HALF_12,  
  FONTROM_ID_HALF_14,  
  FONTROM_ID_HALF_16
};

PROGMEM const uint8_t FontRom_full_font_ids[] = {
  FONTROM_ID_MINCHO_12X,
  FONTROM_ID_MINCHO_14X,
  FONTROM_ID_MINCHO_16X,
  FONTROM_ID_MINCHO_12X,
  FONTROM_ID_MINCHO_14X,
  FONTROM_ID_MINCHO_16X,
  FONTROM_ID_GOTHIC_12X,
  FONTROM_ID_GOTHIC_14X,
  FONTROM_ID_GOTHIC_16X,
  FONTROM_ID_GOTHIC_12X,
  FONTROM_ID_GOTHIC_14X,
  FONTROM_ID_GOTHIC_16X
};

PROGMEM const uint32_t FontRom_font_offsets[] = {
  FONTROM_OFFSET_HALF_12X,
  FONTROM_OFFSET_HALF_14X,
  FONTROM_OFFSET_HALF_16X,
  FONTROM_OFFSET_HALF_12,
  FONTROM_OFFSET_HALF_14,
  FONTROM_OFFSET_HALF_16,
  FONTROM_OFFSET_MINCHO_12X,
  FONTROM_OFFSET_MINCHO_14X,
  FONTROM_OFFSET_MINCHO_16X,
  FONTROM_OFFSET_GOTHIC_12X,
  FONTROM_OFFSET_GOTHIC_14X,
  FONTROM_OFFSET_GOTHIC_16X
};

PROGMEM const uint8_t FontRom_font_lengths[] = {
  12, 14, 16, 12, 14, 16, 24, 28, 32, 24, 28, 32
};

PROGMEM const uint16_t FontRom_ranges[] = {
  0x8140, 0x817e, 0x8180, 0x81ac, 0x81b8, 0x81bf, 0x81c8, 0x81ce, 0x81da, 0x81e8,
  0x81f0, 0x81f7, 0x81fc, 0x81fc, 0x824f, 0x8258, 0x8260, 0x8279, 0x8281, 0x829a,
  0x829f, 0x82f1, 0x8340, 0x837e, 0x8380, 0x8396, 0x839f, 0x83b6, 0x83bf, 0x83d6,
  0x8440, 0x8460, 0x8470, 0x847e, 0x8480, 0x8491, 0x849f, 0x84be, 0x889f, 0x88fc,
  0x8940, 0x897e, 0x8980, 0x89fc, 0x8a40, 0x8a7e, 0x8a80, 0x8afc, 0x8b40, 0x8b7e,
  0x8b80, 0x8bfc, 0x8c40, 0x8c7e, 0x8c80, 0x8cfc, 0x8d40, 0x8d7e, 0x8d80, 0x8dfc,
  0x8e40, 0x8e7e, 0x8e80, 0x8efc, 0x8f40, 0x8f7e, 0x8f80, 0x8ffc, 0x9040, 0x907e,
  0x9080, 0x90fc, 0x9140, 0x917e, 0x9180, 0x91fc, 0x9240, 0x927e, 0x9280, 0x92fc,
  0x9340, 0x937e, 0x9380, 0x93fc, 0x9440, 0x947e, 0x9480, 0x94fc, 0x9540, 0x957e,
  0x9580, 0x95fc, 0x9640, 0x967e, 0x9680, 0x96fc, 0x9740, 0x977e, 0x9780, 0x97fc,
  0x9840, 0x9872, 0x989f, 0x98fc, 0x9940, 0x997e, 0x9980, 0x99fc, 0x9a40, 0x9a7e,
  0x9a80, 0x9afc, 0x9b40, 0x9b7e, 0x9b80, 0x9bfc, 0x9c40, 0x9c7e, 0x9c80, 0x9cfc,
  0x9d40, 0x9d7e, 0x9d80, 0x9dfc, 0x9e40, 0x9e7e, 0x9e80, 0x9efc, 0x9f40, 0x9f7e,
  0x9f80, 0x9ffc, 0xe040, 0xe07e, 0xe080, 0xe0fc, 0xe140, 0xe17e, 0xe180, 0xe1fc,
  0xe240, 0xe27e, 0xe280, 0xe2fc, 0xe340, 0xe37e, 0xe380, 0xe3fc, 0xe440, 0xe47e,
  0xe480, 0xe4fc, 0xe540, 0xe57e, 0xe580, 0xe5fc, 0xe640, 0xe67e, 0xe680, 0xe6fc,
  0xe740, 0xe77e, 0xe780, 0xe7fc, 0xe840, 0xe87e, 0xe880, 0xe8fc, 0xe940, 0xe97e,
  0xe980, 0xe9fc, 0xea40, 0xea7e, 0xea80, 0xeaa4
};

inline void FontRom::select() {
  cbi(FONTROM_PORT_SS, FONTROM_BIT_SS);
}

inline void FontRom::deselect() {
  sbi(FONTROM_PORT_SS, FONTROM_BIT_SS);
}

void FontRom::begin() {
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setDataMode(SPI_MODE0);
}

int8_t FontRom::getGryph(uint8_t type, uint16_t code, uint8_t *pattern) {
#ifdef DEBUG
    mySerial.print("Code: ");
    mySerial.println(code, HEX);
#endif

  int8_t len;
  int32_t start;
  if (type > FONTROM_TYPE_MAX) return -1;

  if (code < 0x100) {
    len = pgm_read_byte_near(FontRom_half_gryph_size + type);
  } else {
    len = pgm_read_byte_near(FontRom_full_gryph_size + type);
  }

  start = getAddress(type, code);
  if (start == -1L) {
    for (uint8_t i = 0; i < len; i++) {
      pattern[i] = 0xff;
    }
    return len;
  }
#ifdef DEBUG
    mySerial.print("Address: ");
    mySerial.println(start);
#endif  
  if (start + len > FONTROM_FLASH_MAX_ADDRESS) return -1;

  select();
  SPI.transfer(FONTROM_FLASH_CMD_READ_DATA);
  SPI.transfer(start >> 16);
  SPI.transfer((start >> 8) & 0xff);
  SPI.transfer(start & 0xff);
  for (uint8_t i = 0; i < len; i++) {
    pattern[i] = SPI.transfer(0x00);
  }
  deselect();
  return len;
}

int32_t FontRom::getAddress(uint8_t type, uint16_t code) {
  uint32_t offset = 0;
  uint16_t first, last;
  uint8_t font_id;
  if (type > FONTROM_TYPE_MAX) return -1L;
  if (code < 0x100) {
    font_id = pgm_read_byte_near(FontRom_half_font_ids + type);
#ifdef DEBUG
    mySerial.print("FONT_ID: ");
    mySerial.println(font_id);
#endif
    return (int32_t)code * pgm_read_byte_near(FontRom_font_lengths + font_id) 
      + pgm_read_dword_near(FontRom_font_offsets + font_id);
  }
  font_id = pgm_read_byte_near(FontRom_full_font_ids + type);
  for (uint8_t i = 0; i < FONTROM_RANGES_SIZE; i += 2) {
    first = pgm_read_word_near(FontRom_ranges + i);
    last  = pgm_read_word_near(FontRom_ranges + i + 1);
    if (code < first) {
      break;
    } else if (code <= last) {
      offset += code - first;
      return offset * pgm_read_byte_near(FontRom_font_lengths + font_id)
        + pgm_read_dword_near(FontRom_font_offsets + font_id);
    } else {
      offset += last - first + 1;
    }
  }
  return -1L;
}

int8_t FontRom::getHalfGryphWidth(uint8_t type) {
  if (type > FONTROM_TYPE_MAX) return -1;
  return pgm_read_byte_near(FontRom_half_gryph_width + type);
}

FontRom::FontRom() {
}

FontRom::~FontRom() {
}
