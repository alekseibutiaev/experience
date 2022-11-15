/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define KeyD0_Pin GPIO_PIN_0
#define KeyD0_GPIO_Port GPIOC
#define KeyD1_Pin GPIO_PIN_1
#define KeyD1_GPIO_Port GPIOC
#define KeyD2_Pin GPIO_PIN_2
#define KeyD2_GPIO_Port GPIOC
#define KeyD3_Pin GPIO_PIN_3
#define KeyD3_GPIO_Port GPIOC
#define KeyD4_Pin GPIO_PIN_4
#define KeyD4_GPIO_Port GPIOC
#define KeyA8_Pin GPIO_PIN_8
#define KeyA8_GPIO_Port GPIOB
#define KeyA9_Pin GPIO_PIN_9
#define KeyA9_GPIO_Port GPIOB
#define KeyA10_Pin GPIO_PIN_10
#define KeyA10_GPIO_Port GPIOB
#define KeyA11_Pin GPIO_PIN_11
#define KeyA11_GPIO_Port GPIOB
#define KeyA12_Pin GPIO_PIN_12
#define KeyA12_GPIO_Port GPIOB
#define KeyA13_Pin GPIO_PIN_13
#define KeyA13_GPIO_Port GPIOB
#define KeyA14_Pin GPIO_PIN_14
#define KeyA14_GPIO_Port GPIOB
#define KeyA15_Pin GPIO_PIN_15
#define KeyA15_GPIO_Port GPIOB
#define USER_LED_Pin GPIO_PIN_5
#define USER_LED_GPIO_Port GPIOA
#define DEBUG_TX_Pin GPIO_PIN_2
#define DEBUG_TX_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_3
#define DEBUG_RX_GPIO_Port GPIOA
#define USB_POWER_SWITCH_ON_Pin GPIO_PIN_8
#define USB_POWER_SWITCH_ON_GPIO_Port GPIOC
#define USB_OWER_CURRENT_Pin GPIO_PIN_9
#define USB_OWER_CURRENT_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */
#define KEYDATA_MASK (KeyD0_Pin | KeyD1_Pin | KeyD2_Pin | KeyD3_Pin | KeyD4_Pin)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
