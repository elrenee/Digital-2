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
	
	sei();
}


/*******************************/
//Interrupt subroutines