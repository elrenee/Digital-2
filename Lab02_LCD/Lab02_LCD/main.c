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
#include <stdlib.h>
#include "PantallasLCD/LCD.h"
#include "Convertidor/ADC.h"
uint8_t lectura =1;
uint8_t valor1= 0;
float voltaje1=0;
char buffer[10];
/****************************************/
// Function prototypes
void setup();

/****************************************/
// Main Function
int main(void)
{
	setup();
	LCDcaracter('P');
	LCDcaracter('1');
	LCDsetcursor(1,2);
	while(1)
	{
		_delay_ms(10);
		LCDsetcursor(1,2);
		voltaje1= ((float)(valor1*5.00f)/255.0f);
		dtostrf(voltaje1, 4, 2, buffer);
		LCDstring(buffer);// cambiarlo a Entero
		ADCSRA |=(1<<ADSC);
	}
}

/********************************/
// NON-Interrupt subroutines
void setup()
{
	cli();
	initLCD8bits();
	LCDsetcursor(2,1);
	DDRC =0x00; //Puerto c como entradas 
	PORTC =0x00; //Puerto c sin pullup
	
	initADC();
	ADCSRA |= (1<<ADSC);
	sei();
}


/*******************************/
//Interrupt subroutines
ISR(ADC_vect)
{
	if (lectura==1)
	{
		valor1=ADCH;
		//ADMUX |= (1<<MUX0); //Canal 1
		//lectura=2;
		
		
	}
	//else if (lectura==2)
	//{
	//	valor2= ADCH;
	//	ADMUX &=
	//}
}