#include "Oled.h"
#include "FontRom.h"

//#define KANJI_OLED_MAX_STRING_SIZE 128
#define KANJI_OLED_MAX_STRING_SIZE 250
#define KANJI_OLED_PADDING_SIZE 6
#define KANJI_OLED_PAUSE 1000UL
#define KANJI_OLED_MAX_INTERVAL 5000UL

class KanjiOled {
  private:
    Oled oled;
    FontRom rom;
    uint8_t msg[KANJI_OLED_MAX_STRING_SIZE + KANJI_OLED_PADDING_SIZE];
    uint8_t pos_msg;
    uint16_t len_msg;
    uint8_t font_type;
    uint8_t gryph[FONTROM_GRYPH_MAX_SIZE];
    uint8_t width_gryph;
    uint8_t pos_gryph;
    uint8_t vram[OLED_Y_SIZE][OLED_X_SIZE];
    uint8_t width_window;
    uint8_t pos_vram;
    uint32_t prev;
    uint16_t interval;
    bool suspend;
    bool overflow;
    void writeVram(bool first);
  public:
    KanjiOled();
    ~KanjiOled();
    void begin();
    int8_t start(uint8_t *message, uint8_t len, uint8_t font_type, uint16_t interval);
    void scroll();
    void pause();
    void resume();
    void displayClear();
    void displayOn();
    void displayOff();
    void sleep();
    void wakeUp();
};
