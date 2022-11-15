/*
 * usbh_hid_keyboard.c
 *
 *  Created on: Aug 18, 2022
 *      Author: butiaev
 */

#include <string.h>
#include "usbh_hid_keyboard.h"

static keys_callback_t callback = 0;
static key_receive_t keys;
static uint8_t receive[sizeof(keys.buf)];

//static key_transmit_t transmit;

USBH_StatusTypeDef usbh_hid_keyboard_init(USBH_HandleTypeDef *phost) {
  uint32_t i;
  HID_HandleTypeDef* HID_Handle = (HID_HandleTypeDef*)phost->pActiveClass->pData;
  for(i = 0; i < sizeof(receive); ++i)
    receive[i] = 0;
  if (HID_Handle->length > sizeof(receive))
    HID_Handle->length = sizeof(receive);
  HID_Handle->pData = receive;
  USBH_HID_FifoInit(&HID_Handle->fifo, phost->device.Data, HID_QUEUE_SIZE * sizeof(receive));
  return USBH_OK;
}

key_receive_t* usbh_hid_keyboard(USBH_HandleTypeDef *phost) {
  HID_HandleTypeDef* h = (HID_HandleTypeDef*)phost->pActiveClass->pData;
  if(h->length != 0U && h->length == USBH_HID_FifoRead(&h->fifo, &keys.buf, h->length))
    return &keys;
  return 0;
}

USBH_StatusTypeDef usbh_hid_keboard_led(USBH_HandleTypeDef* phost, key_leds_t* leds) {
  return USBH_HID_SetReport(phost, 2, 0, &leds->data, sizeof(leds->data));
}

void set_keys_callback(keys_callback_t keys_callback) {
  callback = keys_callback;
}

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
}
