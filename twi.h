#ifndef TWI_H
#define TWI_H

#define ACK   1
#define NACK  0

void twi_init();
uint8_t twi_put(uint8_t addr, uint8_t size, const uint8_t *data);
uint8_t twi_get(uint8_t addr, uint8_t size, uint8_t *data);

#endif
