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
#include "Convertidor/ADC.h"
#include "SPI/Slave.h"

uint8_t pot1=0;
uint8_t pot2=0;
uint8_t lectura=0;

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
		
	}
}

/********************************/
// NON-Interrupt subroutines
void setup()
{
	cli();
	initSlave();
	initADC();
	SPCR|= (1<<SPIE);
	sei();
}


/*******************************/
//Interrupt subroutines