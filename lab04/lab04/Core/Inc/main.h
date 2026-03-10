/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define L1J1_Pin GPIO_PIN_0
#define L1J1_GPIO_Port GPIOC
#define L2J1_Pin GPIO_PIN_1
#define L2J1_GPIO_Port GPIOC
#define L3J1_Pin GPIO_PIN_2
#define L3J1_GPIO_Port GPIOC
#define L4J1_Pin GPIO_PIN_3
#define L4J1_GPIO_Port GPIOC
#define f_Pin GPIO_PIN_0
#define f_GPIO_Port GPIOA
#define a_Pin GPIO_PIN_1
#define a_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define b_Pin GPIO_PIN_4
#define b_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define g_Pin GPIO_PIN_5
#define g_GPIO_Port GPIOC
#define c_Pin GPIO_PIN_0
#define c_GPIO_Port GPIOB
#define L1J2_Pin GPIO_PIN_12
#define L1J2_GPIO_Port GPIOB
#define L2J2_Pin GPIO_PIN_13
#define L2J2_GPIO_Port GPIOB
#define L3J2_Pin GPIO_PIN_14
#define L3J2_GPIO_Port GPIOB
#define L4J2_Pin GPIO_PIN_15
#define L4J2_GPIO_Port GPIOB
#define d_Pin GPIO_PIN_6
#define d_GPIO_Port GPIOC
#define e_Pin GPIO_PIN_8
#define e_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define Binic_Pin GPIO_PIN_10
#define Binic_GPIO_Port GPIOC
#define Binic_EXTI_IRQn EXTI15_10_IRQn
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define B1B4_Pin GPIO_PIN_4
#define B1B4_GPIO_Port GPIOB
#define B1B4_EXTI_IRQn EXTI4_IRQn
#define B2_Pin GPIO_PIN_5
#define B2_GPIO_Port GPIOB
#define B2_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
