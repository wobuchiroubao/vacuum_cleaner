#include <avr/io.h>

#include "ports.h"

#define set(pin) _set(pin)
#define _set(port_no, pin_no) {                  \
  PORT##port_no |= _BV(pin_no);                  \
}

#define reset(pin) _reset(pin)
#define _reset(port_no, pin_no) {                \
  PORT##port_no &= ~_BV(pin_no);                 \
}

#define getDigital(pin) _getDigital(pin)
#define _getDigital(port_no, pin_no)             \
  (((uint8_t) (PORT##port_no & _BV(pin_no))) >> pin_no)
