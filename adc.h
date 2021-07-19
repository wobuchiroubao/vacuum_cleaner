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

class AnalogPin {
public:
  AnalogPin(uint8_t pin);
  uint16_t get() const;
  operator uint16_t() const;
private:
  uint8_t pin_;
};

#endif
