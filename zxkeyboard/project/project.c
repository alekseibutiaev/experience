#include "main.h"
#include "gpio.h"
#include "usb_host.h"
#include "usart.h"

#include "usbh_hid.h"
#include "uart_dbg.h"
#include "project.h"
#include "project.h"
#include "custom_usbh_hid_keyboard.h"
#include "zx_keyboard.h"

#define USB_PERIOD 1024

void init() {
  uart_dbg_init(&huart2);
  printf("all initialized\n");
  set_keys_callback(&prepare_keys);
}

void process() {
  static uint32_t counter = 0;
  if(0 == counter++ % USB_PERIOD)
    MX_USB_HOST_Process();
}
