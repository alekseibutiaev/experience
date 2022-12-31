/*
 * uart_dbg.h
 *
 *  Created on: Nov 16, 2022
 *      Author: butiaev
 */

#ifndef INC_UART_DBG_H_
#define INC_UART_DBG_H_

struct UART_HandleTypeDef;

void uart_dbg_init(UART_HandleTypeDef* huart);

#endif /* INC_UART_DBG_H_ */
