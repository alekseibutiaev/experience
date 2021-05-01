/*
 * gpio_ex.c
 *
 *  Created on: Apr 17, 2021
 *      Author: Aleksei
 */

#include "gpio_ex.h"

typedef union {
  struct {
    uint16_t reset;
    uint16_t set;
  } reg;
  uint32_t data;
} bsrr_t;

void HAL_GPIO_SetWord(GPIO_TypeDef* GPIOx, uint16_t data) {
  bsrr_t reg;
  reg.reg.reset = data ^ 65535;
  reg.reg.set = data;
  GPIOx->BSRR = reg.data;
}
