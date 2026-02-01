/*
 * ADC.c
 *
 * Created: 27/01/2026 17:33:45
 *  Author: Barbaritos
 */ 
#include "ADC.h"

void initADC(void)
{
	CLKPR= (1<<CLKPCE); //Cambios en la frecuencia del sistema
	CLKPR = (1<<CLKPS2); //prescaler de 16 
	
	ADMUX =0;
	ADMUX |= (1<<REFS0)|(1<<ADLAR)|(1<<MUX0); //referancia interna, ajustado a la izquierda, canal 1 inicial mente. 

	ADCSRA =0;
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADIE)|(1<<ADEN);
}