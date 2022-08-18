/*
 * usb_module.c
 *
 *  Created on: Apr 17, 2021
 *      Author: butiaev
 */


#include "usbh_def.h"
#include "usbh_hid.h"
#include "usbh_hid_keyboard.h"



key_leds_t leds;

int find_key(key_receive_t* kr, uint8_t value) {
  for(int i = 0; i < sizeof(kr->data.keys); ++i)
    if(kr->data.keys[ i ] == value)
      return 1;
  return 0;
}

void USBH_HID_EventCallback(USBH_HandleTypeDef* phost) {
  if (USBH_HID_GetDeviceType(phost) == HID_KEYBOARD) {
    key_receive_t* kr = usbh_hid_keyboard(phost);
    printf(
      "lc = 0x%02X, ls = 0x%02X, la = 0x%02X, lg = 0x%02X, "
      "rc = 0x%02X, rs = 0x%02X, ra = 0x%02X, rg = 0x%02X, "
      "k0 = 0x%02X, k1 = 0x%02X, k2 = 0x%02X, "
      "k3 = 0x%02X, k4 = 0x%02X, k5 = 0x%02X\n",
    (int)kr->data.lctrl, (int)kr->data.lshift, (int)kr->data.lalt, (int)kr->data.lgui,
    (int)kr->data.rctrl, (int)kr->data.rshift, (int)kr->data.ralt, (int)kr->data.rgui,
    (int)kr->data.keys[0], (int)kr->data.keys[1], (int)kr->data.keys[2],
    (int)kr->data.keys[3], (int)kr->data.keys[4], (int)kr->data.keys[5]);
    uint8_t tmp = leds.data;
    leds.leds.num = find_key(kr, KEY_KEYPAD_NUM_LOCK_AND_CLEAR) ? !leds.leds.num : leds.leds.num;
    leds.leds.caps = find_key(kr, KEY_CAPS_LOCK) ? !leds.leds.caps : leds.leds.caps;
    leds.leds.scroll = find_key(kr, KEY_SCROLL_LOCK) ? !leds.leds.scroll : leds.leds.scroll;
    if(leds.data != tmp)
      usbh_hid_keboard_led(phost, &leds);
  }
}
