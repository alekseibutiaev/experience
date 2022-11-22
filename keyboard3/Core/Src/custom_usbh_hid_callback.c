/*
 * custom_usbh_hid_callback.c
 *
 *  Created on: Nov 22, 2022
 *      Author: butiaev
 */
#include "usbh_hid.h"
#include <usbh_def.h>
#include "custom_usbh_hid_keyboard.h"
#include "custom_usbh_hid_mouse.h"

extern keys_callback_t callback;

#if 1
void USBH_HID_EventCallback(USBH_HandleTypeDef* phost) {
  static key_leds_t leds = { 0 };
  if(USBH_HID_GetDeviceType(phost) == HID_KEYBOARD) {
    key_receive_t* kr = usbh_hid_keyboard(phost);
    const uint8_t tmp = leds.data;
    if(0 != memchr(kr->data.keys, KEY_KEYPAD_NUM_LOCK_AND_CLEAR, sizeof(kr->data.keys)))
      leds.leds.num = !leds.leds.num;
    if(0 != memchr(kr->data.keys, KEY_CAPS_LOCK, sizeof(kr->data.keys)))
      leds.leds.caps = !leds.leds.caps;
    if(0 != memchr(kr->data.keys, KEY_SCROLL_LOCK, sizeof(kr->data.keys)))
      leds.leds.scroll = !leds.leds.scroll;
    if(tmp != leds.data)
      usbh_hid_keboard_led(phost, &leds);
    if(callback)
      (*callback)(kr, &leds);
  }
  if(USBH_HID_GetDeviceType(phost) == HID_MOUSE) {
    pos_received_t* pr = usbh_hid_mouse(phost);
/*
    printf("0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X\n ",
        pr->buf[0], pr->buf[2], pr->buf[2], pr->buf[3], pr->buf[4], pr->buf[5], pr->buf[6], pr->buf[7], pr->buf[8], pr->buf[9]);*/
  }
}
#endif

