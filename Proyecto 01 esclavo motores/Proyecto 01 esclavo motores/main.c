/*
 * Proyecto de Digital 02 .c 
 *
 * Created:26/01/2026  
 * Author: René David González Herrera 
 * Description: Comunicación I2C, esclavo encargado de controlar los motores en relacion con lo que le diga el maestro. MOdos, Automatico, dependiendo de la informacion recabada el hará con los motores... 
 
 */
/****************************************/

// Encabezado (Libraries)
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "I2C/I2C.h"
#include "PWM/PWM.h"
#include "Stepper/stepper.h"

#define slave2 0x40
uint8_t buffer=0;

uint8_t indicereceipt=0;
uint8_t DC=0;
uint8_t stepper=0;
uint8_t servo=0; //PB1
uint16_t angulo=0;
uint8_t abierto=1;
uint8_t cerrado =0;
//extractor o dc en el PD4
//STEPPER  del D0-D3
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
		if (DC==0)
		{
			PORTD &=~(1<<PORTD4);
		}
		else if (DC==1)
		{
			PORTD |= (1<<PORTD4);
		}
		_delay_ms(100);
		if (stepper==0 && cerrado==0)//0 es cerrar 
		{
			girarPorTiempo(10000, 1); //cierra contra las agujas	
			cerrado=1;
			abierto=0;
		}
		if(stepper==1 && abierto==0){
			girarPorTiempo(10000, 0);
			cerrado=0;
			abierto=1;
		}
		_delay_ms(100);
		if (servo==0){
			angulo=1600; //Ocr1a para 20 grados en el servo.
			movservo2(angulo);
		}else if(servo==1){
			angulo=2100;
			movservo2(angulo);
		}else if(servo==2){
			angulo=2993;
			movservo2(angulo);
		}
		_delay_ms(100);
	}
}

/********************************/
// NON-Interrupt subroutines
void setup()
{
	cli();
	initslave(slave2);
	initPWM();
	DDRD =0x1F;// Salidas de el Stepper y el DC.
	PORTD=0; //0V inicialmente...
	sei();
}


/*******************************/
//Interrupt subroutines
ISR(TWI_vect)
{
	uint8_t estado= TWSR&0xF8; //estado sera el por que ocurrio la interrupción
	switch (estado){
		case 0x60:
		case 0x70://es un GNRL call o un SLA+W
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
		break;
		
		case 0x80:// me escribieron o mandaron algoy mande el ack
		case 0x90://escribieron a todos y mande el ack
		if (indicereceipt==0)//Primera recepción
		{
			DC= TWDR; //Motor DC encendido o apagado
			indicereceipt=1; 
		}else if (indicereceipt==1)//segunda recepción
		{
			stepper=TWDR;
			indicereceipt=2;
			
		}else if (indicereceipt==2)//tercera recepción
		{
			servo=TWDR;
			indicereceipt=0;
		}
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
		break;
		
		case 0xA8: //SLA+R
		case 0xB8://Dato mandamos un dato y nos regresaron por otro
		//TWDR=VALOR;
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
