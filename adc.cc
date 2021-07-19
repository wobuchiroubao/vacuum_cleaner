#include <avr/io.h>

#include "adc.h"

AnalogPin::AnalogPin(uint8_t pin)
: pin_(pin)
{}

uint16_t AnalogPin::get() const {
 //select Vref=AVcc + ADC channel with safety mask
 ADMUX = 0x40 | (pin_ & 0x0F);
 //single conversion mode
 ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
 // wait until ADC conversion is complete
 while (ADCSRA & _BV(ADSC)) {}
 return ADC;
}
