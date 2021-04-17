/*
 * usb_module.c
 *
 *  Created on: Apr 17, 2021
 *      Author: butiaev
 */


#include "usbh_def.h"
#include "usbh_hid.h"


void USBH_HID_EventCallback(USBH_HandleTypeDef *phost)
{
//  printf("all initialized\n");
  if (USBH_HID_GetDeviceType(phost) == HID_KEYBOARD) {
    HID_KEYBD_Info_TypeDef* ki = USBH_HID_GetKeybdInfo(phost);

#if 1
    printf("s = 0x%02X, lc = 0x%02X, ls = 0x%02X, la = 0x%02X, lg = 0x%02X, rc = 0x%02X, rs = 0x%02X, ra = 0x%02X, rg = 0x%02X, k0 = 0x%02X, k1 = 0x%02X, k1 = 0x%02X, k2 = 0x%02X, k3 = 0x%02X, k4 = 0x%02X, k5 = 0x%02X\n",
    (int)ki->state, (int)ki->lctrl, (int)ki->lshift, (int)ki->lalt, (int)ki->lgui, (int)ki->rctrl, (int)ki->rshift, (int)ki->ralt,
    (int)ki->rgui, (int)ki->keys[0], (int)ki->keys[1], (int)ki->keys[2], (int)ki->keys[3], (int)ki->keys[4], (int)ki->keys[5]);
#else
    char key = USBH_HID_GetASCIICode (ki);
    printf("Key Pressed = %c 0x%02X\n", isprint(key) ? key : '.', (int)key);
#endif
  }
}
