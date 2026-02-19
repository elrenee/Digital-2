/*
 * Laboratorio 2.c 
 *
 * Created:26/01/2026  
 * Author: René David González Herrera 
 * Description: Laboratorio 02,Digital 2. Pantallas LCD y ADC
 */
/****************************************/

// Encabezado (Libraries)
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Stepper/stepper.h"
/****************************************/
// Function prototypes
void setup();

/****************************************/
// Main Function
int main(void)
{
	setup();
	while(1)
	{
		 girarPorTiempo(10000, 1);  // gira 2 segundos horario
		 _delay_ms(1000);

		 girarPorTiempo(3000, 0);  // gira 2 segundos antihorario
		 _delay_ms(1000);
	}
}

/********************************/
// NON-Interrupt subroutines
void setup()
{
	cli();
	DDRD |= 0b00001111;  // D0-D3 como salidas
	sei();
}


/*******************************/
//Interrupt subroutines