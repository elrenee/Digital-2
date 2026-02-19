/*
 * stepper.h
 *
 * Created: 18/02/2026 00:28:56
 *  Author: Barbaritos
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void girarPorTiempo(unsigned long tiempoMs, int direccionHoraria);


#endif /* STEPPER_H_ */