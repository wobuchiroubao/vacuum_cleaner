#include <avr/io.h>

#include "adc.h"

void ADCInit() {
  // Select Vref=AVcc
  ADMUX |= _BV(REFS0);
  //set prescaller to 128 and enable ADC -> 16000000/128=125kHz
  ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADEN);
}

uint16_t getAnalog(uint8_t pin) {
 //select ADC channel with safety mask
 ADMUX = (ADMUX & 0xF0) | (pin & 0x0F);
 //single conversion mode
 ADCSRA |= _BV(ADSC);
 // wait until ADC conversion is complete
 while (ADCSRA & _BV(ADSC)) {}
 return ADC;
}
