#include <avr/io.h>
#include <string.h>

#include "adc.h"
#include "pins.h"
#include "uart.h"
#include "twi.h"

using namespace std;

uint8_t get_power() {
  DigitalPin power[3] = {
    DigitalPin(PORTD, 3), DigitalPin(PORTD, 4), DigitalPin(PORTD, 5)
  };
  for (uint8_t i = 0; i < 3; ++i) {
    power[i].init_in();
  }
  return (PORTD >> 3) & 0x07;
}

int main() {
  /* setup */
  uart_init();
  char command[6];
  /* loop*/
  while (1) {
    uart_get_str(6, command);
    if (!strcmp(command, "power")) {
      uint8_t power = get_power();
      switch (power) {
        case 0x01:
          uart_put_str("low\n");
        break;
        case 0x02:
          uart_put_str("medium\n");
        break;
        case 0x04:
          uart_put_str("high\n");
        break;
        default:
          uart_put_byte((power & 0x01) + '0');
          uart_put_byte(((power & 0x02) >> 1) + '0');
          uart_put_byte(((power & 0x04) >> 2) + '0');
          uart_put_byte('\n');
          //uart_put_str("error\n");
      }
    } else {
      uart_put_str("unknown command\n");
    }
  }
}
