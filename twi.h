#ifndef TWI_H
#define TWI_H

#define ACK   1
#define NACK  0

void twiInit();
uint8_t twiPut(uint8_t addr, uint8_t size, uint8_t *data);
uint8_t twiGet(uint8_t addr, uint8_t size, uint8_t *data);

#endif
