/*
 * gpio_ex.h
 *
 *  Created on: Apr 17, 2021
 *      Author: Aleksei
 */

#ifndef INC_GPIO_EX_H_
#define INC_GPIO_EX_H_

#include "stm32f1xx_hal.h"

void HAL_GPIO_SetWord(GPIO_TypeDef *GPIOx, uint16_t data);

#endif /* INC_GPIO_EX_H_ */
