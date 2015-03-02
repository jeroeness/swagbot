MCU   = atmega32

## Main source
MAIN_SOURCE = main.c

## Other sources seperated by a SPACE
OTHER_SOURCES = motor.c


## Defined programs / locations
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude

CFLAGS= -mmcu=$(MCU) -Os  -Wall -std=gnu99

## Lump target and extra source files together

SRC = $(MAIN_SOURCE) $(OTHER_SOURCES)

OBJS = $(SRC:.c=.o)

TARGET = $(strip $(basename $(MAIN_SOURCE)))

## List of all header files
HEADERS = $(SRC:.c=.h) 

## For every .c file, compile an .o object file
OBJS = $(SRC:.c=.o) 
HEXS = $(MAIN_SOURCE:.c=.hex)

$(TARGET).hex: $(TARGET).elf

%.hex: %.elf
	$(OBJCOPY) -R .eeprom -O ihex $< $@
	rm -f *.elf *.o

%.elf: $(SRC)
	$(CC) $(CFLAGS) $(SRC) --output $@ 

$(OBJS): func_defs.h

clean:
	rm -f $(TARGET).elf $(TARGET).hex $(TARGET).obj \
	$(TARGET).o $(TARGET).d $(TARGET).eep $(TARGET).lst \
	$(TARGET).lss $(TARGET).sym $(TARGET).map $(TARGET)~ \
	$(TARGET).eeprom

squeaky_clean:
	rm -f *.elf *.hex *.obj *.o *.d *.eep *.lst *.lss *.sym *.map *~
