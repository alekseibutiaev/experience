/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32l4xx_hal.h"

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
#define blue_button_interrupt_Pin GPIO_PIN_13
#define blue_button_interrupt_GPIO_Port GPIOC
#define blue_button_interrupt_EXTI_IRQn EXTI15_10_IRQn
#define rowrscan_0_Pin GPIO_PIN_0
#define rowrscan_0_GPIO_Port GPIOC
#define rowrscan_1_Pin GPIO_PIN_1
#define rowrscan_1_GPIO_Port GPIOC
#define rowrscan_2_Pin GPIO_PIN_2
#define rowrscan_2_GPIO_Port GPIOC
#define rowrscan_3_Pin GPIO_PIN_3
#define rowrscan_3_GPIO_Port GPIOC
#define custom_Pin GPIO_PIN_0
#define custom_GPIO_Port GPIOA
#define custom_EXTI_IRQn EXTI0_IRQn
#define USART2_TX_Pin GPIO_PIN_2
#define USART2_TX_GPIO_Port GPIOA
#define USART2_RX_Pin GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define rowrscan_4_Pin GPIO_PIN_4
#define rowrscan_4_GPIO_Port GPIOC
#define rowrscan_5_Pin GPIO_PIN_5
#define rowrscan_5_GPIO_Port GPIOC
#define rowrscan_6_Pin GPIO_PIN_6
#define rowrscan_6_GPIO_Port GPIOC
#define rowrscan_7_Pin GPIO_PIN_7
#define rowrscan_7_GPIO_Port GPIOC
#define colbit_0_Pin GPIO_PIN_8
#define colbit_0_GPIO_Port GPIOC
#define colbit_1_Pin GPIO_PIN_9
#define colbit_1_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define colbit_2_Pin GPIO_PIN_10
#define colbit_2_GPIO_Port GPIOC
#define colbit_3_Pin GPIO_PIN_11
#define colbit_3_GPIO_Port GPIOC
#define colbit_4_Pin GPIO_PIN_12
#define colbit_4_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
