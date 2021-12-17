#include "RPiAudioDisplay.h"
#include "IRSend.h"

IRSend::IRSend() {
}

IRSend::~IRSend() {
}

void IRSend::begin(uint8_t carrierFreqKHz) {
  const uint16_t pwmval = 4000UL / carrierFreqKHz; // 105 for 38 kHz @8 MHz clock
  TCCR1A = _BV(WGM11); // PWM, Phase Correct, Top is ICR1
  TCCR1B = _BV(WGM13) | _BV(CS10);// CS10 -> no prescaling
//  ICR1 = pwmval - 1;
//  OCR1A = ((pwmval * IR_SEND_DUTY_CYCLE) / 100) - 1;
  ICR1 = pwmval;
  OCR1A = ((pwmval * IR_SEND_DUTY_CYCLE) / 100);
  TCNT1 = 0;
  DDRB |= _BV(1);
  PORTB &= ~(_BV(1));
}

void IRSend::send(uint32_t data) {
  ENABLE_SEND_PWM_BY_TIMER;
  delayMicroseconds(NEC_HEADER_MARK);
  DISABLE_SEND_PWM_BY_TIMER;
  delayMicroseconds(NEC_HEADER_SPACE);

  uint8_t b;
  for (uint8_t i = 0; i < NEC_BITS; i++) {
    b = data & 0x01;
    ENABLE_SEND_PWM_BY_TIMER;
    delayMicroseconds(NEC_BIT_MARK);
    DISABLE_SEND_PWM_BY_TIMER;
    if (b == 0) {
      delayMicroseconds(NEC_ZERO_SPACE);
    } else {
      delayMicroseconds(NEC_ONE_SPACE);
    }
    data = data >> 1;
  }

  ENABLE_SEND_PWM_BY_TIMER;
  delayMicroseconds(NEC_BIT_MARK);
  DISABLE_SEND_PWM_BY_TIMER;  
  PORTB &= ~(_BV(1));
}
