#include "interupt.h"

static const uint32_t min = 100;
static const uint32_t max = 2000;
static const uint32_t step = 100;

static uint32_t delay = 1000;

static void increase_delay() {
  if(delay < max)
    delay += step;
}

static void decrease_delay() {
  if(delay > min)
    delay -= step;
}

uint32_t get_delay() {
  return delay;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == 1)
    increase_delay();
  else
    decrease_delay();
  return;
}
