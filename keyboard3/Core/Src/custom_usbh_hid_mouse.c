/*
 * usbh_hid_mouse.c
 *
 *  Created on: Nov 22, 2022
 *      Author: butiaev
 */

#include <usbh_def.h>
#include "custom_usbh_hid_mouse.h"

USBH_StatusTypeDef USBH_HID_MouseInit(USBH_HandleTypeDef* phost) {
  return usbh_hid_mouse_init(phost);
}

USBH_StatusTypeDef usbh_hid_mouse_init(USBH_HandleTypeDef* phost) {
  return USBH_NOT_SUPPORTED;
}

