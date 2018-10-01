/*
 * UART.h
 *
 * Created: 22.09.2018 16:30:12
 *  Author: Manuel
 */ 


#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

struct FIFO_Speicher
{
	uint8_t stk[10];
	uint8_t write;
	uint8_t read;
};
typedef struct FIFO_Speicher fifo;


void init_UART(void);
void UART_TRANSMIT(uint8_t * data, struct fifo fifo_uart);



#endif /* UART_H_ */