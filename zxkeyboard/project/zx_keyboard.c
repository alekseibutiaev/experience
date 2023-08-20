/*
 * zx_keyboard.c
 *
 *  Created on: Nov 15, 2022
 *      Author: butiaev
 */
#include <stdint.h>
#include <stdio.h>
#include "spi.h"
#include "main.h"
#include "zx_keyboard.h"

#define KEY_ADDRESS 8

//extern SPI_HandleTypeDef hspi1;

typedef struct {
  uint8_t treg;
  uint8_t tbit;
  uint8_t lreg;
  uint8_t lbit;
} key_layer_t;

#if defined (DEBUG)
#define LSB 1
#define MSB 0
#endif

#define CSID 0x07 // CAPS_SHIFT register index
#define CSVL 0xFE // CAPS_SHIFT register value 
#define SSID 0x00 // SYMBOL_SHIFT register index
#define SSVL 0xFD // SYMBOL_SHIFT register value 

const key_layer_t cs = {CSID, CSVL & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK};
const key_layer_t ss = {SSID, SSVL & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK};

const key_layer_t layers[256] = {
/*00*/  {0x00, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*02*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*04*/  {0x06, 0xFE & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*A */ {0x00, 0xEF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*B */
/*06*/  {0x07, 0xF7 & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*C */ {0x06, 0xFB & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*D */
/*08*/  {0x05, 0xFB & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*E */ {0x06, 0xF7 & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*F */
/*0A*/  {0x06, 0xEF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*G */ {0x01, 0xEF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*H */
/*0C*/  {0x02, 0xFB & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*I */ {0x01, 0xF7 & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*J */
/*0E*/  {0x01, 0xFB & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*K */ {0x01, 0xFD & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*L */
/*10*/  {0x00, 0xFB & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*M */ {0x00, 0xF7 & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*N */
/*12*/  {0x02, 0xFD & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*O */ {0x02, 0xFE & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*P */
/*14*/  {0x05, 0xFE & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*Q */ {0x05, 0xF7 & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*R */
/*16*/  {0x06, 0xFD & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*S */ {0x05, 0xEF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*T */
/*18*/  {0x02, 0xF7 & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*U */ {0x07, 0xEF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*V */
/*1A*/  {0x05, 0xFD & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*W */ {0x07, 0xFB & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*X */
/*1C*/  {0x02, 0xEF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*Y */ {0x07, 0xFD & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*Z */
/*1E*/  {0x04, 0xFE & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*1 */ {0x04, 0xFD & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*2 */
/*20*/  {0x04, 0xFB & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*3 */ {0x04, 0xF7 & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*4 */
/*DC*/  {0x04, 0xEF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*5 */ {0x03, 0xEF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*6 */
/*24*/  {0x03, 0xF7 & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*7 */ {0x03, 0xFB & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*8 */
/*DC*/  {0x03, 0xFD & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*9 */ {0x03, 0xFE & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*0 */
/*28*/  {0x01, 0xFE & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*EN*/ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*2A*/  {0x03, 0xFE & KEYBIT_MASK, CSID, CSVL & KEYBIT_MASK}, /*BS*/ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*2C*/  {0x00, 0xFE & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*SP*/ {0x01, 0xF7 & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*- */
/*2E*/  {0x01, 0xFD & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*= */ {0x02, 0xEF & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*[ */
/*30*/  {0x02, 0xF7 & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*] */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*32*/  {0x02, 0xFE & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*CR*/ {0x02, 0xFD & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*; */
/*34*/  {0x03, 0xF7 & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*' */ {0x07, 0xFB & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*PO*/
/*36*/  {0x00, 0xF7 & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*. */ {0x00, 0xFB & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*. */
/*38*/  {0x07, 0xEF & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*/ */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*3A*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*3C*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*3E*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*40*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*42*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*44*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*46*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*48*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*4A*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0x00, 0xFE & KEYBIT_MASK, CSID, CSVL & KEYBIT_MASK}, /*BR*/
/*4C*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*4E*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0x03, 0xFB & KEYBIT_MASK, CSID, CSVL & KEYBIT_MASK}, /*AR*/
/*50*/  {0x04, 0xEF & KEYBIT_MASK, CSID, CSVL & KEYBIT_MASK}, /*AL*/ {0x03, 0xEF & KEYBIT_MASK, CSID, CSVL & KEYBIT_MASK}, /*AD*/
/*52*/  {0x03, 0xF7 & KEYBIT_MASK, CSID, CSVL & KEYBIT_MASK}, /*AU*/ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*54*/  {0x07, 0xEF & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*/ */ {0x00, 0xEF & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /** */
/*56*/  {0x01, 0xF7 & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*- */ {0x01, 0xFB & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*+ */
/*58*/  {0x01, 0xFE & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*EN*/ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*5A*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*5C*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*5E*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*60*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*62*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*64*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*66*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*68*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*6A*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*6C*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*6E*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*70*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*72*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*74*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*76*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*78*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*7A*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*7C*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*7E*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*80*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*82*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*84*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*86*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*88*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*8A*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*8C*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*8E*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*90*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*92*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*94*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*96*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*98*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*9A*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*9C*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*9E*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*A0*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*A2*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*A4*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*A6*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*A8*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*AA*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*AC*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*AE*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*B0*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*B2*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*B4*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*B6*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*B8*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*BA*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*BC*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*BE*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*C0*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*C2*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*C4*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*C6*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*C8*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*CA*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*DC*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*CE*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*D0*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*D2*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*D4*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*D6*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*D8*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*DA*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*DC*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*DE*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*E0*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*E2*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*E4*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*E6*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
/*E8*/  {0x04, 0xFE & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*! */ {0x04, 0xFD & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*@ */
/*EA*/  {0x04, 0xFB & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*# */ {0x04, 0xF7 & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*$ */
/*EC*/  {0x04, 0xEF & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*% */ {0x01, 0xEF & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*^ */
/*EE*/  {0x03, 0xEF & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*& */ {0x00, 0xEF & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /** */
/*F0*/  {0x03, 0xFB & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*( */ {0x03, 0xFD & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*} */
/*F2*/  {0x03, 0xFE & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*_ */ {0x01, 0xFB & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*+ */
/*F4*/  {0x06, 0xF7 & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*{ */ {0x06, 0xEF & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*} */
/*F6*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0x06, 0xFD & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*| */
/*F8*/  {0x07, 0xFD & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*  */ {0x02, 0xFE & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*" */
/*FA*/  {0x06, 0xFE & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*  */ {0x05, 0xF7 & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*< */
/*FC*/  {0x00, 0xFB & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*> */ {0x07, 0xF7 & KEYBIT_MASK, SSID, SSVL & KEYBIT_MASK}, /*  */
/*FE*/  {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */ {0xFF, 0xFF & KEYBIT_MASK, 0xFF, 0xFF & KEYBIT_MASK}, /*  */
};// /

uint8_t registers[KEY_ADDRESS] = {0};

static void load_impulse() {
  HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_RESET);
}

static const key_layer_t* get_key_layer(uint8_t key, const key_mode_t* mode, const key_leds_t* leds) {
  if(!layers[0].treg) {
    if(mode->bits.lshift || mode->bits.rshift) { 
      if(KEY_1_EXCLAMATION_MARK <= key && key <= KEY_0_CPARENTHESIS)
        key = key - KEY_1_EXCLAMATION_MARK + KEY_RIGHT_GUI + 1;
      else if(KEY_MINUS_UNDERSCORE <= key && key <= KEY_SLASH_QUESTION)
        key = key - KEY_MINUS_UNDERSCORE + KEY_RIGHT_GUI + (KEY_0_CPARENTHESIS - KEY_1_EXCLAMATION_MARK) + 2;
    }
    else if(leds->leds.num && KEY_KEYPAD_1_END <= key && key <= KEY_KEYPAD_DECIMAL_SEPARATOR_DELETE)
      key = key - KEY_KEYPAD_1_END + KEY_EXSEL + 1;
  }
  printf("key : 0x%02X\n", key);
  return &layers[key];
}

#if defined (DEBUG)
const char* printbin(uint8_t lsb, char* buf, uint8_t value, const char(*a)[8]) {
  sprintf(buf, "%c%c%c%c%c%c%c%c",
    (value & (lsb ? 0x80 : 0x01) ? '_' : (*a)[lsb ? 0 : 7]),
    (value & (lsb ? 0x40 : 0x02) ? '_' : (*a)[lsb ? 1 : 6]),
    (value & (lsb ? 0x20 : 0x04) ? '_' : (*a)[lsb ? 2 : 5]),
    (value & (lsb ? 0x10 : 0x08) ? '_' : (*a)[lsb ? 3 : 4]),
    (value & (lsb ? 0x08 : 0x10) ? '_' : (*a)[lsb ? 4 : 3]),
    (value & (lsb ? 0x04 : 0x20) ? '_' : (*a)[lsb ? 5 : 2]),
    (value & (lsb ? 0x02 : 0x40) ? '_' : (*a)[lsb ? 6 : 1]),
    (value & (lsb ? 0x01 : 0x80) ? '_' : (*a)[lsb ? 7 : 0])
  );
  return buf;
}
#endif

void printbuf(const uint8_t* buf, const uint32_t size) {
  for(uint32_t i = 0; i < size; ++i)
    printf("0x%02X%c", buf[i], ((i + 1) % 16 && size - i != 1 ? ' ' : '\n'));
}

void sendbuf(const uint8_t* buf, const uint32_t size) {
  HAL_SPI_Transmit(&hspi1, (uint8_t*)buf, size, 500);
  load_impulse();
}

void clear() {
  memset(registers, 0xFF, sizeof(registers));
  sendbuf(registers, sizeof(registers));
}

void prepare_keys(const key_receive_t* keys, const key_leds_t* leds) {
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

#define BITBUF 9
#define UNPRESSED 0xFF
  uint8_t registers[KEY_ADDRESS];
  memset(registers, UNPRESSED, sizeof(registers));
  uint8_t key = 0;
  if(keys->data.mod.bits.lctrl || keys->data.mod.bits.rctrl)
    registers[cs.treg] &= cs.tbit;
  if(keys->data.mod.bits.lshift || keys->data.mod.bits.rshift)
    registers[ss.treg] &= ss.tbit;
  for(uint8_t i = 0; i < sizeof(keys->data.keys) && 0 != (key = keys->data.keys[i]); ++i) {
    const key_layer_t* l = get_key_layer(key, &keys->data.mod, leds);
    if(l->treg != UNPRESSED)
      registers[l->treg] &= l->tbit;
    if(l->lreg != UNPRESSED)
      registers[l->lreg] &= l->lbit;
  }
#if defined (DEBUG)
  char buf[BITBUF * 2];
  printf("    01234567    76543210\n");
  for(uint8_t i = 3; i <= 3; --i) {
    static const char symbol[8][8] = {
      {'_', '_', '_', 'B', 'N', 'M', 's', 'b'},
      {'_', '_', '_', 'H', 'J', 'K', 'L', 'e'},
      {'_', '_', '_', 'Y', 'U', 'I', 'O', 'P'},
      {'_', '_', '_', '6', '7', '8', '9', '0'},
      {'_', '_', '_', '5', '4', '3', '2', '1'},
      {'_', '_', '_', 'T', 'R', 'E', 'W', 'Q'},
      {'_', '_', '_', 'G', 'F', 'D', 'S', 'A'},
      {'_', '_', '_', 'V', 'C', 'X', 'Z', 'c'}
    };
    uint8_t j = ~i & 0x07;
    printf("A%02d=%s A%02d=%s\n", 15 - j, printbin(MSB, buf, registers[j], &symbol[j] ),
      15 - i, printbin(LSB, buf + BITBUF, registers[i], &symbol[i]));
  }
  printbuf(registers, sizeof(registers));
#endif
  sendbuf(registers, sizeof(registers));
#undef UNPRESSED
#undef BITBUF
}

#if defined (DEBUG)
#undef MSB
#undef LSB
#endif

