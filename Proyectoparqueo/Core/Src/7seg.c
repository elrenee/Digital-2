#include "7seg.h"

GPIO_Config segmentos[7] = {
    {a_GPIO_Port, a_Pin},
    {b_GPIO_Port, b_Pin},
    {c_GPIO_Port, c_Pin},
    {d_GPIO_Port, d_Pin},
    {e_GPIO_Port, e_Pin},
    {f_GPIO_Port, f_Pin},
    {g_GPIO_Port, g_Pin}
};

uint8_t numeros[10][7] = {

 //A B C D E F G

 {1,1,1,1,1,1,0}, //0
 {0,1,1,0,0,0,0}, //1
 {1,1,0,1,1,0,1}, //2
 {1,1,1,1,0,0,1}, //3
 {0,1,1,0,0,1,1}, //4
 {1,0,1,1,0,1,1}, //5
 {1,0,1,1,1,1,1}, //6
 {1,1,1,0,0,0,0}, //7
 {1,1,1,1,1,1,1}, //8
 {1,1,1,1,0,1,1}  //9
};

void MostrarNumero(uint8_t numero)
{
    for(int i = 0; i < 7; i++)
    {
        HAL_GPIO_WritePin(
            segmentos[i].port,
            segmentos[i].pin,
            numeros[numero][i] ? GPIO_PIN_SET : GPIO_PIN_RESET
        );
    }
}

