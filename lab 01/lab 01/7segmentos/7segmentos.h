/*
 * _7segmentos.h
 *
 * Created: 24/01/2026 18:10:46
 *  Author: Barbaritos
 */ 


#ifndef 7SEGMENTOS_H_
#define 7SEGMENTOS_H_

#include <avr/io.h>

int	lista7seg[] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0X79, 0x71};

void mostrar_numero(uint8_t numero);


#endif /* 7SEGMENTOS_H_ */