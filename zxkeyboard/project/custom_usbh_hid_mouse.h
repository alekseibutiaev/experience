/*
 * usbh_hid_mouse.h
 *
 *  Created on: Nov 22, 2022
 *      Author: butiaev
 */

#ifndef INC_CUSTOM_USBH_HID_MOUSE_H_
#define INC_CUSTOM_USBH_HID_MOUSE_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <usbh_def.h>

USBH_StatusTypeDef usbh_hid_mouse_init(USBH_HandleTypeDef* phost);

#ifdef __cplusplus
}
#endif


#endif /* INC_CUSTOM_USBH_HID_MOUSE_H_ */
