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

#define slave2 0x20
uint8_t buffer=0;

uint8_t indicereceipt=0;

uint8_t temperatura=0;
uint8_t luz=0;
uint8_t aire=0;

uint8_t dia=0;
uint8_t calor=0;
uint8_t humo=0;

uint8_t servo=0;
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
		//Vemos los datos de cada sensor
		if(temperatura<85)//Datos que vienen de el sensor de temperatura
			calor=0; //Calor 0 = poco calor
		else if ((temperatura>=85) && (temperatura <170))
			calor=1; //calor intermedio
		else if (temperatura>=170)
			calor=2;
		//Vemos los datos que vienen del sensor de LUZ
		if (luz<127) 
			dia =1;
		else if (luz >= 127)
			dia=0;
		//Vemos los datos que vienen del sensor de calidad de aire
		if (aire<127)
			humo=0;
		else if (aire>= 127)
			humo=1;
			
		if ((calor==0)&&(dia==1)&&(humo==0))
		{
			PORTD &= ~(1<<PORTD5); //extractor apagado
			//servo=  angulo para que se cierre la ventana
			movservo1(servo); //servo
			//cerrarcortina();
		}//else if ()
		//{
			
		//}
	}
}

/********************************/
// NON-Interrupt subroutines
void setup()
{
	cli();
	initslave(slave2);
	initPWM();
	DDRD |= (1<<PORTD5);
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
		if (indicereceipt==0)//Primera recepción
		{
			//variable sensor X= TWDR;
			indicereceipt=1; 
		}else if (indicereceipt==1)//segunda recepción
		{
			indicereceipt=2;
			
		}else if (indicereceipt==2)//tercera recepción
		{
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
