/*
 * Proyecto 01.c 
 *
 * Created:09/02/2026  
 * Author: René David González Herrera 
 * Description: Proyecto 01,Digital 2. Esclavo comunicación I2C.
 */
/****************************************/

// Encabezado (Libraries)
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C/I2C.h"
#include "PWM/PWM.h"
#define slave1 0x10
//MAESTRO LEER O ESCRIBIR
#define slave1R (0x10<<1)|0x01
#define  slave1W (0x10<<1)& 0xFE

uint8_t buffer =0;
volatile uint8_t adc=0;
uint16_t servo=0;
uint16_t servo3=0;
/****************************************/
// Function prototypes
void setup();
//adc?


/****************************************/
// Main Function
int main(void)
{
	setup();
	while(1)
	{
		servo= 1200+(0*14.12);
		movservo1(servo);
		servo3= 16+(0/17);
		movservo4(servo3);
		//if(buffer=='r') Quiere leer o escribir
		//{buffer=0;}
	}
}

/********************************/
// NON-Interrupt subroutines
void setup()
{
	cli();
	initslave(slave1);
	initPWM();
	initPWM2();
	sei();
}


/*******************************/
//Interrupt subroutines

ISR(TWI_vect)
{
	uint8_t estado= TWSR&0xFC; //estado sera el por que ocurrio la interrupción
	switch (estado){
		case 0x60:
		case 0x70://es un GNRL call o un SLA+W
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;	
			
		case 0x80:// me escribieron o mandaron algoy mande el ack
		case 0x90://escribieron a todos y mande el ack
			buffer = TWDR;
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;
		case 0xA8: //SLA+R
		case 0xB8://Dato mandamos un dato y nos regresaron por otro
			TWDR= adc;//enviamos el dato
			TWCR=  (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;
		case 0xC0:
		case 0xC8: //Dato enviado y no ACK o se envio el ultimo dato. 
			TWCR=0;
			TWCR=  (1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;
		case 0x0A: //STOP o REPEATED start
			TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;
		default:
			TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;
	}
}