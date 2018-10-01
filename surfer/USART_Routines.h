/*
 * USART_Routines.h
 *
 * Created: 06.09.2016 13:11:09
 *  Author: Manuel
 */ 

/************************************************************************/
/* Allgemeines:                                                         */
/* Diese Bibliothek enth�lt USART Routinen f�r die Kommunikation		*/
/* zwischen dem PC und dem Luftschiff (Entwicklungsgr�nde) als auch f�r */
/* die Kommunikation zwischen Raspberry Pi und Mikrocontroller.			*/
/* Beide Sendeverfahren	wurden Mittels Polling realisiert, w�hrend der 	*/
/* Empfang mithilfe von Interrupt Routinen gel�st wurde.				*/
/************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include <string.h>
#include "Ringbuffer.h"

#ifndef USART_ROUTINES_H_
#define USART_ROUTINES_H_

/************************************************************************/
/* Definitionen f�r beide USART Interfaces								*/
/* Fosc: Clock Frequenz in Hz, Baud: �bertragungsgeschwindigkeit in     */
/* Bit / Sekunde, UBRR berechnete Baudrate f�r das Baudrateregister		*/
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
/* Sendet 8 Bit (unsigned char data) �ber USART0 an den Empf�nger		*/
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
/* Sendet 8 Bit (unsigned char data) �ber USART1 an den Empf�nger		*/
/************************************************************************/

char usart1_transmit(unsigned char data);

#endif /* USART_ROUTINES_H_ */