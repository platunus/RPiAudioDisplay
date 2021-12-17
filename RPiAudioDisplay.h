#include "SendOnlySoftwareSerial.h"

//#define DEBUG 1

#define I2C_OPCODE_START         0x00
#define I2C_OPCODE_PAUSE         0x10
#define I2C_OPCODE_RESUME        0x11
#define I2C_OPCODE_DISPLAY_CLEAR 0x12
#define I2C_OPCODE_DISPLAY_ON    0x13
#define I2C_OPCODE_DISPLAY_OFF   0x14
#define I2C_OPCODE_SLEEP         0x15
#define I2C_OPCODE_WAKEUP        0x16
#define I2C_OPCODE_VOL_UP        0x20
#define I2C_OPCODE_VOL_DOWN      0x21
#define I2C_OPCODE_MUTE          0x22

#define sbi(PORT,BIT)   PORT |= _BV(BIT)
#define cbi(PORT,BIT)   PORT &=~_BV(BIT)

#ifdef DEBUG
extern SendOnlySoftwareSerial mySerial;
#endif
