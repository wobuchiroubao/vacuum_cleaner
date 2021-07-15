#ifndef UART_H
#define UART_H

void uartInit();
void uartPutByte(uint8_t data);
uint8_t uartGetByte();
void uartPut(uint8_t size, uint8_t *data);
void uartGet(uint8_t size, uint8_t *data);

#endif
