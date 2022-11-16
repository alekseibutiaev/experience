/*
 * uart_dbg.c
 *
 *  Created on: Nov 16, 2022
 *      Author: butiaev
 */

#include "stm32f1xx_hal.h"

#include <errno.h>
#include <stdio.h>

#include "uart_dbg.h"

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

UART_HandleTypeDef* port;

void uart_dbg_init(UART_HandleTypeDef* huart) {
  port = huart;
  /* Disable I/O buffering for STDOUT stream, so that
   * chars are sent out as soon as they are printed. */
  setvbuf(stdout, NULL, _IONBF, 0);
}

int _write(int fd, char* ptr, int len) {
  if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
    HAL_StatusTypeDef hstatus = HAL_UART_Transmit(port, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    if (hstatus == HAL_OK)
      return len;
    else
      return EIO;
  }
  errno = EBADF;
  return -1;
}

int _read(int fd, char* ptr, int len) {
  if (fd == STDIN_FILENO) {
    HAL_StatusTypeDef hstatus = HAL_UART_Receive(port, (uint8_t *) ptr, 1, HAL_MAX_DELAY);
    if (hstatus == HAL_OK)
      return 1;
    else
      return EIO;
  }
  errno = EBADF;
  return -1;
}
