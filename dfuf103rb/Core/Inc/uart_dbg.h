/*
 * uart_dbg.h
 *
 *  Created on: Nov 16, 2022
 *      Author: butiaev
 */

#ifndef INC_UART_DBG_H_
#define INC_UART_DBG_H_

#ifdef UART_DEBUG

struct UART_HandleTypeDef;

void uart_dbg_init(UART_HandleTypeDef* huart);

#endif /*UART_DEBUG*/

#endif /* INC_UART_DBG_H_ */
