/*
 * usbh_hid_mouse.h
 *
 *  Created on: Nov 22, 2022
 *      Author: butiaev
 */

#ifndef INC_CUSTOM_USBH_HID_MOUSE_H_
#define INC_CUSTOM_USBH_HID_MOUSE_H_

#include "usbh_hid.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
  struct {
    union {
      struct {
        uint8_t left : 1;
        uint8_t right : 1;
        uint8_t middle : 1;
        uint8_t specific : 5;
      } bits;
      uint8_t byte;
    } buttons;
    uint8_t x;
    uint8_t y;
    uint8_t specific[5];
  } data;
  uint8_t buf[8];
} pos_received_t;

USBH_StatusTypeDef usbh_hid_mouse_init(USBH_HandleTypeDef* phost);
pos_received_t* usbh_hid_mouse(USBH_HandleTypeDef* phost);

#ifdef __cplusplus
}
#endif


#endif /* INC_CUSTOM_USBH_HID_MOUSE_H_ */
