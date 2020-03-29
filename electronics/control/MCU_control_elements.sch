EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 950  850  0    50   Input ~ 0
MCU_3.3V
$Comp
L power:GNDD #PWR011
U 1 1 5E5DBF5B
P 1500 1650
F 0 "#PWR011" H 1500 1400 50  0001 C CNN
F 1 "GNDD" H 1504 1495 50  0000 C CNN
F 2 "" H 1500 1650 50  0001 C CNN
F 3 "" H 1500 1650 50  0001 C CNN
	1    1500 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 850  1500 1050
$Comp
L Device:C C6
U 1 1 5E5DC751
P 1750 1400
F 0 "C6" H 1865 1446 50  0000 L CNN
F 1 "1µF/16V" H 1865 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1788 1250 50  0001 C CNN
F 3 "~" H 1750 1400 50  0001 C CNN
	1    1750 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1200 1750 1200
Wire Wire Line
	1750 1200 1750 1250
Wire Wire Line
	1750 1550 1500 1550
Wire Wire Line
	1500 1550 1500 1650
Wire Wire Line
	1500 1550 1500 1350
Connection ~ 1500 1550
$Comp
L Device:R_POT_Dual_Separate RV1
U 1 1 5E5DD8D5
P 1500 1200
F 0 "RV1" H 1431 1246 50  0000 R CNN
F 1 "10k" H 1431 1155 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 1500 1200 50  0001 C CNN
F 3 "~" H 1500 1200 50  0001 C CNN
	1    1500 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR015
U 1 1 5E6A71AF
P 2550 1650
F 0 "#PWR015" H 2550 1400 50  0001 C CNN
F 1 "GNDD" H 2554 1495 50  0000 C CNN
F 2 "" H 2550 1650 50  0001 C CNN
F 3 "" H 2550 1650 50  0001 C CNN
	1    2550 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 850  2550 1050
$Comp
L Device:C C10
U 1 1 5E6A71B6
P 2800 1400
F 0 "C10" H 2915 1446 50  0000 L CNN
F 1 "1µF/16V" H 2915 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2838 1250 50  0001 C CNN
F 3 "~" H 2800 1400 50  0001 C CNN
	1    2800 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1200 2800 1200
Wire Wire Line
	2800 1200 2800 1250
Wire Wire Line
	2800 1550 2550 1550
Wire Wire Line
	2550 1550 2550 1650
Wire Wire Line
	2550 1550 2550 1350
Connection ~ 2550 1550
$Comp
L Device:R_POT_Dual_Separate RV1
U 2 1 5E6A71C2
P 2550 1200
F 0 "RV1" H 2481 1246 50  0000 R CNN
F 1 "10k" H 2481 1155 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2550 1200 50  0001 C CNN
F 3 "~" H 2550 1200 50  0001 C CNN
	2    2550 1200
	1    0    0    -1  
$EndComp
Text HLabel 2800 1200 2    50   Output ~ 0
presence_pot
$Comp
L power:GNDD #PWR018
U 1 1 5E6A84B8
P 3650 1650
F 0 "#PWR018" H 3650 1400 50  0001 C CNN
F 1 "GNDD" H 3654 1495 50  0000 C CNN
F 2 "" H 3650 1650 50  0001 C CNN
F 3 "" H 3650 1650 50  0001 C CNN
	1    3650 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 850  3650 1050
$Comp
L Device:C C12
U 1 1 5E6A84BF
P 3900 1400
F 0 "C12" H 4015 1446 50  0000 L CNN
F 1 "1µF/16V" H 4015 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3938 1250 50  0001 C CNN
F 3 "~" H 3900 1400 50  0001 C CNN
	1    3900 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1200 3900 1200
Wire Wire Line
	3900 1200 3900 1250
Wire Wire Line
	3900 1550 3650 1550
Wire Wire Line
	3650 1550 3650 1650
Wire Wire Line
	3650 1550 3650 1350
Connection ~ 3650 1550
$Comp
L Device:R_POT_Dual_Separate RV2
U 1 1 5E6A84CB
P 3650 1200
F 0 "RV2" H 3581 1246 50  0000 R CNN
F 1 "10k" H 3581 1155 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3650 1200 50  0001 C CNN
F 3 "~" H 3650 1200 50  0001 C CNN
	1    3650 1200
	1    0    0    -1  
$EndComp
Text HLabel 3900 1200 2    50   Output ~ 0
EQ_low_pot
$Comp
L power:GNDD #PWR021
U 1 1 5E6A91E7
P 4650 1650
F 0 "#PWR021" H 4650 1400 50  0001 C CNN
F 1 "GNDD" H 4654 1495 50  0000 C CNN
F 2 "" H 4650 1650 50  0001 C CNN
F 3 "" H 4650 1650 50  0001 C CNN
	1    4650 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 850  4650 1050
$Comp
L Device:C C14
U 1 1 5E6A91EE
P 4900 1400
F 0 "C14" H 5015 1446 50  0000 L CNN
F 1 "1µF/16V" H 5015 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4938 1250 50  0001 C CNN
F 3 "~" H 4900 1400 50  0001 C CNN
	1    4900 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 1200 4900 1200
Wire Wire Line
	4900 1200 4900 1250
Wire Wire Line
	4900 1550 4650 1550
Wire Wire Line
	4650 1550 4650 1650
Wire Wire Line
	4650 1550 4650 1350
Connection ~ 4650 1550
$Comp
L Device:R_POT_Dual_Separate RV2
U 2 1 5E6A91FA
P 4650 1200
F 0 "RV2" H 4581 1246 50  0000 R CNN
F 1 "10k" H 4581 1155 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 4650 1200 50  0001 C CNN
F 3 "~" H 4650 1200 50  0001 C CNN
	2    4650 1200
	1    0    0    -1  
$EndComp
Text HLabel 4900 1200 2    50   Output ~ 0
EQ_low_mid_pot
$Comp
L power:GNDD #PWR024
U 1 1 5E6AA2CA
P 5850 1650
F 0 "#PWR024" H 5850 1400 50  0001 C CNN
F 1 "GNDD" H 5854 1495 50  0000 C CNN
F 2 "" H 5850 1650 50  0001 C CNN
F 3 "" H 5850 1650 50  0001 C CNN
	1    5850 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 850  5850 1050
$Comp
L Device:C C17
U 1 1 5E6AA2D1
P 6100 1400
F 0 "C17" H 6215 1446 50  0000 L CNN
F 1 "1µF/16V" H 6215 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6138 1250 50  0001 C CNN
F 3 "~" H 6100 1400 50  0001 C CNN
	1    6100 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 1200 6100 1200
Wire Wire Line
	6100 1200 6100 1250
Wire Wire Line
	6100 1550 5850 1550
Wire Wire Line
	5850 1550 5850 1650
Wire Wire Line
	5850 1550 5850 1350
Connection ~ 5850 1550
$Comp
L Device:R_POT_Dual_Separate RV3
U 1 1 5E6AA2DD
P 5850 1200
F 0 "RV3" H 5781 1246 50  0000 R CNN
F 1 "10k" H 5781 1155 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 5850 1200 50  0001 C CNN
F 3 "~" H 5850 1200 50  0001 C CNN
	1    5850 1200
	1    0    0    -1  
$EndComp
Text HLabel 6100 1200 2    50   Output ~ 0
EQ_high_mid_pot
$Comp
L power:GNDD #PWR026
U 1 1 5E6AB27E
P 7100 1650
F 0 "#PWR026" H 7100 1400 50  0001 C CNN
F 1 "GNDD" H 7104 1495 50  0000 C CNN
F 2 "" H 7100 1650 50  0001 C CNN
F 3 "" H 7100 1650 50  0001 C CNN
	1    7100 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 850  7100 1050
$Comp
L Device:C C19
U 1 1 5E6AB285
P 7350 1400
F 0 "C19" H 7465 1446 50  0000 L CNN
F 1 "1µF/16V" H 7465 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7388 1250 50  0001 C CNN
F 3 "~" H 7350 1400 50  0001 C CNN
	1    7350 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 1200 7350 1200
Wire Wire Line
	7350 1200 7350 1250
Wire Wire Line
	7350 1550 7100 1550
Wire Wire Line
	7100 1550 7100 1650
Wire Wire Line
	7100 1550 7100 1350
Connection ~ 7100 1550
$Comp
L Device:R_POT_Dual_Separate RV3
U 2 1 5E6AB291
P 7100 1200
F 0 "RV3" H 7031 1246 50  0000 R CNN
F 1 "10k" H 7031 1155 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7100 1200 50  0001 C CNN
F 3 "~" H 7100 1200 50  0001 C CNN
	2    7100 1200
	1    0    0    -1  
$EndComp
Text HLabel 7350 1200 2    50   Output ~ 0
EQ_high_pot
$Comp
L power:GNDD #PWR028
U 1 1 5E6AD4D2
P 8150 1650
F 0 "#PWR028" H 8150 1400 50  0001 C CNN
F 1 "GNDD" H 8154 1495 50  0000 C CNN
F 2 "" H 8150 1650 50  0001 C CNN
F 3 "" H 8150 1650 50  0001 C CNN
	1    8150 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 850  8150 1050
$Comp
L Device:C C21
U 1 1 5E6AD4D9
P 8400 1400
F 0 "C21" H 8515 1446 50  0000 L CNN
F 1 "1µF/16V" H 8515 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8438 1250 50  0001 C CNN
F 3 "~" H 8400 1400 50  0001 C CNN
	1    8400 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 1200 8400 1200
Wire Wire Line
	8400 1200 8400 1250
Wire Wire Line
	8400 1550 8150 1550
Wire Wire Line
	8150 1550 8150 1650
Wire Wire Line
	8150 1550 8150 1350
Connection ~ 8150 1550
$Comp
L Device:R_POT_Dual_Separate RV4
U 1 1 5E6AD4E5
P 8150 1200
F 0 "RV4" H 8081 1246 50  0000 R CNN
F 1 "10k" H 8081 1155 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 8150 1200 50  0001 C CNN
F 3 "~" H 8150 1200 50  0001 C CNN
	1    8150 1200
	1    0    0    -1  
$EndComp
Text HLabel 8400 1200 2    50   Output ~ 0
comp_ratio_pot
Wire Wire Line
	9300 850  9300 1050
Text HLabel 9550 1200 2    50   Output ~ 0
comp_threshold_pot
$Comp
L Device:R_POT_Dual_Separate RV4
U 2 1 5E6AE8B0
P 9300 1200
F 0 "RV4" H 9231 1246 50  0000 R CNN
F 1 "10k" H 9231 1155 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 9300 1200 50  0001 C CNN
F 3 "~" H 9300 1200 50  0001 C CNN
	2    9300 1200
	1    0    0    -1  
$EndComp
Connection ~ 9300 1550
Wire Wire Line
	9300 1550 9300 1350
Wire Wire Line
	9300 1550 9300 1650
Wire Wire Line
	9550 1550 9300 1550
Wire Wire Line
	9550 1200 9550 1250
Wire Wire Line
	9450 1200 9550 1200
$Comp
L Device:C C22
U 1 1 5E6AE8A4
P 9550 1400
F 0 "C22" H 9665 1446 50  0000 L CNN
F 1 "1µF/16V" H 9665 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9588 1250 50  0001 C CNN
F 3 "~" H 9550 1400 50  0001 C CNN
	1    9550 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR029
U 1 1 5E6AE89D
P 9300 1650
F 0 "#PWR029" H 9300 1400 50  0001 C CNN
F 1 "GNDD" H 9304 1495 50  0000 C CNN
F 2 "" H 9300 1650 50  0001 C CNN
F 3 "" H 9300 1650 50  0001 C CNN
	1    9300 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 850  2550 850 
Connection ~ 1500 850 
Wire Wire Line
	2550 850  3650 850 
Connection ~ 2550 850 
Wire Wire Line
	3650 850  4650 850 
Connection ~ 3650 850 
Wire Wire Line
	4650 850  5850 850 
Connection ~ 4650 850 
Wire Wire Line
	5850 850  7100 850 
Connection ~ 5850 850 
Wire Wire Line
	7100 850  8150 850 
Connection ~ 7100 850 
Wire Wire Line
	8150 850  9300 850 
Connection ~ 8150 850 
Wire Wire Line
	950  850  1100 850 
$Comp
L power:GNDD #PWR012
U 1 1 5E6BEC70
P 1500 2900
F 0 "#PWR012" H 1500 2650 50  0001 C CNN
F 1 "GNDD" H 1504 2745 50  0000 C CNN
F 2 "" H 1500 2900 50  0001 C CNN
F 3 "" H 1500 2900 50  0001 C CNN
	1    1500 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2100 1500 2300
$Comp
L Device:C C7
U 1 1 5E6BEC77
P 1750 2650
F 0 "C7" H 1865 2696 50  0000 L CNN
F 1 "1µF/16V" H 1865 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1788 2500 50  0001 C CNN
F 3 "~" H 1750 2650 50  0001 C CNN
	1    1750 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2450 1750 2450
Wire Wire Line
	1750 2450 1750 2500
Wire Wire Line
	1750 2800 1500 2800
Wire Wire Line
	1500 2800 1500 2900
Wire Wire Line
	1500 2800 1500 2600
Connection ~ 1500 2800
$Comp
L Device:R_POT_Dual_Separate RV5
U 1 1 5E6BEC83
P 1500 2450
F 0 "RV5" H 1431 2496 50  0000 R CNN
F 1 "10k" H 1431 2405 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 1500 2450 50  0001 C CNN
F 3 "~" H 1500 2450 50  0001 C CNN
	1    1500 2450
	1    0    0    -1  
$EndComp
Text HLabel 1750 2450 2    50   Output ~ 0
overdrive_gain_pot
$Comp
L power:GNDD #PWR017
U 1 1 5E6C0646
P 2800 2900
F 0 "#PWR017" H 2800 2650 50  0001 C CNN
F 1 "GNDD" H 2804 2745 50  0000 C CNN
F 2 "" H 2800 2900 50  0001 C CNN
F 3 "" H 2800 2900 50  0001 C CNN
	1    2800 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2100 2800 2300
$Comp
L Device:C C11
U 1 1 5E6C064D
P 3050 2650
F 0 "C11" H 3165 2696 50  0000 L CNN
F 1 "1µF/16V" H 3165 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3088 2500 50  0001 C CNN
F 3 "~" H 3050 2650 50  0001 C CNN
	1    3050 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 2450 3050 2450
Wire Wire Line
	3050 2450 3050 2500
Wire Wire Line
	3050 2800 2800 2800
Wire Wire Line
	2800 2800 2800 2900
Wire Wire Line
	2800 2800 2800 2600
Connection ~ 2800 2800
$Comp
L Device:R_POT_Dual_Separate RV5
U 2 1 5E6C0659
P 2800 2450
F 0 "RV5" H 2731 2496 50  0000 R CNN
F 1 "10k" H 2731 2405 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2800 2450 50  0001 C CNN
F 3 "~" H 2800 2450 50  0001 C CNN
	2    2800 2450
	1    0    0    -1  
$EndComp
Text HLabel 3050 2450 2    50   Output ~ 0
overdrive_tone_pot
$Comp
L power:GNDD #PWR019
U 1 1 5E6C2B4D
P 4100 2900
F 0 "#PWR019" H 4100 2650 50  0001 C CNN
F 1 "GNDD" H 4104 2745 50  0000 C CNN
F 2 "" H 4100 2900 50  0001 C CNN
F 3 "" H 4100 2900 50  0001 C CNN
	1    4100 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 2100 4100 2300
$Comp
L Device:C C13
U 1 1 5E6C2B54
P 4350 2650
F 0 "C13" H 4465 2696 50  0000 L CNN
F 1 "1µF/16V" H 4465 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4388 2500 50  0001 C CNN
F 3 "~" H 4350 2650 50  0001 C CNN
	1    4350 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2450 4350 2450
Wire Wire Line
	4350 2450 4350 2500
Wire Wire Line
	4350 2800 4100 2800
Wire Wire Line
	4100 2800 4100 2900
Wire Wire Line
	4100 2800 4100 2600
Connection ~ 4100 2800
$Comp
L Device:R_POT_Dual_Separate RV6
U 1 1 5E6C2B60
P 4100 2450
F 0 "RV6" H 4031 2496 50  0000 R CNN
F 1 "10k" H 4031 2405 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 4100 2450 50  0001 C CNN
F 3 "~" H 4100 2450 50  0001 C CNN
	1    4100 2450
	1    0    0    -1  
$EndComp
Text HLabel 4350 2450 2    50   Output ~ 0
octaver_down_pot
$Comp
L power:GNDD #PWR023
U 1 1 5E6C502B
P 5350 2900
F 0 "#PWR023" H 5350 2650 50  0001 C CNN
F 1 "GNDD" H 5354 2745 50  0000 C CNN
F 2 "" H 5350 2900 50  0001 C CNN
F 3 "" H 5350 2900 50  0001 C CNN
	1    5350 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2100 5350 2300
$Comp
L Device:C C16
U 1 1 5E6C5032
P 5600 2650
F 0 "C16" H 5715 2696 50  0000 L CNN
F 1 "1µF/16V" H 5715 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5638 2500 50  0001 C CNN
F 3 "~" H 5600 2650 50  0001 C CNN
	1    5600 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2450 5600 2450
Wire Wire Line
	5600 2450 5600 2500
Wire Wire Line
	5600 2800 5350 2800
Wire Wire Line
	5350 2800 5350 2900
Wire Wire Line
	5350 2800 5350 2600
Connection ~ 5350 2800
$Comp
L Device:R_POT_Dual_Separate RV6
U 2 1 5E6C503E
P 5350 2450
F 0 "RV6" H 5281 2496 50  0000 R CNN
F 1 "10k" H 5281 2405 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 5350 2450 50  0001 C CNN
F 3 "~" H 5350 2450 50  0001 C CNN
	2    5350 2450
	1    0    0    -1  
$EndComp
Text HLabel 5600 2450 2    50   Output ~ 0
octaver_up_pot
$Comp
L power:GNDD #PWR025
U 1 1 5E6C891D
P 6550 2900
F 0 "#PWR025" H 6550 2650 50  0001 C CNN
F 1 "GNDD" H 6554 2745 50  0000 C CNN
F 2 "" H 6550 2900 50  0001 C CNN
F 3 "" H 6550 2900 50  0001 C CNN
	1    6550 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 2100 6550 2300
$Comp
L Device:C C18
U 1 1 5E6C8924
P 6800 2650
F 0 "C18" H 6915 2696 50  0000 L CNN
F 1 "1µF/16V" H 6915 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6838 2500 50  0001 C CNN
F 3 "~" H 6800 2650 50  0001 C CNN
	1    6800 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2450 6800 2450
Wire Wire Line
	6800 2450 6800 2500
Wire Wire Line
	6800 2800 6550 2800
Wire Wire Line
	6550 2800 6550 2900
Wire Wire Line
	6550 2800 6550 2600
Connection ~ 6550 2800
$Comp
L Device:R_POT_Dual_Separate RV7
U 1 1 5E6C8930
P 6550 2450
F 0 "RV7" H 6481 2496 50  0000 R CNN
F 1 "10k" H 6481 2405 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 6550 2450 50  0001 C CNN
F 3 "~" H 6550 2450 50  0001 C CNN
	1    6550 2450
	1    0    0    -1  
$EndComp
Text HLabel 6800 2450 2    50   Output ~ 0
delay_vol_pot
$Comp
L power:GNDD #PWR027
U 1 1 5E6CD854
P 7650 2900
F 0 "#PWR027" H 7650 2650 50  0001 C CNN
F 1 "GNDD" H 7654 2745 50  0000 C CNN
F 2 "" H 7650 2900 50  0001 C CNN
F 3 "" H 7650 2900 50  0001 C CNN
	1    7650 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2100 7650 2300
$Comp
L Device:C C20
U 1 1 5E6CD85B
P 7900 2650
F 0 "C20" H 8015 2696 50  0000 L CNN
F 1 "1µF/16V" H 8015 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7938 2500 50  0001 C CNN
F 3 "~" H 7900 2650 50  0001 C CNN
	1    7900 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 2450 7900 2450
Wire Wire Line
	7900 2450 7900 2500
Wire Wire Line
	7900 2800 7650 2800
Wire Wire Line
	7650 2800 7650 2900
Wire Wire Line
	7650 2800 7650 2600
Connection ~ 7650 2800
$Comp
L Device:R_POT_Dual_Separate RV7
U 2 1 5E6CD867
P 7650 2450
F 0 "RV7" H 7581 2496 50  0000 R CNN
F 1 "10k" H 7581 2405 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7650 2450 50  0001 C CNN
F 3 "~" H 7650 2450 50  0001 C CNN
	2    7650 2450
	1    0    0    -1  
$EndComp
Text HLabel 7900 2450 2    50   Output ~ 0
reverb_vol_pot
Wire Wire Line
	1100 850  1100 2100
Wire Wire Line
	1100 2100 1500 2100
Connection ~ 1100 850 
Wire Wire Line
	1100 850  1500 850 
Connection ~ 1500 2100
Wire Wire Line
	1500 2100 2800 2100
Wire Wire Line
	2800 2100 4100 2100
Connection ~ 2800 2100
Wire Wire Line
	4100 2100 5350 2100
Connection ~ 4100 2100
Wire Wire Line
	5350 2100 6550 2100
Connection ~ 5350 2100
Wire Wire Line
	6550 2100 7650 2100
Connection ~ 6550 2100
$Comp
L bass_amplifier:SW_SPST_X3 SW1
U 1 1 5E6F51A5
P 1500 4500
F 0 "SW1" V 1546 4412 50  0000 R CNN
F 1 "SW_SPST_X3" V 1455 4412 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 1500 4500 50  0001 C CNN
F 3 "~" H 1500 4500 50  0001 C CNN
	1    1500 4500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5E6FD5E4
P 1500 3950
F 0 "R2" H 1570 3996 50  0000 L CNN
F 1 "10k" H 1570 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1430 3950 50  0001 C CNN
F 3 "~" H 1500 3950 50  0001 C CNN
	1    1500 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5E7042B6
P 1950 4200
F 0 "R3" V 1743 4200 50  0000 C CNN
F 1 "10k" V 1834 4200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1880 4200 50  0001 C CNN
F 3 "~" H 1950 4200 50  0001 C CNN
	1    1950 4200
	0    1    1    0   
$EndComp
$Comp
L bass_amplifier:74HC14 U3
U 1 1 5E705CAD
P 2950 4200
F 0 "U3" H 3175 4515 50  0000 C CNN
F 1 "74HC14" H 3175 4424 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 2950 4200 50  0001 C CNN
F 3 "" H 2950 4200 50  0001 C CNN
	1    2950 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 5300 1100 3650
Connection ~ 1100 2100
Wire Wire Line
	1100 3650 1500 3650
Wire Wire Line
	1500 3650 1500 3800
Connection ~ 1100 3650
Wire Wire Line
	1100 3650 1100 2100
Wire Wire Line
	1500 4100 1500 4200
Wire Wire Line
	1500 4200 1800 4200
Connection ~ 1500 4200
Wire Wire Line
	1500 4200 1500 4300
Wire Wire Line
	1500 4700 1500 4800
Wire Wire Line
	2450 4600 2450 5300
Wire Wire Line
	1100 5300 2450 5300
Text HLabel 3750 4200 2    50   Output ~ 0
mute_sw
Wire Wire Line
	3600 4200 3750 4200
$Comp
L bass_amplifier:SW_SPST_X3 SW1
U 2 1 5E74F9D2
P 4400 4500
F 0 "SW1" V 4446 4412 50  0000 R CNN
F 1 "SW_SPST_X3" V 4355 4412 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 4400 4500 50  0001 C CNN
F 3 "~" H 4400 4500 50  0001 C CNN
	2    4400 4500
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDD #PWR020
U 1 1 5E74F9D8
P 4400 4800
F 0 "#PWR020" H 4400 4550 50  0001 C CNN
F 1 "GNDD" H 4404 4645 50  0000 C CNN
F 2 "" H 4400 4800 50  0001 C CNN
F 3 "" H 4400 4800 50  0001 C CNN
	1    4400 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5E74F9DE
P 4400 3950
F 0 "R4" H 4470 3996 50  0000 L CNN
F 1 "10k" H 4470 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4330 3950 50  0001 C CNN
F 3 "~" H 4400 3950 50  0001 C CNN
	1    4400 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5E74F9E4
P 4850 4200
F 0 "R5" V 4643 4200 50  0000 C CNN
F 1 "10k" V 4734 4200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4780 4200 50  0001 C CNN
F 3 "~" H 4850 4200 50  0001 C CNN
	1    4850 4200
	0    1    1    0   
$EndComp
$Comp
L bass_amplifier:74HC14 U3
U 2 1 5E74F9EA
P 5650 4200
F 0 "U3" H 5875 4515 50  0000 C CNN
F 1 "74HC14" H 5875 4424 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 5650 4200 50  0001 C CNN
F 3 "" H 5650 4200 50  0001 C CNN
	2    5650 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 3650 4400 3800
Wire Wire Line
	4400 4100 4400 4200
Wire Wire Line
	4400 4200 4700 4200
Connection ~ 4400 4200
Wire Wire Line
	4400 4200 4400 4300
Wire Wire Line
	4400 4700 4400 4800
Wire Wire Line
	5000 4200 5200 4200
Text HLabel 6450 4200 2    50   Output ~ 0
delay_tap_button
Wire Wire Line
	6300 4200 6450 4200
Wire Wire Line
	4400 3650 1500 3650
Connection ~ 1500 3650
Text HLabel 1750 1200 2    50   Output ~ 0
contour_pot
$Comp
L Device:C C15
U 1 1 5E602ABB
P 5200 4400
F 0 "C15" H 5315 4446 50  0000 L CNN
F 1 "0.1µF/25V" H 5315 4355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5238 4250 50  0001 C CNN
F 3 "~" H 5200 4400 50  0001 C CNN
	1    5200 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR022
U 1 1 5E60412F
P 5200 4600
F 0 "#PWR022" H 5200 4350 50  0001 C CNN
F 1 "GNDD" H 5204 4445 50  0000 C CNN
F 2 "" H 5200 4600 50  0001 C CNN
F 3 "" H 5200 4600 50  0001 C CNN
	1    5200 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 4550 5200 4600
Wire Wire Line
	5200 4250 5200 4200
Connection ~ 5200 4200
Wire Wire Line
	5200 4200 5450 4200
Wire Wire Line
	2100 4200 2200 4200
$Comp
L Device:C C8
U 1 1 5E60F58C
P 2200 4400
F 0 "C8" H 2315 4446 50  0000 L CNN
F 1 "0.1µF/25V" H 2315 4355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2238 4250 50  0001 C CNN
F 3 "~" H 2200 4400 50  0001 C CNN
	1    2200 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 4500 2350 4600
Wire Wire Line
	2350 4600 2200 4600
Wire Wire Line
	2200 4250 2200 4200
Connection ~ 2200 4200
Wire Wire Line
	2200 4200 2750 4200
Wire Wire Line
	2350 4500 2750 4500
Wire Wire Line
	2450 4600 2600 4600
$Comp
L power:GNDD #PWR016
U 1 1 5E6AC4D7
P 2600 5000
AR Path="/5E5D9B7F/5E5DB240/5E6AC4D7" Ref="#PWR016"  Part="1" 
AR Path="/5E5D9B7F/5E6AC4D7" Ref="#PWR?"  Part="1" 
F 0 "#PWR016" H 2600 4750 50  0001 C CNN
F 1 "GNDD" H 2604 4845 50  0000 C CNN
F 2 "" H 2600 5000 50  0001 C CNN
F 3 "" H 2600 5000 50  0001 C CNN
	1    2600 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 4950 2600 5000
$Comp
L Device:C C?
U 1 1 5E6AC4DE
P 2600 4800
AR Path="/5E5D9B7F/5E6AC4DE" Ref="C?"  Part="1" 
AR Path="/5E5D9B7F/5E5DB240/5E6AC4DE" Ref="C9"  Part="1" 
F 0 "C9" H 2715 4846 50  0000 L CNN
F 1 "1µF/10V/UL ESR" H 2715 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2638 4650 50  0001 C CNN
F 3 "~" H 2600 4800 50  0001 C CNN
	1    2600 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 4650 2600 4600
Connection ~ 2600 4600
Wire Wire Line
	2600 4600 2750 4600
Wire Wire Line
	2200 4650 2200 4600
Wire Wire Line
	2200 4550 2200 4600
Connection ~ 2200 4600
$Comp
L power:GNDD #PWR0101
U 1 1 5E6A4DEF
P 2200 4650
AR Path="/5E5D9B7F/5E5DB240/5E6A4DEF" Ref="#PWR0101"  Part="1" 
AR Path="/5E5D9B7F/5E6A4DEF" Ref="#PWR?"  Part="1" 
F 0 "#PWR0101" H 2200 4400 50  0001 C CNN
F 1 "GNDD" H 2204 4495 50  0000 C CNN
F 2 "" H 2200 4650 50  0001 C CNN
F 3 "" H 2200 4650 50  0001 C CNN
	1    2200 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0102
U 1 1 5E6ACD46
P 1500 4800
AR Path="/5E5D9B7F/5E5DB240/5E6ACD46" Ref="#PWR0102"  Part="1" 
AR Path="/5E5D9B7F/5E6ACD46" Ref="#PWR?"  Part="1" 
F 0 "#PWR0102" H 1500 4550 50  0001 C CNN
F 1 "GNDD" H 1504 4645 50  0000 C CNN
F 2 "" H 1500 4800 50  0001 C CNN
F 3 "" H 1500 4800 50  0001 C CNN
	1    1500 4800
	1    0    0    -1  
$EndComp
$EndSCHEMATC