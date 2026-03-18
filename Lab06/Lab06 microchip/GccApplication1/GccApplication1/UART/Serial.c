/*
 * Serial.c
 *
 * Created: 31/01/2026 22:49:31
 *  Author: Barbaritos
 */ 
#include "Serial.h"

void iniUart(void)//modo asincrono.
{
	DDRD |= (1<<PORTD1); // TX pin d1
	DDRD &= ~(1<<PORTD0); //RX pin d0 como entrada
	
	UCSR0A =0; 
	UCSR0A |=(1<<U2X0); //doble velocidad.
	
	UCSR0B =0;
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); // Habilitamos Interrupciónes al recibir, habilitamos la recepcion y tambien la transmisión (no la usaremos en este caso).
	
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00); // 8 bits
	
	UBRR0 = 12; //para un Baudrate de 9615 con una frecuencia de reloj de 1MHz
}

void writechar(char letra)
{
	while ((UCSR0A & (1<<UDRE0))==0); //mientras no este vacio esperará, el 5to bit da 1 cuando esta vacío. 
	UDR0=letra;
}

void writecadena(char* string)
{
	int i;
	for (i=0; string[i] != '\0'; i++)
	{
		writechar(string[i]);
	}
}