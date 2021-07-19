#ifndef UART_H
#define UART_H

void uart_init();
void uart_put_byte(uint8_t data);
uint8_t uart_get_byte();
void uart_put(uint8_t size, const uint8_t *data);
void uart_get(uint8_t size, uint8_t *data);

#endif
