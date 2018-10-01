/*
 * USART_Routines.h
 *
 * Created: 06.09.2016 13:11:09
 *  Author: Manuel
 */ 

/************************************************************************/
/* Allgemeines:                                                         */
/* Diese Bibliothek enthält USART Routinen für die Kommunikation		*/
/* zwischen dem PC und dem Luftschiff (Entwicklungsgründe) als auch für */
/* die Kommunikation zwischen Raspberry Pi und Mikrocontroller.			*/
/* Beide Sendeverfahren	wurden Mittels Polling realisiert, während der 	*/
/* Empfang mithilfe von Interrupt Routinen gelöst wurde.				*/
/************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include <string.h>
#include "Ringbuffer.h"

#ifndef USART_ROUTINES_H_
#define USART_ROUTINES_H_

/************************************************************************/
/* Definitionen für beide USART Interfaces								*/
/* Fosc: Clock Frequenz in Hz, Baud: Übertragungsgeschwindigkeit in     */
/* Bit / Sekunde, UBRR berechnete Baudrate für das Baudrateregister		*/
/************************************************************************/

#define Fosc  16000000UL
#define Baud  9600
#define quot  Fosc/Baud
#define UBRR  (Fosc/(16UL*Baud)-1)

/************************************************************************/
/* void usart_init(void);												*/
/* Initialisierung des USART0 Interfaces                                */
/************************************************************************/

void usart0_init(void);

/************************************************************************/
/* void usart_transmit(unsigned char data);                             */
/* Sendet 8 Bit (unsigned char data) über USART0 an den Empfänger		*/
/************************************************************************/

char usart0_transmit(unsigned char data);

/************************************************************************/
/* void usart0_transmit_string(const char *data);						*/
/* Sendet einen beliebig langen String an den Computer					*/
/************************************************************************/

void usart0_transmit_string(const char *data);

/************************************************************************/
/* void sendvalue(int number);                                          */
/* Sendet den Wert einer Variable in einer lesbaren Form an den Computer*/
/************************************************************************/

void sendvalue(int number);

/************************************************************************/
/* void usart_init(void);												*/
/* Initialisierung des USART1 Interfaces                                */
/************************************************************************/

void usart1_init(void);

/************************************************************************/
/* void usart_transmit(unsigned char data);                             */
/* Sendet 8 Bit (unsigned char data) über USART1 an den Empfänger		*/
/************************************************************************/

char usart1_transmit(unsigned char data);

#endif /* USART_ROUTINES_H_ */