#ifndef DISPLAY7SEG_H
#define DISPLAY7SEG_H

#include "main.h"


typedef struct {
	GPIO_TypeDef* port;
    uint16_t pin;
} GPIO_Config;


void Display7Seg_Init(void);
void MostrarNumero(uint8_t numero);

#endif
