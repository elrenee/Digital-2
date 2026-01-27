/*
 * LCD.c
 *
 * Created: 26/01/2026 23:01:59
 *  Author: Barbaritos
 */ 
#include "LCD.h"

void initLCD8bits(void)
{
	DDRD |=(1<<PORTD7)|(1<<PORTD6)|(1<<PORTD5)|(1<<PORTD4)|(1<<PORTD2)|(1<<PORTD3);// salidas para la LCD primeros 4 bits
	PORTD &= ~((1<<PORTD7)|(1<<PORTD6)|(1<<PORTD5)|(1<<PORTD4)); //las ponemos en 0
	DDRB |=(1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3); //salidas de la LCD siguientes 4 bits
	PORTB &= ~((1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3));
	
	LCDPort(0x00);
	_delay_ms(20);
	LCDCMD(0x03);
	_delay_ms(4);
	LCDCMD(0x03);
	_delay_ms(4);
	LCDCMD(0x03);
	_delay_ms(4);
	LCDCMD(0x38);
	_delay_ms(4);
	LCDCMD(0x0C);
	_delay_ms(10);
	LCDCMD(0X06);
	_delay_ms(10);
	LCDCMD(0x01);
}

//mandar comando
void LCDCMD(char a)
{
	PORTD &= ~(1<<PORTD2); //Rs en 0
	LCDPort(a);//Enviar el comando alto y bajo 
	PORTD |= (1<<PORTD3); //E=1
	_delay_ms(4);
	PORTD &= ~(1<<PORTD3); //E=0
}
void LCDPort(char a)
{
	// Limpiamos los bits altos del puerto D y los bajos del puerto B, que es donde esta del D0 al D7 de la LCD
	PORTD &= 0x0F;      // Limpiar solo bits D4-D7 (11110000 en binario)
	PORTB &= 0xF0;      // Limpiar solo bits B0-B3 (00001111 en binario)
	
	// corremos los bits a sus posiciones
	PORTD |= ((a & 0x0F) << 4);  // parte baja a D4-D7
	PORTB |= ((a & 0xF0) >> 4);  // parte alta a B0-B3

}

void LCDcaracter(char c)
{
	PORTD |= (1<<PORTD2); //rs=1
	LCDPort(c);
	PORTD |= (1<<PORTD3); //E=1
	_delay_ms(4);
	PORTD &= ~(1<<PORTD3); //E=0
}

void LCDstring(char *a)
{
	int i;
	for (i=0; a[i] != '\0'; i++)
	{
		LCDcaracter(a[i]);
	}
}
void LCDderecha(void)
{
	LCDCMD(0x1C);
}

void LCDizq(void)
{
	LCDCMD(0x18);
}

void LCDsetcursor(char a, char f)
{
	char temp;
	if (f==1) //Vemos que columna y fila queremos escribir y lo seteamos ahi
	{
		temp =0x80+ a - 1;
		LCDCMD(temp);
	} else if (f==2)
	{
		temp =0xC0+a -1;
		LCDCMD(temp);
	}
}