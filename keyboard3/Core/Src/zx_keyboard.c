/*
 * zx_keyboard.c
 *
 *  Created on: Nov 15, 2022
 *      Author: butiaev
 */
#include <stdio.h>
#include "main.h"
#include "zx_keyboard.h"

typedef struct {
  uint8_t top;
  uint8_t tbit;
  uint8_t lower;
  uint8_t lbit;
} key_layer_t;

const key_layer_t layers[256] = {
/*00*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*04*/  {0xFD, 0x1E, 0xFF, 0x1F}, /*A */ {0x7F, 0x0F, 0xFF, 0x1F}, /*B */ {0xFE, 0x17, 0xFF, 0x1F}, /*C */ {0xFD, 0x1B, 0xFF, 0x1F}, /*D */
/*08*/  {0xFB, 0x1B, 0xFF, 0x1F}, /*E */ {0xFD, 0x17, 0xFF, 0x1F}, /*F */ {0xFD, 0x0F, 0xFF, 0x1F}, /*G */ {0xBF, 0x0F, 0xFF, 0x1F}, /*H */
/*0C*/  {0xDF, 0x1B, 0xFF, 0x1F}, /*I */ {0xBF, 0x17, 0xFF, 0x1F}, /*J */ {0xBF, 0x1B, 0xFF, 0x1F}, /*K */ {0xBF, 0x1D, 0xFF, 0x1F}, /*L */
/*10*/  {0x7F, 0x1B, 0xFF, 0x1F}, /*M */ {0x7F, 0x17, 0xFF, 0x1F}, /*N */ {0xDF, 0x1D, 0xFF, 0x1F}, /*O */ {0xDF, 0x1E, 0xFF, 0x1F}, /*P */
/*14*/  {0xFB, 0x1E, 0xFF, 0x1F}, /*Q */ {0xFB, 0x17, 0xFF, 0x1F}, /*R */ {0xFD, 0x1D, 0xFF, 0x1F}, /*S */ {0xFB, 0x0F, 0xFF, 0x1F}, /*T */
/*18*/  {0xDF, 0x17, 0xFF, 0x1F}, /*U */ {0xFE, 0x0F, 0xFF, 0x1F}, /*V */ {0xFB, 0x1D, 0xFF, 0x1F}, /*W */ {0xFE, 0x1B, 0xFF, 0x1F}, /*X */
/*1C*/  {0xDF, 0x0F, 0xFF, 0x1F}, /*Y */ {0xFE, 0x1D, 0xFF, 0x1F}, /*Z */ {0xF7, 0x1E, 0xFF, 0x1F}, /*1 */ {0xF7, 0x1D, 0xFF, 0x1F}, /*2 */
/*20*/  {0xF7, 0x1B, 0xFF, 0x1F}, /*3 */ {0xF7, 0x17, 0xFF, 0x1F}, /*4 */ {0xF7, 0x0F, 0xFF, 0x1F}, /*5 */ {0xEF, 0x0F, 0xFF, 0x1F}, /*6 */
/*24*/  {0xEF, 0x17, 0xFF, 0x1F}, /*7 */ {0xEF, 0x1B, 0xFF, 0x1F}, /*8 */ {0xEF, 0x1D, 0xFF, 0x1F}, /*9 */ {0xEF, 0x1E, 0xFF, 0x1F}, /*0 */
/*28*/  {0xBF, 0x1E, 0xFF, 0x1F}, /*EN*/ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*2C*/  {0x7F, 0x1E, 0xFF, 0x1F}, /*SP*/ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*30*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*34*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*38*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFE, 0x1E, 0xFF, 0x1F}, /*CS*/ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*3C*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*40*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*44*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*48*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*4C*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*50*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*54*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*58*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*5C*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*60*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*64*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*68*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*6C*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*70*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*74*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*78*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*7C*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*80*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*84*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*88*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*8C*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*90*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*94*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*98*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*9C*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*A0*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*A4*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*A8*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*AC*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*B0*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*B4*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*B8*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*BC*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*C0*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*C4*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*C8*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*DC*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*D0*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*D4*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*D8*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*DC*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*E0*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*E4*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*E8*/  {0x7F, 0x1D, 0xFF, 0x1F}, /*SS*/ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*EC*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*F0*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*F4*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*F8*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
/*FC*/  {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */ {0xFF, 0x1F, 0xFF, 0x1F}, /*  */
};

uint8_t zx_keyboards[256] = {0};

void printbuf(const uint8_t* buf, const uint32_t size) {
  for(uint32_t i = 0; i < size; ++i)
    printf("0x%02X%c%c", buf[i], (buf[i] == KEYDATA_MASK ? ' ' : '*'), ((i + 1) % 16 ? ' ' : '\n'));
}

void prepare_keys(const key_receive_t* keys, const key_leds_t* leds) {
  static key_receive_t previous = {0};
#if 1
  printf("lc = %d,ls = %d, la = %d, lg = %d, rc = %d, rs = %d, ra = %d, rg = %d, "
    "k0 = 0x%02X, k1 = 0x%02X, k2 = 0x%02X, k3 = 0x%02X, k4 = 0x%02X, k5 = 0x%02X\n",
    (int)keys->data.mod.bits.lctrl, (int)keys->data.mod.bits.lshift,
    (int)keys->data.mod.bits.lalt, (int)keys->data.mod.bits.lgui,
    (int)keys->data.mod.bits.rctrl, (int)keys->data.mod.bits.rshift,
    (int)keys->data.mod.bits.ralt, (int)keys->data.mod.bits.rgui,
    (int)keys->data.keys[0], (int)keys->data.keys[1], (int)keys->data.keys[2],
    (int)keys->data.keys[3], (int)keys->data.keys[4], (int)keys->data.keys[5]);
#endif
  if(keys->data.mod.bits.lshift | keys->data.mod.bits.rshift)
    zx_keyboards[layers[SYMBOL_SHIFT].top] &= layers[SYMBOL_SHIFT].tbit;
  else
    zx_keyboards[layers[SYMBOL_SHIFT].top] |= KEYDATA_MASK;
  for(int i = 0; i < sizeof(keys->data.keys); ++i) {
    if(0 == memchr(previous.data.keys, keys->data.keys[i], sizeof(previous.data.keys)))
      zx_keyboards[layers[keys->data.keys[i]].top] &= layers[keys->data.keys[i]].tbit;
    if(0 == memchr(keys->data.keys, previous.data.keys[i], sizeof(keys->data.keys)))
      zx_keyboards[layers[previous.data.keys[i]].top] |= KEYDATA_MASK;
  }
//  printbuf(zx_keyboards, sizeof(zx_keyboards));
  memcpy(&previous, keys, sizeof(key_receive_t));
}
