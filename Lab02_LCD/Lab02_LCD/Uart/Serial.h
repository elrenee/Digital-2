/*
 * Serial.h
 *
 * Created: 31/01/2026 22:49:15
 *  Author: Barbaritos
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void iniUart(void);
void writechar(char letra);
void writecadena(char* string);
#endif /* SERIAL_H_ */