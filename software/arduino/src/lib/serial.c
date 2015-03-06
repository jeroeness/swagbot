
#ifndef BAUD
#define BAUD 9600
#endif

#include <Arduino.h>

#include <avr/io.h>
#include <stdio.h>
//#include <USART.h>
#include <util/setbaud.h>
#include "serial.h"
#include <util/delay.h>

#ifndef BAUD_PRESCALLER
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 16UL))) - 1)
#endif

//char wait_until_bit_is_set(char sfr,char bit){
//while (bit_is_clear(sfr, bit)){
//_delay_ms(10);
//}
//}
void serialBegin(){
    UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
    UBRR0L = (uint8_t)(BAUD_PRESCALLER);
    UCSR0B |= (1 << TXEN0 | 1 << RXEN0); //Enable RX and TX
    UCSR0C |= (1<<USBS0 | 1 << UCSZ01) | (1 << UCSZ00); //1 stopbit(USBS0) 8 databits(UCSZ00 & UCSZ01)
}

void serialEnd(){
    UCSR0A &= ~(1 << U2X0);
    UCSR0B &= ~(1 << TXEN0 | 1 << RXEN0);
    UCSR0C &= ~(1<<USBS0 | 1 << UCSZ01) | (1 << UCSZ00);
}

//TODO <for later change the code for serialread and write to a interupt. (224 datashee) >
char serialRead(void){
  loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}
void serialWrite(char *c){
char *test = "hallo";
//serialWriteCharacter(test);
}

void serialWriteCharacter(char c){
switch(c){
case '\r': Serial.print("\n\r");
         break;
default:
 loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
 UDR0 = c;
}



}
