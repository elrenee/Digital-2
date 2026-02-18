/*
 * I2C.c
 *
 * Created: 9/02/2026 23:28:37
 *  Author: Barbaritos
 */ 
#include "I2C.h"

void initmaster()
{
	DDRC &= ~((1<<PORTC4)|(1<<PORTC5)); //SA y SCL
	//TWSR =  PRESCALER
	//TWBR = ((F_CPU/SCLK)-16)/(2*prescaler);
	TWCR |= (1<<TWEN); //Activar I2C
}

uint8_t masterstart()
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR&(1<<TWINT)));//eSPERAMOS QUE SE ENCIENDA LA BANDERA
	return ((TWSR & 0xF8)==0x08);
}

uint8_t masterrepeatedstart()
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR&(1<<TWINT)));//eSPERAMOS QUE SE ENCIENDA LA BANDERA
	return ((TWSR & 0xF8)==0x10);
}

void masterstop()
{
		TWCR =(1<<TWEN)|(1<<TWINT)|(1<<TWSTO);
		while (TWCR	& (1<<TWSTO)); //esperamos a que se haga la secuencia de start
}

uint8_t masterwrite(uint8_t dato)
{
	uint8_t estado;
	TWDR = dato;
	TWCR = (1<<TWEN)| (1<<TWINT);
	
	while (TWCR &(1<<TWINT)); //bandera de interrupcion
	estado = TWSR & 0XF8; //SOlo nos quedamos con los bits de estado
	
	if (estado==0x18 || estado==0x28)
	{
		return 1;
	}else
	{
		return estado;
	}
}

uint8_t masterread(uint8_t *buffer, uint8_t ack)
{
	uint8_t estado;
	if (ack)
	{
		//se desea seguir leyendo.
		TWCR= (1<<TWINT)| (1<<TWEN) | (1<<TWEA); //LIMPIO INTERRUPT, I2C ENABLE, Envio de ack automatico
	} else{
		//Ultimo byte, NACK
		TWCR= (1<<TWINT)| (1<<TWEN); //LIMPIO INTERRUPT, I2C ENABLE, ya no envio ack
	}
	while (!(TWCR&(1<<TWINT))); //esperamos a que suceda la comunicación
	
	estado= TWSR & 0xF8; //vemos que estado viene.
	//vemos si viene con ACK o NACK
	if (ack && estado != 0x50) return 0; //Dato recibido, ACK, Si no es ninguno de estos 2 mandamos 0
	if (!ack && estado!= 0x58) return 0; //Dato recibido, NACK
	
	*buffer = TWDR; //Dato recibido a Buffer
	return 1; // s todo bien guardamos los datos y return 1
}



//Inicializar Esclavo

void initslave(uint8_t slaveaddress)
{
	DDRC &= ~((1<<PORTC4)|(1<<PORTC5)); //Pines I2c como entradas
	TWAR =slaveaddress<<1; //nombre o direccion sin general call
	TWCR = (1<<TWEA)|(1<<TWEN)|(1<<TWIE)|(1<<TWINT); //Habilitamos I2C,ACK automatico, ISR habilitadas
}