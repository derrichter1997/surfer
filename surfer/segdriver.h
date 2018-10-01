/*
 * _7segdriver.h
 *
 * Created: 14.09.2018 18:49:09
 *  Author: Manuel
 */ 


#ifndef SEGDRIVER_H_
#define SEGDRIVER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void init7seg(void);

void write7seg(uint8_t value, uint8_t segno, uint8_t dotpos);

uint8_t numspliter7seg(uint8_t value, uint8_t charno, uint8_t StatusREG);	//für den Temperatursensor 


#endif /* SEGDRIVER_H_ */