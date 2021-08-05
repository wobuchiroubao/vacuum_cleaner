#ifndef UART_H
#define UART_H

void uart_init();
void uart_put_byte(uint8_t data);
uint8_t uart_get_byte();
void uart_put(uint8_t size, const uint8_t *data);
void uart_put_str(const char *data);
void uart_get(uint8_t size, uint8_t *data);
void uart_get_str(uint8_t max_size, char *data); // read until '\n'
                // or size == max_size and discard the ending of the string
                // + adds '\0' at the end o the string

#endif
