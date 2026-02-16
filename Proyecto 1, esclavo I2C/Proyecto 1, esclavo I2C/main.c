/*
 * Proyecto 01.c 
 *
 * Created:09/02/2026  
 * Author: René David González Herrera 
 * Description: Proyecto 01,Digital 2. Esclavo comunicación I2C. en el cual leeremos todos los sensores y prepararemos la data para cuando el maestro la requiera.
 */
/****************************************/

// Encabezado (Libraries)
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C/I2C.h"
#include "ADC/ADC.h"
#define slave1 0x10 //Direccion del esclavo encargado de los sensores.

uint8_t buffer =0;
volatile uint8_t contconversion=0;// INdice de recoleccion de datos 
uint8_t sensoraire=0; //Canal 1 de ADC A1
uint8_t sensor_luz=0;//Canal 0 de ADC A0
uint8_t enviodedatos =0; //Indice de envio de datos
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
		
	}
}

/********************************/
// NON-Interrupt subroutines
void setup()
{
	cli();
	initslave(slave1);
	initADC();
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
			if (enviodedatos==0)//Indice de envio de datos, Sensor de aire
			{
				TWDR=sensoraire; //enviamos valor de 0 a 255 de sensor
				enviodedatos=1;//Acomodamos el indice para la proxima vez
			}else if (enviodedatos==1) //Indice de envio de datos, Sensor de LUZ data send
			{
				TWDR=sensor_luz;//Enviamos el dato
				enviodedatos=0;//acomodamos el indice para la proxima vez
			}
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

ISR (ADC_vect)
{
	if (contconversion==0)//Lectura de Aire
	{
		contconversion=1;
		ADMUX &= ~(1<<MUX0); //Escogemos el canal 0, Sensor de luz
		sensoraire=ADCH;//Esta lectura es del sensor de aire en el canal 1.
		ADCSRA |= (1<<ADSC);//Iniciamos conversion
	}
	else if (contconversion==1) //Lectura de Luz
	{
		contconversion=0;
		ADMUX |= (1<<MUX0);//Canal 1 escogido para ir a leer el sensor de aire
		sensor_luz=ADCH; //Esta lectura es de luz.
		ADCSRA |=(1<<ADSC);
	}
	
}