# Define those in project:
#
F_CPU ?= 8000000
MCU ?= atmega328p
NAME ?= main
OBJS ?= pins.cc adc.cc twi.cc uart.cc main.cc

DUDEMCU ?= $(MCU)
DUDEPORT ?= /dev/ttyACM0
DUDEPROGRAMER ?= usbasp

#################

CC = avr-g++
override CFLAGS += -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -Wall -g -std=c++17

#################
all: $(NAME) size

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(NAME).hex: $(NAME)
	avr-objcopy -O ihex -R .eeprom $< $@

flash: $(NAME).hex
	avrdude -V -c $(DUDEPROGRAMER) -p $(DUDEMCU) -P $(DUDEPORT) -U flash:w:$<

readfuse:
	avrdude -V -c $(DUDEPROGRAMER) -p $(DUDEMCU) -P $(DUDEPORT) -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h

size: $(NAME) $(NAME).lst
	avr-size --mcu=${MCU} -C $<

$(NAME).lst: $(NAME)
	avr-objdump -h -S $< > $@

clean:
	rm -rf $(NAME) $(NAME).hex $(NAME).lst
