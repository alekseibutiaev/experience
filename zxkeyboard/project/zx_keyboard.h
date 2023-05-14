/*
 * zx_keyboard.h
 *
 *  Created on: Nov 15, 2022
 *      Author: butiaev
 */

#ifndef INC_ZX_KEYBOARD_H_
#define INC_ZX_KEYBOARD_H_

#define KEYBIT_MASK 0xFF

#define SYMBOL_SHIFT 232

#include <custom_usbh_hid_keyboard.h>

#if defined (DEBUG)
const char* printbin(uint8_t lsb, char* buf, uint8_t value, const char(*s)[8]);
#endif
void printbuf(const uint8_t* buf, const uint32_t size);
void sendbuf(const uint8_t* buf, const uint32_t size);
void clear();
void prepare_keys(const key_receive_t* keys, const key_leds_t* leds);

#endif /* INC_ZX_KEYBOARD_H_ */
