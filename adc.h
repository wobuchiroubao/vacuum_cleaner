#ifndef ADC_H
#define ADC_H

#define ADC0  0
#define ADC1  1
#define ADC2  2
#define ADC3  3
#define ADC4  4
#define ADC5  5
#define ADC6  6
#define ADC7  7

void adcInit();
uint16_t getAnalog(uint8_t pin);

#endif
