/*
 * usbh_hid_mouse.c
 *
 *  Created on: Nov 22, 2022
 *      Author: butiaev
 */

#include <string.h>
#include <usbh_def.h>
#include "custom_usbh_hid_mouse.h"

pos_received_t pos;
uint8_t rx_buf[sizeof(pos)];


USBH_StatusTypeDef USBH_HID_MouseInit(USBH_HandleTypeDef* phost) {
  return usbh_hid_mouse_init(phost);
}

USBH_StatusTypeDef usbh_hid_mouse_init(USBH_HandleTypeDef* phost) {
  HID_HandleTypeDef *HID_Handle = (HID_HandleTypeDef *) phost->pActiveClass->pData;
  memset(rx_buf, 0, sizeof(rx_buf));
  if (HID_Handle->length > sizeof(rx_buf))
    HID_Handle->length = sizeof(rx_buf);
  HID_Handle->pData = rx_buf;
  USBH_HID_FifoInit(&HID_Handle->fifo, phost->device.Data, HID_QUEUE_SIZE * sizeof(rx_buf));
  return USBH_OK;
}


pos_received_t* usbh_hid_mouse(USBH_HandleTypeDef* phost) {
  pos_received_t* test = &pos;
  HID_HandleTypeDef* h = (HID_HandleTypeDef *)phost->pActiveClass->pData;
  if (h->length != 0U && h->length == USBH_HID_FifoRead(&h->fifo, &pos.buf, h->length)){
    for(int i = 0; i < sizeof(pos.buf); ++i)
      printf("0x%02X%c", pos.buf[i], (0 != (i + 1) % 16 ? ' ' : '\n' ));
    printf("%d \n", sizeof(pos));
    return &pos;
  }
  return 0;
}