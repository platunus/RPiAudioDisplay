#include <SPI.h>

#define FONTROM_PORT_SS PORTB
#define FONTROM_DDR_SS DDRB
#define FONTROM_BIT_SS 2

#define FONTROM_FLASH_MAX_ADDRESS (8UL * 1024 * 1024)
#define FONTROM_GRYPH_MAX_SIZE 32
#define FONTROM_FLASH_CMD_READ_DATA 0x03

#define FONTROM_TYPE_MINCHO_12X 0
#define FONTROM_TYPE_MINCHO_14X 1
#define FONTROM_TYPE_MINCHO_16X 2
#define FONTROM_TYPE_MINCHO_12  3
#define FONTROM_TYPE_MINCHO_14  4
#define FONTROM_TYPE_MINCHO_16  5
#define FONTROM_TYPE_GOTHIC_12X 6
#define FONTROM_TYPE_GOTHIC_14X 7
#define FONTROM_TYPE_GOTHIC_16X 8
#define FONTROM_TYPE_GOTHIC_12  9
#define FONTROM_TYPE_GOTHIC_14  10
#define FONTROM_TYPE_GOTHIC_16  11
#define FONTROM_TYPE_MAX        FONTROM_TYPE_GOTHIC_16

#define FONTROM_GRYPH_WIDTH_HALF_MINCHO_12X 6
#define FONTROM_GRYPH_WIDTH_HALF_MINCHO_14X 7
#define FONTROM_GRYPH_WIDTH_HALF_MINCHO_16X 8
#define FONTROM_GRYPH_WIDTH_HALF_MINCHO_12  6
#define FONTROM_GRYPH_WIDTH_HALF_MINCHO_14  7
#define FONTROM_GRYPH_WIDTH_HALF_MINCHO_16  8
#define FONTROM_GRYPH_WIDTH_HALF_GOTHIC_12X 6
#define FONTROM_GRYPH_WIDTH_HALF_GOTHIC_14X 7
#define FONTROM_GRYPH_WIDTH_HALF_GOTHIC_16X 8
#define FONTROM_GRYPH_WIDTH_HALF_GOTHIC_12  6
#define FONTROM_GRYPH_WIDTH_HALF_GOTHIC_14  7
#define FONTROM_GRYPH_WIDTH_HALF_GOTHIC_16  8

#define FONTROM_GRYPH_SIZE_HALF_12X     12
#define FONTROM_GRYPH_SIZE_HALF_14X     14
#define FONTROM_GRYPH_SIZE_HALF_16X     16
#define FONTROM_GRYPH_SIZE_HALF_12      12
#define FONTROM_GRYPH_SIZE_HALF_14      14
#define FONTROM_GRYPH_SIZE_HALF_16      16
#define FONTROM_GRYPH_SIZE_MINCHO_12X   24
#define FONTROM_GRYPH_SIZE_MINCHO_14X   28
#define FONTROM_GRYPH_SIZE_MINCHO_16X   32
#define FONTROM_GRYPH_SIZE_GOTHIC_12X   24
#define FONTROM_GRYPH_SIZE_GOTHIC_14X   28
#define FONTROM_GRYPH_SIZE_GOTHIC_16X   32

#define FONTROM_ID_HALF_12X     0
#define FONTROM_ID_HALF_14X     1
#define FONTROM_ID_HALF_16X     2
#define FONTROM_ID_HALF_12      3
#define FONTROM_ID_HALF_14      4
#define FONTROM_ID_HALF_16      5
#define FONTROM_ID_MINCHO_12X   6
#define FONTROM_ID_MINCHO_14X   7
#define FONTROM_ID_MINCHO_16X   8
#define FONTROM_ID_GOTHIC_12X   9
#define FONTROM_ID_GOTHIC_14X   10
#define FONTROM_ID_GOTHIC_16X   11

#define FONTROM_SIZE_HALF_12    3072UL
#define FONTROM_SIZE_HALF_14    3584UL
#define FONTROM_SIZE_HALF_16    4096UL
#define FONTROM_SIZE_FULL_12    165096UL
#define FONTROM_SIZE_FULL_14    192612UL
#define FONTROM_SIZE_FULL_16    220128UL

#define FONTROM_OFFSET_HALF_12X   (                                             0)
#define FONTROM_OFFSET_HALF_14X   (0                       + FONTROM_SIZE_HALF_12)
#define FONTROM_OFFSET_HALF_16X   (FONTROM_OFFSET_HALF_14X + FONTROM_SIZE_HALF_14)
#define FONTROM_OFFSET_HALF_12    (FONTROM_OFFSET_HALF_16X + FONTROM_SIZE_HALF_16)
#define FONTROM_OFFSET_HALF_14    (FONTROM_OFFSET_HALF_12  + FONTROM_SIZE_HALF_12)
#define FONTROM_OFFSET_HALF_16    (FONTROM_OFFSET_HALF_14  + FONTROM_SIZE_HALF_14)
#define FONTROM_OFFSET_MINCHO_12X (FONTROM_OFFSET_HALF_16  + FONTROM_SIZE_HALF_16)
#define FONTROM_OFFSET_MINCHO_14X (FONTROM_OFFSET_MINCHO_12X + FONTROM_SIZE_FULL_12)
#define FONTROM_OFFSET_MINCHO_16X (FONTROM_OFFSET_MINCHO_14X + FONTROM_SIZE_FULL_14)
#define FONTROM_OFFSET_GOTHIC_12X (FONTROM_OFFSET_MINCHO_16X + FONTROM_SIZE_FULL_16)
#define FONTROM_OFFSET_GOTHIC_14X (FONTROM_OFFSET_GOTHIC_12X + FONTROM_SIZE_FULL_12)
#define FONTROM_OFFSET_GOTHIC_16X (FONTROM_OFFSET_GOTHIC_14X + FONTROM_SIZE_FULL_14)

#define FONTROM_RANGES_SIZE 140


class FontRom {
  public:
    FontRom();
    ~FontRom();
    void select();
    void deselect();
    void begin();
    int8_t getGryph(uint8_t type, uint16_t code, uint8_t *pattern);
    int8_t getHalfGryphWidth(uint8_t type);
  private:
    int32_t getAddress(uint8_t type, uint16_t code);
};
