/*
 * Ringbuffer.h
 *
 * Created: 09.11.2016 03:21:36
 *  Author: manuelrichter
 *	
*/

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
#include <stdint.h>
#define BUFFER_FAIL     0
#define BUFFER_SUCCESS  1
#define BUFFER_SIZE 100	//100Byte UARTBUFFER


//
// Stellt 1 Byte in den Ringbuffer für das UART0
//
// Returns:
//     BUFFER_FAIL       der Ringbuffer ist voll. Es kann kein weiteres Byte gespeichert werden
//     BUFFER_SUCCESS    das Byte wurde gespeichert
//
uint8_t Buffer0In(uint8_t byte);

//
// Holt 1 Byte aus dem Ringbuffer für das UART0, sofern mindestens eines abholbereit ist
//
// Returns:
//     BUFFER_FAIL       der Ringbuffer ist leer. Es kann kein Byte geliefert werden.
//     BUFFER_SUCCESS    1 Byte wurde geliefert
//
uint8_t Buffer0Out(uint8_t *pByte);

//
// Stellt 1 Byte in den Ringbuffer fürs UART1
//
// Returns:
//     BUFFER_FAIL       der Ringbuffer ist voll. Es kann kein weiteres Byte gespeichert werden
//     BUFFER_SUCCESS    das Byte wurde gespeichert
//
uint8_t Buffer1In(uint8_t byte);

//
// Holt 1 Byte aus dem Ringbuffer fürs UART0, sofern mindestens eines abholbereit ist

// Returns:
//     BUFFER_FAIL       der Ringbuffer ist leer. Es kann kein Byte geliefert werden.
//     BUFFER_SUCCESS    1 Byte wurde geliefert
//
uint8_t Buffer1Out(uint8_t *pByte);

#endif /* RINGBUFFER_H_ */