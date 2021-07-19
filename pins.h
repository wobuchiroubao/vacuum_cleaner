#ifndef PINS_H
#define PINS_H

enum {
  IN,
  OUT
};

class DigitalPin {
public:
  DigitalPin(uint8_t& port, uint8_t pin);
  void init_in();
  void init_out();
  int8_t set();
  int8_t reset();
  bool get() const;
  operator bool() const;
private:
  volatile uint8_t *port_;
  uint8_t pin_;
  bool direction_;
};

#endif
