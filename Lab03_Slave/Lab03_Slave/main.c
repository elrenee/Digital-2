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
uint8_t spivalor=0;
uint8_t contador=0;
uint8_t hablamaestro=0;
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
		PORTD = contador;
		
	}
}

/********************************/
// NON-Interrupt subroutines
void setup()
{
	cli();
	DDRD = 0XFF; // PUERTO D COMO SALIDA
	PORTD=0X00; //iNICIALMENTE APAGADOS
	initSlave();
	initADC();
	SPCR|= (1<<SPIE);
	ADCSRA|= (1<<ADSC);
	sei();
}


/*******************************/
//Interrupt subroutines
ISR(ADC_vect)
{
	if (lectura==0)
	{
		pot1=ADCH;
		lectura=1;
		ADMUX|= (1<<MUX0); //CANAL 1 SELECCIONADO
		ADCSRA|= (1<<ADSC);
	}else if (lectura==1)
	{
		pot2=ADCH;
		lectura=0;
		ADMUX&= ~(1<<MUX0); //CANAL 0 SELECCIONADO
		ADCSRA|=(1<<ADSC);
	}
}

ISR(SPI_STC_vect)
{
	uint8_t spivalor= SPDR;
	
	if (hablamaestro==0)
	{
		if (spivalor== 'a')
		{
			SPDR=pot1;
		}
		else if (spivalor == 'b')
		{
			SPDR=pot2;
		}
		else if (spivalor=='c')
		{
			SPDR=0x00;
			hablamaestro=1;
		}
	}else if (hablamaestro==1)
	{
		hablamaestro=0;
		contador=spivalor;
	}
	
}