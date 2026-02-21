/*
 * stepper.c
 *
 * Created: 18/02/2026 00:29:37
 *  Author: Barbaritos
 */ 
#include "stepper.h"


const uint8_t secuencia[4] = {
	0b0011, // Paso 1: pines D0 y D1 en HIGH
	0b0110, // Paso 2: pines D1 y D2 en HIGH
	0b1100, // Paso 3: pines D2 y D3 en HIGH
	0b1001  // Paso 4: pines D3 y D0 en HIGH
};

static int pasoActual = 0;
static const int intervaloPasos = 5; // ms entre cada paso

// Girar el motor 
void girarPorTiempo(unsigned long tiempoMs, int direccionHoraria) {
	unsigned long pasosTotales = tiempoMs / intervaloPasos;

	for (unsigned long i = 0; i < pasosTotales; i++) {

		// Avanzar o retroceder
		if (direccionHoraria)
		{
			pasoActual = (pasoActual + 1) % 4;
		} else 
		{
			pasoActual = (pasoActual - 1 + 4) % 4;
		}

		// Actualizar pines D0-D3
		PORTD = (PORTD & 0b11110000) | (secuencia[pasoActual] & 0b00001111);

		_delay_ms(intervaloPasos);
	}
	PORTD &= 0b11110000; //apagar las bobinas del stepper 
}
