/*
 * USART_Routines.c
 *
 * Created: 06.09.2016 13:11:53
 *  Author: Manuel
 */ 

#include "USART_Routines.h"

/************************************************************************/
/* void usart_init(void);												*/
/* Initialisierung des USART0 Interfaces                                */
/************************************************************************/

void usart0_init(void)
{

	//Datenformat (8 Datenbits, Even Parity, 2 Stopbits), asyncron (UMSEL = 0)
	UCSR0C = (1<<USBS0)			//2 x Stopbit
	|(3<<UCSZ00)|(1<<UPM01);	    //8 Datenbit

	//Baud Rate anpassen
	UBRR0H =(uint8_t)(UBRR>>8);
	UBRR0L =(uint8_t) UBRR;

	//USART aktivieren
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);	//Freigabe Receiver, Transmitter sowie Receiverint und Transmitint
}

/************************************************************************/
/* void usart_transmit(unsigned char data);                             */
/* Sendet 8 Bit (unsigned char data) über USART0 an den Empfänger		*/
/* Liefert eine 1 wenn erfolgreich und eine 0 wenn nicht erfolgreich	*/
/************************************************************************/

char usart0_transmit(unsigned char data)
{
	//auf die entleerung des Datenregisters warten...
	if (!(UCSR0A & (1<<UDRE0))){
		return Buffer0In(data);
	}
	else{
		UDR0 = data;
		return 1;
	}
}

/************************************************************************/
/* void usart_init(void);												*/
/* Initialisierung des USART1 Interfaces                                */
/************************************************************************/

void usart1_init(void)
{

	//Datenformat (8 Datenbits, Even parity , 2 Stopbits), asyncron (UMSEL = 0)
	UCSR1C = (1<<USBS1)			//2 x Stopbit
	|(3<<UCSZ10)|(1<<UPM11);	    //8 Datenbit

	//Baud Rate anpassen
	UBRR1H =(uint8_t)(UBRR>>8);
	UBRR1L =(uint8_t) UBRR;

	//USART aktivieren
	UCSR1B = (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1)|(1<<TXCIE1);	//Freigabe Receiver, Transmitter sowie Receiverint und Transmitint
}

/************************************************************************/
/* void usart_transmit(unsigned char data);                             */
/* Sendet 8 Bit (unsigned char data) über USART1 an den Empfänger		*/
/************************************************************************/

char usart1_transmit(unsigned char data)
{

	//auf die entleerung des Datenregisters warten...
	if (!(UCSR1A & (1<<UDRE1))){
		return Buffer1In(data);
	}
	else{
		UDR1 = data;
		return 1;
	}
}

/************************************************************************/
/* void usart0_transmit_string(const char *data);						*/
/* Sendet einen beliebig langen String an den Computer					*/
/************************************************************************/

void usart0_transmit_string(const char *data){
	for(int i = 0; i<strlen(data); i++)
		usart0_transmit(data[i]);
	usart0_transmit(0x0A); //LF für einen Zeilenumbruch
}

/************************************************************************/
/* void sendvalue(int number);                                          */
/* Sendet den Wert einer Variable in einer lesbaren Form an den Computer*/
/************************************************************************/

void sendvalue(int number){
	int digit[]={0,0,0,0};
	int count = 0;
	while(number>0){
		digit[count] = number %10;
		number /= 10;
		count ++;
	}
	while(count!=-1){
		usart0_transmit((char) (digit[count]+'0'));
		count--;
	}
	usart0_transmit(0x0A); //LF für einen Zeilenumbruch
}