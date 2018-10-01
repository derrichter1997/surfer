/*
 * Ringbuffer.c
 *
 * Created: 03.11.2016 11:22:21
 *  Author: manuelrichter
*/
#include "Ringbuffer.h"


//Buffer für das UART0
struct Buffer0 {
	uint8_t data[BUFFER_SIZE];
	uint8_t read; // zeigt auf das Feld mit dem ältesten Inhalt
	uint8_t write; // zeigt immer auf leeres Feld
	} buffer0 = {{}, 0, 0};
		
//Buffer für das UART1
struct Buffer1 {
	uint8_t data[BUFFER_SIZE];
	uint8_t read; // zeigt auf das Feld mit dem ältesten Inhalt
	uint8_t write; // zeigt immer auf leeres Feld
	} buffer1 = {{}, 0, 0};


	//
	// Stellt 1 Byte in den Ringbuffer
	//
	// Returns:
	//     BUFFER_FAIL       der Ringbuffer fürs UART0 ist voll. Es kann kein weiteres Byte gespeichert werden
	//     BUFFER_SUCCESS    das Byte wurde gespeichert
	//
	uint8_t Buffer0In(uint8_t byte)
	{
		//if (buffer.write >= BUFFER_SIZE)
		//  buffer.write = 0; // erhöht sicherheit

		if ( ( buffer0.write + 1 == buffer0.read ) ||
		( buffer0.read == 0 && buffer0.write + 1 == BUFFER_SIZE ) )
		return BUFFER_FAIL; // voll

		buffer0.data[buffer0.write] = byte;

		buffer0.write++;
		if (buffer0.write >= BUFFER_SIZE)
		buffer0.write = 0;

		return BUFFER_SUCCESS;
	}

	//
	// Holt 1 Byte aus dem Ringbuffer fürs UART0, sofern mindestens eines abholbereit ist
	//
	// Returns:
	//     BUFFER_FAIL       der Ringbuffer ist leer. Es kann kein Byte geliefert werden.
	//     BUFFER_SUCCESS    1 Byte wurde geliefert
	//
	uint8_t Buffer0Out(uint8_t *pByte)
	{
		if (buffer0.read == buffer0.write)
		return BUFFER_FAIL;

		*pByte = buffer0.data[buffer0.read];

		buffer0.read++;
		if (buffer0.read >= BUFFER_SIZE)
		buffer0.read = 0;

		return BUFFER_SUCCESS;
	}


	//
	// Stellt 1 Byte in den Ringbuffer
	//
	// Returns:
	//     BUFFER_FAIL       der Ringbuffer fürs UART1 ist voll. Es kann kein weiteres Byte gespeichert werden
	//     BUFFER_SUCCESS    das Byte wurde gespeichert
	//
	uint8_t Buffer1In(uint8_t byte)
	{
		//if (buffer.write >= BUFFER_SIZE)
		//  buffer.write = 0; // erhöht sicherheit

		if ( ( buffer1.write + 1 == buffer1.read ) ||
		( buffer1.read == 0 && buffer1.write + 1 == BUFFER_SIZE ) )
		return BUFFER_FAIL; // voll

		buffer1.data[buffer1.write] = byte;

		buffer1.write++;
		if (buffer1.write >= BUFFER_SIZE)
		buffer1.write = 0;

		return BUFFER_SUCCESS;
	}

	//
	// Holt 1 Byte aus dem Ringbuffer fürs UART1, sofern mindestens eines abholbereit ist
	//
	// Returns:
	//     BUFFER_FAIL       der Ringbuffer ist leer. Es kann kein Byte geliefert werden.
	//     BUFFER_SUCCESS    1 Byte wurde geliefert
	//
	uint8_t Buffer1Out(uint8_t *pByte)
	{
		if (buffer1.read == buffer1.write)
		return BUFFER_FAIL;

		*pByte = buffer1.data[buffer1.read];

		buffer1.read++;
		if (buffer1.read >= BUFFER_SIZE)
		buffer1.read = 0;

		return BUFFER_SUCCESS;
	}
