#include <avr/io.h>

#include "pins.h"

DigitalPin::DigitalPin(volatile uint8_t& port, uint8_t pin)
: port_(&port)
, pin_(pin)
{}

void DigitalPin::init_in() {
  volatile uint8_t *dir_port;
  if (port_ == &PORTB) {
    dir_port = &DDRB;
  } else if (port_ == &PORTC) {
    dir_port = &DDRC;
  } else {
    dir_port = &DDRD;
  }
  *dir_port &= ~_BV(pin_);
  direction_ = IN;
}

void DigitalPin::init_out() {
  volatile uint8_t *dir_port;
  if (port_ == &PORTB) {
    dir_port = &DDRB;
  } else if (port_ == &PORTC) {
    dir_port = &DDRC;
  } else {
    dir_port = &DDRD;
  }
  *dir_port |= _BV(pin_);
  direction_ = OUT;
}

int8_t DigitalPin::set() {
  if (direction_ == IN) {
    return 1;
  }
  *port_ |= _BV(pin_);
  return 0;
}

int8_t DigitalPin::reset() {
  if (direction_ == IN) {
    return 1;
  }
  *port_ &= ~_BV(pin_);
  return 0;
}

bool DigitalPin::get() const {
  return static_cast<bool>(*this);
}

DigitalPin::operator bool() const {
  return (*port_ & _BV(pin_)) >> pin_;
}
