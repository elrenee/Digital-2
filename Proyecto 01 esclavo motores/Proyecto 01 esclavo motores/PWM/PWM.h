/*
 * PWM.h
 *
 * Created: 10/02/2026 15:43:18
 *  Author: Barbaritos
 */ 


#ifndef PWM_H_
#define PWM_H_

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
void initPWM();void initPWM2();void movservo1(uint16_t posicion);
void movservo2(uint16_t servo2);void movservo3(uint16_t posicion3);void movservo4(uint16_t posicion4);

#endif /* PWM_H_ */