/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define BOARD_TYPE NUCLEO
#define LOAD_Pin GPIO_PIN_4
#define LOAD_GPIO_Port GPIOA
#define CLEAR_Pin GPIO_PIN_6
#define CLEAR_GPIO_Port GPIOA
#if defined(NUCLEO)
  #define USB_OWER_CURRENT_Pin GPIO_PIN_9
  #define USB_OWER_CURRENT_GPIO_Port GPIOC
  #define USB_POWER_SWITCH_ON_Pin GPIO_PIN_8
  #define USB_POWER_SWITCH_ON_GPIO_Port GPIOC
#else
#define USB_OWER_CURRENT_Pin GPIO_PIN_8
#define USB_OWER_CURRENT_GPIO_Port GPIOC
#define USB_POWER_SWITCH_ON_Pin GPIO_PIN_9
#define USB_POWER_SWITCH_ON_GPIO_Port GPIOC
#endif

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
