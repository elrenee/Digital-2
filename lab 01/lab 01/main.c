/*
 * ejemploen_C.c 
 *
 * Created:29/03/2025  
 * Author: René David González 
 * Description: Laboratorio 01, programación de microcontroladores. juego de carreras
 */
/****************************************/
// Encabezado (Libraries)
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
uint8_t contador1=0;
uint8_t contador2= 0;
uint8_t seg7=5;
uint8_t iniciar=0;//estados de juego, espera, contar y jugar
uint8_t botonesC=0; // pinchange
int	lista7seg[] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0X79, 0x71};
int contador[]={0x00, 0x01, 0x02, 0x04, 0x08 };
/****************************************/
// Function prototypes
void setup();
void initimr0();
void initmr1();
/****************************************/
// Main Function
int main(void)
{
	setup();
	while(1)
	{
		switch (iniciar)
		{
			case 0:
			PORTD = lista7seg[seg7];// a la espera de iniciar o a que termine de contar
			break;
			case 1:
			 //Juego de botones 2 jugadores 
			 if (contador1>=4)
			 {
				 PCMSK1=0; //quitamos las interrupciones del pinchange
				 PCMSK1 |=  (1<<PCINT8); //Habilitamos nuevamente el boton de iniciar.
				 PORTD &= ~(1<<PORTD7); //apagamos al jugador 2
				 PORTD = lista7seg[1];// mostramos 1 en el 7 seg
				 PORTB = 0x1F; //encendemos los 4 leds y el transitor en PB4
			 }
			 else if (contador2>=4)
			 {
				 PCMSK1=0; //quitamos las interrupciones del pinchange
				 PCMSK1 |=  (1<<PCINT8); //Habilitamos nuevamente el boton de iniciar.
				 PORTB = 0 ;//apagamos al jugador 1
				 PORTD = lista7seg[2];// mostramos 2 en el 7 seg
				 PORTB |= 0x0F; //encendemos los 4 leds 
				 PORTD |= (1<<PORTD7); //ENCENDEMOS EL TRANSIS J2
			 }
			 else
			 {
				  PORTD &= ~(1<<PORTD7); //Apagamos los leds del J2
				  PORTB= contador[contador1]; //mostramos el primer jugador
				  PORTB|= (1<<PORTB4);//encendemos los leds de J1 con su transistor
				  PORTB &= ~(1<<PORTB4); //apago al J1
				  PORTB= contador[contador2]; //mostramos el primer jugador
				  PORTD|= (1<<PORTD7); //ENCIENDO AL J2
				  PORTD |= lista7seg[seg7];
			 }
			break;
		}
	} 
}
/********************************/
// NON-Interrupt subroutines
void setup()
{
	cli();
	DDRB = 0xFF; //Salida, Contador de decadas y multiplexeado
	PORTB = 0x00; // 0v en cada pin.
	
	DDRD = 0xFF; // 7seg
	PORTD = 0x00; // 0v en cada pin
	
	DDRC = 0x00; // Botones de entradas 
	PORTC = 0xFF; //Pull-Up habilitado 
	
	UCSR0B = 0x00; //apagamos los leds del nano
	PCMSK1 |= (1<<PCINT8);// inicialmente solo queremos pinchange en el boton de iniciar, para que antes de iniciar los demas botones no produzcan ningun cambio, al terminar de contar los 5 seg se debe de encender el pinchange de los demas botones y apagar el de iniciar mientras que se este jugando. 
	PCICR |= (1<<PCIE1); //Pinchange enable para el puerto C.
	CLKPR = (1<<CLKPCE) ; // Cambios en el preescaler
	CLKPR = (1<<CLKPS2); //1MHz
	initimr0();
	initmr1(); //Iniciamos timer 1 para contar segundos cuando el botonaso lo diga
	
	sei();	
}

void initmr1()
{
	TCCR1A = 0; //Modo Normal
	TCCR1B |= (1<<CS10)|(1<<CS11); //prescaler de 64
	TCNT1H = 0xC2;
	TCNT1L= 0xF7; //contara de 0xC2F7 a 0xFFFF
	
	
	
}
void initimr0()
{	
	TCCR0A=0;	
	TCCR0B |= (1<<CS02)|(1<<CS00);	//prescaler del timer de 1024
	TCNT0 = 158;
}
/*******************************/
//Interrupt subroutines
ISR(PCINT1_vect)
{
	botonesC= PINC; //vemos como estan los botones y en 10 ms veremos nuevamente
	TIFR0 |= (1<<TOV0); //limpiamos la bandera de Overflow 
	TCNT0=158; //decimos que empiece a contar desde 158
	TIMSK0= (1<<TOIE0); //habilitamos la interrupcción
}

ISR(TIMER0_OVF_vect) //occurre la interrupción
{	
	TIMSK0=0; //apagamos las interrupciones del timer 0
	uint8_t botonest0 = PINC; //vemos nuevamente como estan los botones apachado/no apachados
	if (botonesC == botonest0)	//estan igual que antes??
	{		
		uint8_t start = botonest0 & (0b00000001); //por si acaso matamos todos los demás bits de Puerto C 
		if(start != 0b00000001)	//como tengo pull up interno, cuando este apachado el boton deberia de ser 0. 	
		{
			contador1=0;//REINICIAMOS CONTADORES
			contador2=0;
			iniciar=0; //Reiniciamos estado
			seg7=5;
			PORTB=0;
			PORTD=0;
			TIFR1 |= (1<<TOV1); // limpiamos la bandera de overflow
			TCNT1H = 0xC2;
			TCNT1L= 0xF7; //contara de 0xC2F7 a 0xFFFF
			TIMSK1= (1<<TOIE1); //habilite la interrupción del contador de segundos
			
		}
		uint8_t incj1 = botonest0 & (0b00000010);
		if(incj1 != 0b00000010) //se apacho el inc1
		{
			contador1++; 
		}
		uint8_t incj2 = botonest0 & (0b00000100);
		if(incj2 != 0b00000100) //se apacho el inc2
		{
			contador2++;
		}
		 		
	}
}
ISR(TIMER1_OVF_vect)
{
	seg7--;	
	TCNT1H = 0xC2;
	TCNT1L= 0xF7; //contara de 0xC2F7 a 0xFFFF
	if (seg7==0)
	{	
		iniciar=1;
		TIMSK1= 0;
		PCMSK1 &= ~(1<<PCINT8);//deshabilitamos el boton de iniciar juego durante juegan
		PCMSK1 |= (1<<PCINT9)|(1<<PCINT10); //habilitamos los botones de jugar con pinchange
		
	} 
}