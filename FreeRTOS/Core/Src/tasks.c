/*
 * tasks.c
 *
 *  Created on: Nov 19, 2022
 *      Author: butiaev
 */

#include <cmsis_os.h>
#include "main.h"

void task_ds01(void *argument) {
  for(;;) {
    HAL_GPIO_TogglePin(GPIOB, DS1_Pin);
    osDelay(1000);
  }
}

void task_ds02(void *argument) {
  for(;;) {
    HAL_GPIO_TogglePin(GPIOB, DS2_Pin);
    osDelay(2000);
  }
}
