MAIN_SOURCE = main.c
OTHER_SOURCES = 
TARGET = sintest.exe

CC = gcc

CFLAGS = -std=c99 -lm

SRC = $(MAIN_SOURCE) $(OTHER_SOURCES)

HEADERS = $(wildcard *.h)

OBJS = $(SRC:.c=.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJS) : $(HEADERS)

clean : 
	rm *.o
