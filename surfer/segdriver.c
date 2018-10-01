/*
 * _7segdriver.c
 *
 * Created: 14.09.2018 18:56:13
 *  Author: Manuel
 */ 
#include "segdriver.h"


void init7seg(void){
	DDRA = 0xFE;
	DDRB = 0x0B;
	sei();
	OCR1A = 0xF424; //31250 OCR Register -> 1000ms bei Prescaler 256 
	TIMSK1 = 0x00 | (1<<OCIE1A);
	TCCR1B = 0x00 | (1<<WGM12) | (1<<CS12);
	//
	OCR0A = 250;	//OCR für 2 ms
	TIMSK0 |= (1<<OCIE0A);	//OCI enable
	TCCR0A |= (1<<WGM01);	//CTC
	TCCR0B |= (1<<CS01) | (1<<CS00);	//prescaler 64
	 
	
}

void write7seg(uint8_t value, uint8_t segno, uint8_t dotpos){
	if(segno<4){
		PORTB = segno;
		switch(value){
			case 0: PORTA = 0x00 | (1<<PORTA2) | (1<<PORTA3) | (1<<PORTA4) | (1<<PORTA5) | (1<<PORTA6) | (1<<PORTA7); 
			break;
			case 1: PORTA = 0x00 | (1<<PORTA3) | (1<<PORTA6); 
			break; 
			case 2: PORTA = 0x00 | (1<<PORTA1) | (1<<PORTA2) | (1<<PORTA3) | (1<<PORTA5) |  (1<<PORTA7);
			break;
			case 3: PORTA = 0x00 | (1<<PORTA1) | (1<<PORTA2) | (1<<PORTA3) | (1<<PORTA6) |  (1<<PORTA7);
			break;
			case 4: PORTA = 0x00 | (1<<PORTA1) | (1<<PORTA3) | (1<<PORTA4) | (1<<PORTA6);
			break;
			case 5: PORTA = 0x00 | (1<<PORTA1) | (1<<PORTA2) | (1<<PORTA4) | (1<<PORTA6) | (1<<PORTA7); 
			break;
			case 6: PORTA = 0x00 | (1<<PORTA1) | (1<<PORTA2) | (1<<PORTA4) | (1<<PORTA5) | (1<<PORTA6) | (1<<PORTA7); 
			break;
			case 7: PORTA = 0x00 | (1<<PORTA2) | (1<<PORTA3) | (1<<PORTA4) | (1<<PORTA6); 
			break;
			case 8: PORTA = 0x00 | (1<<PORTA1) | (1<<PORTA2) | (1<<PORTA3) | (1<<PORTA4) | (1<<PORTA5) | (1<<PORTA6) | (1<<PORTA7); 
			break;
			case 9: PORTA = 0x00 | (1<<PORTA1) | (1<<PORTA2) | (1<<PORTA3) | (1<<PORTA4) | (1<<PORTA6) | (1<<PORTA7); 
			break;
			case 10: PORTA = 0x00 | (1<<PORTA2)  | (1<<PORTA4) | (1<<PORTA5) | (1<<PORTA7); // (C) Celsius Zeichen
			break;
			case 11: PORTA = 0x00 | (1<<PORTA1);	// Minus
			break;
			default: PORTA = 0x00;					//Disabled 
			break;
		}	
	}
	if(dotpos == segno)
		PORTB |= (1<<PORTB3);
	else
		PORTB &= ~(1<<PORTB3);
}

uint8_t numspliter7seg(uint8_t value, uint8_t charno, uint8_t StatusREG){
	value = value/2;
	switch(charno){
		case 0: value = 10;	//C Stelle 0 (rechts)
		break;
		case 1: value = value %10;	//Wert Stelle 1
		break;
		
		case 2: 
		if(((value/100) == 0) && (((value/10) %10) ==0)){	//falls die 3 und 4 Stelle 0 sand 
			value = 12;
		}
		else{
			value = (value/10) %10;	//Wert Stelle 2	
		}
		
		break;
		case 3: 
		value = value/100;
		if((StatusREG & (1<<0))==0x01){	//negative Temp
			value = 11;
		}
		if (value == 0){	//falls erste zahl = 0 -> stelle wird leer gelassen
			value = 12;
		}
		break;
		default: value = 12; //ungülitg
		break;
	}
	return value;
}
