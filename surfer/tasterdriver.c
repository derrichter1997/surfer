/*
 * CFile1.c
 *
 * Created: 18.09.2018 22:25:07
 *  Author: Manuel
 */ 
#include "tasterdriver.h"

void initTasterInput(void){
	sei();
	PORTD |= (1<<PORTD2) | (1<<PORTD3);
	EICRA = 0x00 | (1<<ISC00) | (1<<ISC01) | (1<<ISC10) | (1<<ISC11);
	EIMSK = 0x00 | (1<<INT1) | (1<<INT0);
}

