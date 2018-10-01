/*
 * UART.c
 *
 * Created: 22.09.2018 16:29:24
 *  Author: Manuel
 */ 
#include "UART.h"

#define fOSC 16000000
#define UART_BAUDRATE 9600

void init_UART(void){
	UBRR0L = (fOSC/(16*UART_BAUDRATE))-1;
	UBRR0H = (((fOSC/(16*UART_BAUDRATE))-1)>>8);
	UCSR0C = 0x00 | (1<<UPM01) | (1<<UCSZ00) | (1<<UCSZ01); //Even Parity, 8Bit
	UCSR0B = 0x00 | (1<<RXEN0) | (1<TXEN0) | (1<<RXCIE0) | (1<<TXCIE0); //Receiver & Transmiter enable, UART RX/TX ISR enable
}


void UART_TRANSMIT(int8_t * data, struct fifo fifo_uart){
	if ( !( UCSR0A & (1<<UDRE0))){ //UART am werkeln 
		if((fifo_uart.read+1)%10 == fifo_uart.write){	//fifo_uart voll
			while ( !( UCSR0A & (1<<UDRE0)));
			UDR0 = *data;	
		}
		else{
			fifo_uart.stk[fifo_uart.write] = *data;
			fifo_uart.write = (fifo_uart.write +1)%10;	
		}
	}
	else{
		UDR0 = *data;
	}
}