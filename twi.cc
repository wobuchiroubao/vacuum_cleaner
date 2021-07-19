#include <avr/io.h>

#include "twi.h"

void twi_init() {
  TWBR = 0x0C; // set SCL to 400kHz
  TWSR = 0x00;
  TWCR &= ~_BV(TWIE); // disable TWINT interrupts
  //__enable_interrupt(); // enable global interrupt
  TWCR = _BV(TWEN); // enable TWI
}

static inline void _twi_start() {
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
  while (!(TWCR & _BV(TWINT))) {}
}

static inline void _twi_stop() {
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

static inline uint8_t _twi_transmit_byte(uint8_t byte) {
  TWDR = byte;
  TWCR = _BV(TWINT) | _BV(TWEN);
  while (!(TWCR & _BV(TWINT))) {}
  return TWSR & 0xF8; // (N)ACK
}

static inline uint8_t _twi_receive_byte(uint8_t ack) {
  TWCR = _BV(TWINT) | _BV(TWEN) | (ack << TWEA);
  while (!(TWCR & _BV(TWINT))) {}
  return TWDR;
}

uint8_t twi_put(uint8_t addr, uint8_t size, const uint8_t *data) {
  _twi_start();
  if (!_twi_transmit_byte(addr << 1)) {
    return 0; // mr_sla_nack
  }
  for (uint8_t i = 0; i < size; ++i) {
    if (!_twi_transmit_byte(*(data + i))) {
      return 0; // mr_sla_nack
    }
  }
  _twi_stop();
  return 1; // mr_sla_ack
}

uint8_t twi_get(uint8_t addr, uint8_t size, uint8_t *data) {
  _twi_start();
  if (!_twi_transmit_byte((addr << 1) | 0x01)) {
    return 0; // mr_sla_nack
  }
  for (uint8_t i = 0; i + 1 < size; ++i) {
    data[i] = _twi_receive_byte(ACK);
  }
  data[size - 1] = _twi_receive_byte(NACK);
  _twi_stop();
  return 1; // mr_sla_ack
}
