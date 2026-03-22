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
#include <util/delay.h>
#include "Uart/Serial.h"
volatile uint8_t botonesB=0; // pinchange
volatile uint8_t BotonesC=0;
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
	CLKPR = (1<<CLKPCE) ; // Cambios en el preescaler
	CLKPR = (1<<CLKPS2); //1MHz
	UCSR0B = 0x00;
	DDRB = 0b00000000;
	PORTB = 0xFF; //Pull up.
	DDRC =0b00000000;
	PORTC|= 0b00000001;
	PCICR |= (1<<PCIE0)|(1<<PCIE1); //pINCHANGE DEL PUERTO B
	PCMSK0 |= (1<<PCINT0)|(1<<PCINT1)|(1<<PCINT2)|(1<<PCINT3)|(1<<PCINT4)|(1<<PCINT5);
	PCMSK1 |= (1<<PCINT8);
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
// Rutina de interrupcion para PUERTO B: PB0 = AccionB, PB1 = Derecha, PB2 = Izquierda, PB3 = AccionA, PB4 = Arriba, PB5 = Abajo.
ISR(PCINT0_vect)
{
	//PORTB ^= (1 << PORTB5);
	botonesB= PINB; //vemos como estan los botones y en 10 ms veremos nuevamente
	TIFR0 = (1<<TOV0); //limpiamos la bandera de Overflow
	TCNT0=207; //decimos que empiece a contar desde 207
	TIMSK0= (1<<TOIE0); //habilitamos la interrupcción
	PCICR =0;
}
ISR(PCINT1_vect){
	BotonesC=PINC;	
	TIFR0 = (1<<TOV0); //limpiamos la bandera de Overflow
	TCNT0=207; //decimos que empiece a contar desde 207
	TIMSK0= (1<<TOIE0); //habilitamos la interrupcción
	PCICR =0;
}

ISR(TIMER0_OVF_vect) //occurre la interrupción
{
	TIMSK0=0; //apagamos las interrupciones del timer 0
	uint8_t botonest0 = PINB; //vemos nuevamente como estan los botones apachado/no apachados
	if (botonesB == botonest0)	//estan igual que antes??
	{
		if(!(botonesB & (1 << PORTB0)))	//como tengo pull up interno, cuando este apachado el boton deberia de ser 0.
		{
			writecadena("b\n");
		}
		else if(!(botonesB & (1 << PORTB3)))	//como tengo pull up interno, cuando este apachado el boton deberia de ser 0.
		{
			writecadena("a\n");
		}
		else if(!(botonesB & (1 << PORTB1)))	//como tengo pull up interno, cuando este apachado el boton deberia de ser 0.
		{
			writecadena("r\n");
		}
		else if(!(botonesB & (1 << PORTB2)))	//como tengo pull up interno, cuando este apachado el boton deberia de ser 0.
		{
			writecadena("l\n");
		}
		else if(!(botonesB & (1 << PORTB4)))	//como tengo pull up interno, cuando este apachado el boton deberia de ser 0.
		{
			writecadena("u\n");
		}
		//else if(!(botonesB & (1 << PORTB5)))	//como tengo pull up interno, cuando este apachado el boton deberia de ser 0.
		//{
		//	writecadena("d\n");
		//}
	}
	uint8_t botonest1 = PINC; //vemos nuevamente como estan los botones apachado/no apachados
	if (BotonesC == botonest1)	//estan igual que antes??
	{
		if(!(BotonesC & (1 << PORTC0)))	//como tengo pull up interno, cuando este apachado el boton deberia de ser 0.
		{
			writecadena("d\n");
		}
	}
	PCICR |= (1<<PCIE0)|(1<<PCIE1);
}
	