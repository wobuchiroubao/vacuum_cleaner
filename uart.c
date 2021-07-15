#include <avr/io.h>

#include "uart.h"

void uartInit() {
  // set baudrate in UBRR to 9600
  UBRR0L = (uint8_t) (103 & 0xFF);
  UBRR0H = (uint8_t) (103 >> 8);
	UCSR0A = _BV(U2X0);
  // enable the transmitter and receiver
  UCSR0B |= _BV(RXEN0) | _BV(TXEN0);
}

void uartPutByte(uint8_t data) {
    // wait for transmit buffer to be empty
    while(!(UCSR0A & _BV(UDRE0)));
    // load data into transmit register
    UDR0 = data;
}

uint8_t uartGetByte() {
    // wait for data
    while(!(UCSR0A & _BV(RXC0)));
    // return data
    return UDR0;
}

void uartPut(uint8_t size, uint8_t *data) {
  for (uint8_t i = 0; i < size; ++i) {
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = *(data + i);
  }
}

void uartGet(uint8_t size, uint8_t *data) {
  for (uint8_t i = 0; i < size; ++i) {
    while(!(UCSR0A & _BV(RXC0)));
    *(data + i) = UDR0;
  }
}
