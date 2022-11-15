/*
 * zx_keyboard.h
 *
 *  Created on: Nov 15, 2022
 *      Author: butiaev
 */

#ifndef INC_ZX_KEYBOARD_H_
#define INC_ZX_KEYBOARD_H_

#define SYMBOL_SHIFT 232

#include "usbh_hid_keyboard.h"

void prepare_keys(const key_receive_t* keys, const key_leds_t* leds);

#endif /* INC_ZX_KEYBOARD_H_ */
