/*
 * LCD.h
 *
 * Created: 26/01/2026 23:01:25
 *  Author: Barbaritos
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

//Funcion Prototype

void initLCD8bits(void); //inicializar la lcd funcion
void LCDPort(char a); //Enviar el dato a la LCD
void LCDCMD(char a);//Enviar comando a RS
void LCDcaracter(char c); //Funcion para escribir caracteres
void LCDstring(char *a); //Funcion para escribir cadena
void LCDderecha(void);// funcion para desplazarme a la derecha
void LCDizq(void); //Desplazamiento a la izquierda
void LCDsetcursor(char a, char f);//establecer posicion del cursor



#endif /* LCD_H_ */