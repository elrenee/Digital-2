/*
 * Slave.c
 *
 * Created: 7/02/2026 00:28:26
 *  Author: Barbaritos
 */ 
#include "Slave.h"
void initSlave()
{
	DDRB |= (1<<PORTB4); // Miso como salida
	DDRB &= ~((1<<PORTB3)|(1<<PORTB5)|(1<<PORTB2)); //MOSI, SCK, SS como entradas.
	
	SPCR &= ~((1<<MSTR)|(1<<CPOL)|(1<<CPHA)|(1<<DORD)); //esclavo seleccionado, CLK POLARITY 0, CLK PHASE 0, ORDEN DE ENVIO
	
	SPCR |= (1<<SPE); //COMUNICACIÓN HABILITADA
}
