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
#include <util/delay.h>
#include <avr/interrupt.h>
#include "PantallasLCD/LCD.h"

/****************************************/
// Function prototypes
void setup();

/****************************************/
// Main Function
int main(void)
{
	setup();
	LCDcaracter('O');
	LCDcaracter('O');
	LCDsetcursor(1,2);
	LCDcaracter('A');
	LCDstring("jorch petenero");
	while(1)
	{
		
	}
}

/********************************/
// NON-Interrupt subroutines
void setup()
{
	cli();
	initLCD8bits();
	LCDsetcursor(1,1);
	sei();
}


/*******************************/
//Interrupt subroutines