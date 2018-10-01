/*
 * surfer.c
 *
 * Created: 14.09.2018 15:06:48
 *  Author: Manuel
 */ 
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "segdriver.h"
#include "tasterdriver.h"
#include "USART_Routines.h"
#include <util/delay.h>
#include "StatusREG.h"

#define F_CPU 16000000UL 

uint8_t StatusREG = 0x00;

uint8_t TIMER1_COUNTER = 0;
uint8_t INTERFACE_7SEG_SEGNR = 0;
uint8_t INTERFACE_7SEG_VALUES [4]= {0,0,0,0};
uint8_t INTERFACE_7SEG_DOTPOS = 1;
uint8_t UARTBUFFER = 0;
uint8_t msbyte = 0;
uint8_t msbytecopy = 0;
uint8_t lsbyte = 0;
uint8_t fifo_buffer = 0;
uint8_t sec = 0, min = 0, h = 0;


int main(void)
{
	usart0_init();
	
	i2c_init();
	init7seg();
	initTasterInput();
	i2c_start(0b11011110);	//Adresse + write
	i2c_write(0x07);		//adresse SREG 
	i2c_write(0x10);			//Wert Uhr aktivieren
	i2c_stop();
	i2c_start(0b11011110);	//Adresse + write
	i2c_write(0x00);		//adresse sekunden
	i2c_write(30);			//Wert sekunden
	i2c_stop();
	i2c_start(0b11011110);	//Adresse + write
	i2c_write(0x01);		//adresse minuten
	i2c_write(30);		//Wert Minuten
	i2c_stop();
	i2c_start(0b11011110);	//Adresse + write
	i2c_write(0x02);		//adresse Stunden
	i2c_write(14);		//Wert Stunden
	i2c_stop();
	
	//sreg clock init bit setzen
	//über die Ext Interrupts die Uhrzeit setzen
	//mit der letzten Bestätigung die Uhrzeit übertragen und das sreg init bit deaktivieren
	//clock activ bit setzen
	// im sekunden takt uhrzeit abfragen 
	 
    while(1)
    {
		_delay_ms(20000);
		usart0_transmit(sec);
		usart0_transmit(min);
		usart0_transmit(h);

    }
}


ISR(TIMER1_COMPA_vect){	//alle 1000ms
	
	i2c_gettemp(&msbyte, &lsbyte);
	msbytecopy = msbyte;
	msbyte = ((msbyte<<1) | (lsbyte>>7)); //das letzte bit um 7 nach rechts shiften //Dateninhalt um 1 nach links shiften
	if(((1<<7)&msbytecopy)==128){	//negative Temperatur (MSB = 1)
		StatusREG |= (1<<NTV);
		msbyte = (~msbyte)+1;
	}
	else{
		StatusREG &= ~(1<<NTV);
	}
	for(int i = 0;i<4; i++){
		INTERFACE_7SEG_VALUES[i] = numspliter7seg(msbyte,i,StatusREG);
	}
	//************************************ Uhr I2C Übertragung ****************************************
	i2c_start(0b11011110);	//Adresse + write
	i2c_write(0x00);		//adresse sekunden
	i2c_start(0b11011111);	//Adresse + read
	sec = i2c_read_ack();
	min = i2c_read_ack();
	h = i2c_read_nack();
	i2c_stop();
	
		
}

ISR(TIMER0_COMPA_vect){
	write7seg(INTERFACE_7SEG_VALUES[INTERFACE_7SEG_SEGNR],INTERFACE_7SEG_SEGNR,INTERFACE_7SEG_DOTPOS);
	INTERFACE_7SEG_SEGNR = (INTERFACE_7SEG_SEGNR+1)%4;
}

ISR(INT0_vect){
	INTERFACE_7SEG_VALUES[0]++;
	if(INTERFACE_7SEG_VALUES[0]==10)
		INTERFACE_7SEG_VALUES[0]=0;
}

ISR(INT1_vect){
	if(INTERFACE_7SEG_VALUES[0]==0)
		INTERFACE_7SEG_VALUES[0]=10;
	INTERFACE_7SEG_VALUES[0]--;
}

ISR(USART0_RX_vect){
	//msbyte = UDR0;

}
ISR(USART0_TX_vect){
	if(Buffer0Out(&fifo_buffer)){	//Buffer abarbeiten
		UDR0 = fifo_buffer;
	}
}