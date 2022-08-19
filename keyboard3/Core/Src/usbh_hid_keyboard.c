/*
 * usbh_hid_keyboard.c
 *
 *  Created on: Aug 18, 2022
 *      Author: butiaev
 */

#include "usbh_hid_keyboard.h"

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

