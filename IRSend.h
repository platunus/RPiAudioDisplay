#include <Arduino.h>

#define ENABLE_SEND_PWM_BY_TIMER   TCNT1 = 0; (TCCR1A |= _BV(COM1A1))
#define DISABLE_SEND_PWM_BY_TIMER  (TCCR1A &= ~(_BV(COM1A1)))
#define IR_SEND_DUTY_CYCLE 30

#define NEC_BITS                32
#define NEC_UNIT                560

#define NEC_HEADER_MARK         (16 * NEC_UNIT) // 9000
#define NEC_HEADER_SPACE        (8 * NEC_UNIT)  // 4500 

#define NEC_BIT_MARK            NEC_UNIT
#define NEC_ONE_SPACE           (3 * NEC_UNIT)  // 1690
#define NEC_ZERO_SPACE          NEC_UNIT

#define IRSEND_VOL_UP     0xFD0203D2
#define IRSEND_VOL_DOWN   0xFC0303D2
#define IRSEND_MUTE       0xFA0503D2

#define IRSEND_FREQ       38

class IRSend {
  public:
    IRSend();
    ~IRSend();
    void begin(uint8_t carrierFreqKHz);
    void send(uint32_t data);
};
