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
int adcleido=0;
uint8_t lectura =1;
uint8_t valor1= 0; //de 0 a 255
uint16_t valor2=0; //lectura 2, de 0 a 1023
float voltaje1=0;
char buffer[10];
char buffer2[10];
/****************************************/
// Function prototypes
void setup();

/****************************************/
// Main Function
int main(void)
{
	setup();
	LCDstring("S1:");
	LCDsetcursor(8,1);
	LCDstring("S2");
	while(1)
	{
		while (adcleido==1)//creo que no es necesario pero esto hara entrar a cambiar los valores desplegados en la LCD solo si hay lectura de ADC 
		{
			if (lectura==1)
			{
				LCDsetcursor(1,2);//lleva el cursor de escribir a la columna 1 fila 2 de mi pantalla
				voltaje1= ((float)(valor1*5.00f)/255.0f);//convierte a float y cambia de 0-255 a 0-5 V 
				dtostrf(voltaje1, 4, 2, buffer);
				LCDstring(buffer);// escribo el valor en cadena
				LCDcaracter('V');
				ADMUX |= (1<<MUX0); //Cambiamos canal de lectura a Canal 1 del adc
				lectura=2; // que pot leere en la proxima conversion?
				ADCSRA |=(1<<ADSC);
			}else if (lectura==2)
			{
				LCDsetcursor(7,2);
				dtostrf(valor2, 4 ,0,buffer2);
				LCDstring(buffer2);
				ADMUX &= ~(1<<MUX0); //canal 0 seleccionado
				lectura=1; //prox lectura sera en el 1
				ADCSRA |= (1<<ADSC);
			}
			adcleido=0;
		}
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
	adcleido=1;
	if (lectura==1)
	{
		valor1=ADCH;
	}
	else if (lectura==2)
	{
		valor2= ADC>>6; // de 0 a 1023, 10 bits 
	}
}