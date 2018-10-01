/*
 * I2C.h
 *
 * Created: 19.09.2018 22:07:54
 *  Author: Manuel
 */ 


#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void i2c_init(void);
uint8_t i2c_start(uint8_t address);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);
void i2c_gettemp(uint8_t * msbyte, uint8_t * lsbyte);
uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
void i2c_stop(void);

#endif /* I2C_H_ 229*/