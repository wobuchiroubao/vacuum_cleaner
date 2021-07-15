#include <avr/io.h>

#include "twi.h"

void twiInit() {
  TWBR = 0x0C; // set SCL to 400kHz
  TWSR = 0x00;
  TWCR &= ~_BV(TWIE); // disable TWINT interrupts
  //__enable_interrupt(); // enable global interrupt
  TWCR = _BV(TWEN); // enable TWI
}

inline void _twiStart() {
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
  while (!(TWCR & _BV(TWINT))) {}
}

inline void _twiStop() {
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

inline uint8_t _twiTransmitByte(uint8_t byte) {
  TWDR = byte;
  TWCR = _BV(TWINT) | _BV(TWEN);
  while (!(TWCR & _BV(TWINT))) {}
  return TWSR & 0xF8; // (N)ACK
}

inline uint8_t _twiReceiveByte(uint8_t ack) {
  TWCR = _BV(TWINT) | _BV(TWEN) | (ack << TWEA);
  while (!(TWCR & _BV(TWINT))) {}
  return TWDR;
}

uint8_t twiPut(uint8_t addr, uint8_t size, uint8_t *data) {
  _twiStart();
  if (!_twiTransmitByte(addr << 1)) {
    return 0; // mr_sla_nack
  }
  for (uint8_t i = 0; i < size; ++i) {
    if (!_twiTransmitByte(*(data + i))) {
      return 0; // mr_sla_nack
    }
  }
  _twiStop();
  return 1; // mr_sla_ack
}

uint8_t twiGet(uint8_t addr, uint8_t size, uint8_t *data) {
  _twiStart();
  if (!_twiTransmitByte((addr << 1) | 0x01)) {
    return 0; // mr_sla_nack
  }
  for (uint8_t i = 0; i + 1 < size; ++i) {
    *(data + i) = _twiReceiveByte(ACK);
  }
  *(data + (size - 1)) = _twiReceiveByte(NACK);
  _twiStop();
  return 1; // mr_sla_ack
}
