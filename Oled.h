#include <Arduino.h>

#define OLED_DDR_DATA     DDRD
#define OLED_PORT_DATA    PORTD
#define OLED_PIN_DATA     PIND

#define OLED_DDR_CONTROL  DDRC
#define OLED_PORT_CONTROL PORTC
#define OLED_PIN_CONTROL  PINC

#define OLED_BIT_D0       0
#define OLED_BIT_D1       1
#define OLED_BIT_D2       2
#define OLED_BIT_D3       3
#define OLED_BIT_D4       4
#define OLED_BIT_D5       5
#define OLED_BIT_D6       6
#define OLED_BIT_D7       7
#define OLED_BIT_BUSY     OLED_BIT_D7

#define OLED_BIT_EN       2
#define OLED_BIT_RW       1
#define OLED_BIT_RS       0

#define OLED_X_SIZE       100
#define OLED_Y_SIZE       2

class Oled {
  private:
    void send(uint8_t data);
    void wait();
    void setGraphicCursor(uint8_t x, uint8_t y);
    uint8_t offset = 0;
  public:
    Oled();
    ~Oled();
    void displayOn();
    void displayOff();
    void displayClear();
    void wakeUp();
    void sleep();
    void begin();
    void draw(uint8_t x, uint8_t y, uint8_t *data, uint8_t len);
    void test();
};
