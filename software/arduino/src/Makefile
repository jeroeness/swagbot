MCU   = atmega2560

## Main source
MAIN_SOURCE = main.c


## Defined programs / locations
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude

CFLAGS= -mmcu=$(MCU) -Os  -Wall -x c++ -DF_CPU16000000L -I ./modules -I ./lib

## All the source files
SRC = $(MAIN_SOURCE) $(wildcard modules/*.c) $(wildcard modules/new_automatic_mode/*.c) $(wildcard lib/*.c)

## All header files
HEADERS = $(wildcard modules/*.h) $(wildcard modules/new_automatic_mode/*.h) $(wildcard lib/*.h)

OBJS = $(SRC:.c=.o)

TARGET = $(strip $(basename $(MAIN_SOURCE)))


## For every .c file, compile an .o object file
OBJS = $(SRC:.c=.o) 
HEXS = $(MAIN_SOURCE:.c=.hex)

$(TARGET).hex: $(TARGET).elf

%.hex: %.elf
	$(OBJCOPY) -R .eeprom -O ihex $< $@
	rm -f *.elf *.o

%.elf: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -lc -lm --output $@

$(OBJS): $(HEADERS)

clean:
	rm -f $(TARGET).elf $(TARGET).hex $(TARGET).obj \
	$(TARGET).o $(TARGET).d $(TARGET).eep $(TARGET).lst \
	$(TARGET).lss $(TARGET).sym $(TARGET).map $(TARGET)~ \
	$(TARGET).eeprom

squeaky_clean:
	rm -f *.elf *.hex *.obj *.o *.d *.eep *.lst *.lss *.sym *.map *~

test:
	echo "SRC: $(SRC)"
	echo "HEADERS: $(HEADERS)"
	
git:
	make clean
	make
	git add -f ./$(TARGET).hex
	git commit -m 'new hex'
	git pull
	git push