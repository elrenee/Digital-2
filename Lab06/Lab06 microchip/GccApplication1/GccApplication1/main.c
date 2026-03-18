/*
 * Laboratorio 2.c 
 *
 * Created:26/01/2026  
 * Author: René David González Herrera 
 * Description: Laboratorio 06,Digital 2. Pinchange y uart
 */
/****************************************/

// Encabezado (Libraries)
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART/Serial.h"

uint8_t botonesB=0; // pinchange
/****************************************/
// Function prototypes
void setup();
void initimr0();

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
	DDRB = 0x00;
	PORTB = 0xFF; //Pull up.
	PCMSK0 = 0XFF;
	PCICR |= (1<<PCIE0); //pINCHANGE DEL PUERTO B
	CLKPR = (1<<CLKPCE) ; // Cambios en el preescaler
	CLKPR = (1<<CLKPS2); //1MHz
	initimr0();
	iniUart();
	sei();
}


void initimr0()
{
	TCCR0A=0;
	TCCR0B |= (1<<CS02)|(1<<CS00);	//prescaler del timer de 1024
	TCNT0 = 207; //207 para 0.05 seg
}


/*******************************/
//Interrupt subroutines

ISR(PCINT0_vect)
{
	botonesB= PINB; //vemos como estan los botones y en 10 ms veremos nuevamente
	TIFR0 |= (1<<TOV0); //limpiamos la bandera de Overflow
	TCNT0=207; //decimos que empiece a contar desde 207
	TIMSK0= (1<<TOIE0); //habilitamos la interrupcción
}

ISR(TIMER0_OVF_vect) //occurre la interrupción
{
	TIMSK0=0; //apagamos las interrupciones del timer 0
	uint8_t botonest0 = PINB; //vemos nuevamente como estan los botones apachado/no apachados
	if (botonesB == botonest0)	//estan igual que antes??
	{
		uint8_t accionB = botonest0 & (0b00000001); //por si acaso matamos todos los demás bits de Puerto B
		if(accionB != 0b00000001)	//como tengo pull up interno, cuando este apachado el boton deberia de ser 0.
		{
			writecadena("BotB");
		}
		uint8_t accionA = botonest0 & (0b00001000);
		if(accionA != 0b00001000){
			writecadena("BotA");
		}
		uint8_t derecha = botonest0 & (0b00000010);
		if(derecha != 0b00000010){
			writecadena("derecha");
		}
		uint8_t izquierda = botonest0 & (0b00000100);
		if(izquierda != 0b00000100){
			writecadena("izquierda");
		}
		uint8_t Arriba = botonest0 & (0b00010000);
		if(Arriba != 0b00010000){
			writecadena("arriba");
		}
		uint8_t Abajo = botonest0 & (0b00100000);
		if(Abajo != 0b00100000){
			writecadena("abajo");
		}
	}
}
		