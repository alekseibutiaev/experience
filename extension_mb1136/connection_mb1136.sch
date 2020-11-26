EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title ""
Date "2020-11-25"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_02x19_Odd_Even CN2
U 1 1 5FBDFAC2
P 9850 4900
F 0 "CN2" H 9900 6017 50  0000 C CNN
F 1 "Conn_02x19_Odd_Even" H 9900 5926 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x19_P2.54mm_Vertical" H 9850 4900 50  0001 C CNN
F 3 "~" H 9850 4900 50  0001 C CNN
	1    9850 4900
	1    0    0    -1  
$EndComp
Text GLabel 900  4000 0    50   BiDi ~ 0
PC10
Text GLabel 900  4100 0    50   BiDi ~ 0
PC12
Text GLabel 900  4200 0    50   UnSpc ~ 0
VDD
Text GLabel 900  4300 0    50   Input ~ 0
BOOT0
Text GLabel 900  4600 0    50   BiDi ~ 0
PA13
Text GLabel 900  4700 0    50   BiDi ~ 0
PA14
Text GLabel 900  4800 0    50   BiDi ~ 0
PA15
Text GLabel 900  4900 0    50   UnSpc ~ 0
GND
Text GLabel 900  5000 0    50   BiDi ~ 0
PB7
Text GLabel 900  5100 0    50   BiDi ~ 0
PC13
Text GLabel 900  5200 0    50   BiDi ~ 0
PC14
Text GLabel 900  5300 0    50   BiDi ~ 0
PC15
Text GLabel 900  5400 0    50   BiDi ~ 0
PD0
Text GLabel 900  5500 0    50   BiDi ~ 0
PD1
Text GLabel 900  5600 0    50   Input ~ 0
VBAT
Text GLabel 900  5700 0    50   BiDi ~ 0
PC2
Text GLabel 900  5800 0    50   BiDi ~ 0
PC3
$Comp
L Connector_Generic:Conn_01x08 CN3
U 1 1 5FC05FC2
P 4250 2850
F 0 "CN3" H 4330 2842 50  0000 L CNN
F 1 "Conn_01x08" H 4330 2751 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 4250 2850 50  0001 C CNN
F 3 "~" H 4250 2850 50  0001 C CNN
	1    4250 2850
	1    0    0    -1  
$EndComp
Text GLabel 2500 4000 2    50   BiDi ~ 0
PC11
Text GLabel 2500 4100 2    50   BiDi ~ 0
PC11
Text GLabel 2500 4200 2    50   UnSpc ~ 0
E5V
Text GLabel 2500 4300 2    50   UnSpc ~ 0
GND
Text GLabel 2500 4500 2    50   UnSpc ~ 0
IOREF
Text GLabel 2500 4600 2    50   UnSpc ~ 0
RESET
Text GLabel 2500 4700 2    50   UnSpc ~ 0
+3V3
Text GLabel 2500 4800 2    50   UnSpc ~ 0
+5
Text GLabel 2500 4900 2    50   UnSpc ~ 0
GND
Text GLabel 2500 5000 2    50   UnSpc ~ 0
GND
Text GLabel 2500 5100 2    50   UnSpc ~ 0
VIN
Wire Wire Line
	900  4300 1500 4300
Wire Wire Line
	900  5100 1500 5100
Wire Wire Line
	900  5000 1500 5000
Wire Wire Line
	900  4900 1500 4900
Wire Wire Line
	900  4800 1500 4800
Wire Wire Line
	900  4700 1500 4700
Wire Wire Line
	900  4600 1500 4600
Wire Wire Line
	900  4200 1500 4200
Wire Wire Line
	900  4100 1500 4100
Wire Wire Line
	900  4000 1500 4000
Text GLabel 9050 4000 0    50   BiDi ~ 0
PC9
Text GLabel 9050 4100 0    50   BiDi ~ 0
PB8
Text GLabel 9050 4200 0    50   BiDi ~ 0
PB9
Text GLabel 9050 4500 0    50   BiDi ~ 0
PA5
Text GLabel 9050 4600 0    50   BiDi ~ 0
PA6
Text GLabel 9050 4700 0    50   BiDi ~ 0
PA7
Text GLabel 9050 4800 0    50   BiDi ~ 0
PB6
Text GLabel 9050 4900 0    50   BiDi ~ 0
PC7
Text GLabel 9050 5000 0    50   BiDi ~ 0
PA9
Text GLabel 10550 4000 2    50   BiDi ~ 0
PC8
Text GLabel 10550 4100 2    50   BiDi ~ 0
PC6
Text GLabel 10550 4200 2    50   BiDi ~ 0
PC5
Text GLabel 10550 4500 2    50   BiDi ~ 0
PA12
Text GLabel 10550 4600 2    50   BiDi ~ 0
PA11
Text GLabel 10550 4700 2    50   BiDi ~ 0
PB12
Text GLabel 10550 4800 2    50   BiDi ~ 0
PB11
Text GLabel 10550 5000 2    50   BiDi ~ 0
PB2
Text GLabel 10550 5100 2    50   BiDi ~ 0
PB1
Text GLabel 10550 5200 2    50   BiDi ~ 0
PB15
Text GLabel 10550 5300 2    50   BiDi ~ 0
PB14
Text GLabel 10550 5400 2    50   BiDi ~ 0
PB13
Text GLabel 10550 5600 2    50   BiDi ~ 0
PC4
Text GLabel 10550 4300 2    50   UnSpc ~ 0
U5V
Text GLabel 10550 4900 2    50   UnSpc ~ 0
GND
Text GLabel 10550 5500 2    50   UnSpc ~ 0
AGND
Wire Wire Line
	9050 5000 9650 5000
Wire Wire Line
	9050 4900 9650 4900
Wire Wire Line
	9050 4800 9650 4800
Wire Wire Line
	9050 4700 9650 4700
Wire Wire Line
	9050 4600 9650 4600
Wire Wire Line
	9050 4500 9650 4500
Wire Wire Line
	9050 4000 9650 4000
Wire Wire Line
	9050 4100 9650 4100
Wire Wire Line
	9050 4200 9650 4200
Text GLabel 9050 4300 0    50   UnSpc ~ 0
AVDD
Text GLabel 9050 4400 0    50   UnSpc ~ 0
GND
Wire Wire Line
	2000 5100 2500 5100
Wire Wire Line
	2000 5000 2500 5000
Wire Wire Line
	2000 4900 2500 4900
Wire Wire Line
	2000 4800 2500 4800
Wire Wire Line
	2000 4700 2500 4700
Wire Wire Line
	2000 4600 2500 4600
Wire Wire Line
	2000 4500 2500 4500
Wire Wire Line
	2000 4300 2500 4300
Wire Wire Line
	2000 4200 2500 4200
Wire Wire Line
	2000 4100 2500 4100
Wire Wire Line
	2000 4000 2500 4000
Wire Wire Line
	900  5200 1500 5200
Wire Wire Line
	900  5300 1500 5300
Wire Wire Line
	900  5400 1500 5400
Wire Wire Line
	900  5500 1500 5500
Wire Wire Line
	900  5600 1500 5600
Wire Wire Line
	900  5700 1500 5700
Wire Wire Line
	900  5800 1500 5800
$Comp
L Connector_Generic:Conn_02x19_Odd_Even CN1
U 1 1 5FBDC355
P 1700 4900
F 0 "CN1" H 1750 6017 50  0000 C CNN
F 1 "Conn_02x19_Odd_Even" H 1750 5926 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x19_P2.54mm_Vertical" H 1700 4900 50  0001 C CNN
F 3 "~" H 1700 4900 50  0001 C CNN
	1    1700 4900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 CN4
U 1 1 5FC30886
P 4250 3850
F 0 "CN4" H 4330 3842 50  0000 L CNN
F 1 "Conn_01x06" H 4330 3751 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 4250 3850 50  0001 C CNN
F 3 "~" H 4250 3850 50  0001 C CNN
	1    4250 3850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x10 CN6
U 1 1 5FC317A9
P 6700 2900
F 0 "CN6" H 6618 3517 50  0000 C CNN
F 1 "Conn_01x10" H 6618 3426 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 6700 2900 50  0001 C CNN
F 3 "~" H 6700 2900 50  0001 C CNN
	1    6700 2900
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 CN5
U 1 1 5FC42325
P 6750 4500
F 0 "CN5" H 6830 4492 50  0000 L CNN
F 1 "Conn_01x08" H 6830 4401 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 6750 4500 50  0001 C CNN
F 3 "~" H 6750 4500 50  0001 C CNN
	1    6750 4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2000 5300 2500 5300
Wire Wire Line
	2000 5400 2500 5400
Wire Wire Line
	2000 5500 2500 5500
Wire Wire Line
	2000 5600 2500 5600
Wire Wire Line
	2000 5700 2500 5700
Wire Wire Line
	2000 5800 2500 5800
Text GLabel 2500 5300 2    50   BiDi ~ 0
PA0
Text GLabel 2500 5400 2    50   BiDi ~ 0
PA1
Text GLabel 2500 5500 2    50   BiDi ~ 0
PA4
Text GLabel 2500 5600 2    50   BiDi ~ 0
PB0
Text GLabel 2500 5700 2    50   BiDi ~ 0
PC1
Text GLabel 2500 5800 2    50   BiDi ~ 0
PC0
Text GLabel 3700 3650 0    50   BiDi ~ 0
PA0
Text GLabel 3700 3750 0    50   BiDi ~ 0
PA1
Text GLabel 3700 3850 0    50   BiDi ~ 0
PA4
Text GLabel 3700 3950 0    50   BiDi ~ 0
PB0
Text GLabel 3700 4050 0    50   BiDi ~ 0
PC1
Text GLabel 3700 4150 0    50   BiDi ~ 0
PC0
Wire Wire Line
	3700 3650 4050 3650
Wire Wire Line
	3700 3750 4050 3750
Wire Wire Line
	3700 3850 4050 3850
Wire Wire Line
	3700 3950 4050 3950
Wire Wire Line
	3700 4050 4050 4050
Wire Wire Line
	3700 4150 4050 4150
Text GLabel 3650 2650 0    50   UnSpc ~ 0
IOREF
Text GLabel 3650 2750 0    50   UnSpc ~ 0
RESET
Text GLabel 3650 2850 0    50   UnSpc ~ 0
+3V3
Text GLabel 3650 2950 0    50   UnSpc ~ 0
+5
Text GLabel 3650 3050 0    50   UnSpc ~ 0
GND
Text GLabel 3650 3150 0    50   UnSpc ~ 0
GND
Text GLabel 3650 3250 0    50   UnSpc ~ 0
VIN
Wire Wire Line
	3650 2650 4050 2650
Wire Wire Line
	3650 2750 4050 2750
Wire Wire Line
	3650 2850 4050 2850
Wire Wire Line
	3650 2950 4050 2950
Wire Wire Line
	3650 3050 4050 3050
Wire Wire Line
	3650 3150 4050 3150
Wire Wire Line
	3650 3250 4050 3250
Wire Wire Line
	10150 4000 10550 4000
Wire Wire Line
	10150 4100 10550 4100
Wire Wire Line
	10150 4200 10550 4200
Wire Wire Line
	10150 4300 10550 4300
Wire Wire Line
	10150 4500 10550 4500
Wire Wire Line
	10150 4600 10600 4600
Wire Wire Line
	10150 4700 10550 4700
Wire Wire Line
	10150 4800 10550 4800
Wire Wire Line
	10150 4900 10550 4900
Wire Wire Line
	10150 5000 10550 5000
Wire Wire Line
	10150 5100 10550 5100
Wire Wire Line
	10150 5200 10550 5200
Wire Wire Line
	10150 5300 10550 5300
Wire Wire Line
	10150 5400 10550 5400
Wire Wire Line
	10150 5600 10550 5600
Wire Wire Line
	10150 5500 10550 5500
Wire Wire Line
	9050 4300 9650 4300
Wire Wire Line
	9050 4400 9650 4400
Text GLabel 7300 2500 2    50   BiDi ~ 0
PB8
Text GLabel 7300 2600 2    50   BiDi ~ 0
PB9
Text GLabel 7300 2900 2    50   BiDi ~ 0
PA5
Text GLabel 7300 3000 2    50   BiDi ~ 0
PA6
Text GLabel 7300 3100 2    50   BiDi ~ 0
PA7
Text GLabel 7300 3200 2    50   BiDi ~ 0
PB6
Text GLabel 7300 3300 2    50   BiDi ~ 0
PC7
Text GLabel 7300 3400 2    50   BiDi ~ 0
PA9
Text GLabel 7300 2700 2    50   UnSpc ~ 0
AVDD
Text GLabel 7300 2800 2    50   UnSpc ~ 0
GND
Wire Wire Line
	6900 2500 7300 2500
Wire Wire Line
	6900 2600 7300 2600
Wire Wire Line
	6900 2700 7300 2700
Wire Wire Line
	6900 2800 7300 2800
Wire Wire Line
	6900 2900 7300 2900
Wire Wire Line
	6900 3000 7300 3000
Wire Wire Line
	6900 3100 7300 3100
Wire Wire Line
	6900 3200 7300 3200
Wire Wire Line
	6900 3300 7300 3300
Wire Wire Line
	6900 3400 7300 3400
Wire Wire Line
	9050 5100 9650 5100
Wire Wire Line
	9050 5200 9650 5200
Wire Wire Line
	9050 5300 9650 5300
Wire Wire Line
	9050 5400 9650 5400
Wire Wire Line
	9050 5500 9650 5500
Wire Wire Line
	9050 5600 9650 5600
Wire Wire Line
	9050 5700 9650 5700
Wire Wire Line
	9050 5800 9650 5800
Text GLabel 9050 5800 0    50   BiDi ~ 0
PA3
Text GLabel 9050 5700 0    50   BiDi ~ 0
PA2
Text GLabel 9050 5600 0    50   BiDi ~ 0
PA10
Text GLabel 9050 5500 0    50   BiDi ~ 0
PB3
Text GLabel 9050 5400 0    50   BiDi ~ 0
PB5
Text GLabel 9050 5300 0    50   BiDi ~ 0
PB4
Text GLabel 9050 5200 0    50   BiDi ~ 0
PB10
Text GLabel 9050 5100 0    50   BiDi ~ 0
PA8
Wire Wire Line
	7550 4200 6950 4200
Wire Wire Line
	7550 4300 6950 4300
Wire Wire Line
	7550 4400 6950 4400
Wire Wire Line
	7550 4500 6950 4500
Wire Wire Line
	7550 4600 6950 4600
Wire Wire Line
	7550 4700 6950 4700
Wire Wire Line
	7550 4800 6950 4800
Wire Wire Line
	7550 4900 6950 4900
Text GLabel 7550 4900 2    50   BiDi ~ 0
PA3
Text GLabel 7550 4800 2    50   BiDi ~ 0
PA2
Text GLabel 7550 4700 2    50   BiDi ~ 0
PA10
Text GLabel 7550 4600 2    50   BiDi ~ 0
PB3
Text GLabel 7550 4500 2    50   BiDi ~ 0
PB5
Text GLabel 7550 4400 2    50   BiDi ~ 0
PB4
Text GLabel 7550 4300 2    50   BiDi ~ 0
PB10
Text GLabel 7550 4200 2    50   BiDi ~ 0
PA8
$EndSCHEMATC
