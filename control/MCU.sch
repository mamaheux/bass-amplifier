EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L bass_amplifier:Teensy_LC U1
U 1 1 5E5D9C58
P 3000 1400
F 0 "U1" H 3700 1565 50  0000 C CNN
F 1 "Teensy_LC" H 3700 1474 50  0000 C CNN
F 2 "bass_amplifier:Teensy_LC" H 3000 1400 50  0001 C CNN
F 3 "" H 3000 1400 50  0001 C CNN
	1    3000 1400
	1    0    0    -1  
$EndComp
$Comp
L bass_amplifier:MCP3208 U2
U 1 1 5E747D2B
P 8700 1600
F 0 "U2" H 8875 1675 50  0000 C CNN
F 1 "MCP3208" H 8875 1584 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 8700 1600 50  0001 C CNN
F 3 "" H 8700 1600 50  0001 C CNN
	1    8700 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2800 2450 2800
Wire Wire Line
	2600 2700 2450 2700
Wire Wire Line
	2600 2600 2450 2600
Wire Wire Line
	4800 2800 4900 2800
Text Label 4900 2800 0    50   ~ 0
ADC_SCK
Text Label 9550 2050 0    50   ~ 0
ADC_SCK
Wire Wire Line
	9550 2050 9450 2050
Wire Wire Line
	9450 2150 9550 2150
Wire Wire Line
	9450 2250 9550 2250
Wire Wire Line
	9450 2350 9550 2350
Wire Wire Line
	4800 1700 5100 1700
Wire Wire Line
	4800 2000 5350 2000
Wire Wire Line
	4800 2100 5350 2100
Wire Wire Line
	4800 2200 5350 2200
Wire Wire Line
	4800 2300 5350 2300
Wire Wire Line
	4800 2400 5350 2400
Wire Wire Line
	4800 2500 5350 2500
Wire Wire Line
	4800 2600 5350 2600
Text Label 4900 2700 0    50   ~ 0
ADC_CS
Text Label 9550 2350 0    50   ~ 0
ADC_CS
Text Label 2450 2700 2    50   ~ 0
ADC_MOSI
Text Label 9550 2250 0    50   ~ 0
ADC_MOSI
Text Label 2450 2800 2    50   ~ 0
ADC_MISO
Text Label 9550 2150 0    50   ~ 0
ADC_MISO
Wire Wire Line
	8300 1750 7400 1750
Wire Wire Line
	7400 1850 8300 1850
Wire Wire Line
	8300 1950 7400 1950
Wire Wire Line
	7400 2050 8300 2050
Wire Wire Line
	4800 1500 4950 1500
Wire Wire Line
	4950 1500 4950 1200
Text GLabel 4950 1200 0    50   Input ~ 0
D+5V
$Comp
L power:GNDD #PWR?
U 1 1 5E77C2E4
P 2000 1500
AR Path="/5E5D9B7F/5E5DB240/5E77C2E4" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E77C2E4" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 2000 1250 50  0001 C CNN
F 1 "GNDD" H 2004 1345 50  0000 C CNN
F 2 "" H 2000 1500 50  0001 C CNN
F 3 "" H 2000 1500 50  0001 C CNN
	1    2000 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 1500 2000 1500
Wire Wire Line
	5100 1700 5100 1250
Wire Wire Line
	5100 1250 9750 1250
Connection ~ 5100 1700
Wire Wire Line
	5100 1700 5350 1700
Wire Wire Line
	9450 1750 9600 1750
Wire Wire Line
	9600 1750 9600 1850
Connection ~ 9600 1850
Wire Wire Line
	9600 1850 9450 1850
Wire Wire Line
	9750 1850 9750 1250
Wire Wire Line
	9750 1850 9600 1850
$Comp
L power:GNDD #PWR?
U 1 1 5E780006
P 10050 2600
AR Path="/5E5D9B7F/5E5DB240/5E780006" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E780006" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 10050 2350 50  0001 C CNN
F 1 "GNDD" H 10054 2445 50  0000 C CNN
F 2 "" H 10050 2600 50  0001 C CNN
F 3 "" H 10050 2600 50  0001 C CNN
	1    10050 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 2450 10050 2450
Wire Wire Line
	10050 2450 10050 2600
Wire Wire Line
	9450 1950 10050 1950
Wire Wire Line
	10050 1950 10050 2450
Connection ~ 10050 2450
Wire Wire Line
	2600 1800 2500 1800
Wire Wire Line
	2500 1900 2600 1900
Wire Wire Line
	2600 1600 2500 1600
Wire Wire Line
	2600 1700 2500 1700
Text HLabel 2500 1600 0    50   Input ~ 0
DSP_TX
Text HLabel 2500 1700 0    50   Output ~ 0
DSP_RX
$Sheet
S 550  1900 750  850 
U 5E78D2F2
F0 "MCU_LED" 50
F1 "MCU_LED.sch" 50
F2 "mute_LED" I R 1300 2500 50 
F3 "comp_LED" I R 1300 2600 50 
F4 "overdrive_LED" I R 1300 2200 50 
F5 "octaver_LED" I R 1300 2000 50 
F6 "delay_LED" I R 1300 2100 50 
F7 "reverb_LED" I R 1300 2300 50 
F8 "clipping_LED" I R 1300 2400 50 
$EndSheet
Wire Wire Line
	7400 2150 8300 2150
Wire Wire Line
	7400 2250 8300 2250
Text HLabel 2500 1900 0    50   Output ~ 0
fan_pwm
$Comp
L Device:Thermistor_NTC TH1
U 1 1 5E66787A
P 10850 1950
F 0 "TH1" H 10947 1996 50  0000 L CNN
F 1 "10k" H 10947 1905 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10850 2000 50  0001 C CNN
F 3 "~" H 10850 2000 50  0001 C CNN
	1    10850 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E66E59C
P 10850 2350
F 0 "R1" H 10920 2396 50  0000 L CNN
F 1 "10k" H 10920 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10780 2350 50  0001 C CNN
F 3 "~" H 10850 2350 50  0001 C CNN
	1    10850 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 5E671F46
P 10850 2600
AR Path="/5E5D9B7F/5E5DB240/5E671F46" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E671F46" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 10850 2350 50  0001 C CNN
F 1 "GNDD" H 10854 2445 50  0000 C CNN
F 2 "" H 10850 2600 50  0001 C CNN
F 3 "" H 10850 2600 50  0001 C CNN
	1    10850 2600
	1    0    0    -1  
$EndComp
Connection ~ 9750 1250
Wire Wire Line
	10850 2100 10850 2150
Wire Wire Line
	10850 2500 10850 2600
Wire Wire Line
	10850 2150 10900 2150
Connection ~ 10850 2150
Wire Wire Line
	10850 2150 10850 2200
Text Label 10900 2150 0    50   ~ 0
V_temp
Text Label 8300 2350 2    50   ~ 0
V_temp
$Comp
L power:GNDD #PWR?
U 1 1 5E693600
P 10000 1700
AR Path="/5E5D9B7F/5E5DB240/5E693600" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E693600" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 10000 1450 50  0001 C CNN
F 1 "GNDD" H 10004 1545 50  0000 C CNN
F 2 "" H 10000 1700 50  0001 C CNN
F 3 "" H 10000 1700 50  0001 C CNN
	1    10000 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 1250 10000 1250
Wire Wire Line
	10000 1650 10000 1700
Wire Wire Line
	10000 1350 10000 1250
Connection ~ 10000 1250
Wire Wire Line
	10000 1250 10850 1250
$Comp
L Device:C C5
U 1 1 5E692B8B
P 10000 1500
F 0 "C5" H 10115 1546 50  0000 L CNN
F 1 "1µF/10V/UL ESR" H 10115 1455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10038 1350 50  0001 C CNN
F 3 "~" H 10000 1500 50  0001 C CNN
	1    10000 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10850 1250 10850 1800
NoConn ~ 3150 3850
NoConn ~ 3600 3850
NoConn ~ 3700 3850
NoConn ~ 4150 3850
NoConn ~ 4800 1600
Text Label 3250 3950 0    50   ~ 0
3V3
Text Label 4900 1700 0    50   ~ 0
3V3
Wire Wire Line
	3250 3950 3250 3850
NoConn ~ 3800 3850
$Sheet
S 5350 1500 2050 1750
U 5E5DB240
F0 "MCU_control_elements" 50
F1 "MCU_control_elements.sch" 50
F2 "MCU_3.3V" I L 5350 1700 50 
F3 "contour_pot" O L 5350 2100 50 
F4 "presence_pot" O L 5350 2000 50 
F5 "EQ_low_pot" O L 5350 2300 50 
F6 "EQ_low_mid_pot" O L 5350 2200 50 
F7 "EQ_high_mid_pot" O L 5350 2500 50 
F8 "EQ_high_pot" O L 5350 2400 50 
F9 "comp_ratio_pot" O R 7400 2450 50 
F10 "comp_threshold_pot" O L 5350 2600 50 
F11 "overdrive_gain_pot" O R 7400 2150 50 
F12 "overdrive_tone_pot" O R 7400 2250 50 
F13 "octaver_down_pot" O R 7400 1950 50 
F14 "octaver_up_pot" O R 7400 2050 50 
F15 "delay_vol_pot" O R 7400 1750 50 
F16 "reverb_vol_pot" O R 7400 1850 50 
F17 "mute_sw" O L 5350 1900 50 
F18 "delay_tap_button" O L 5350 1800 50 
$EndSheet
NoConn ~ 2500 1800
Wire Wire Line
	5350 1900 4800 1900
Wire Wire Line
	4800 1800 5350 1800
Wire Wire Line
	7400 2450 8300 2450
Wire Wire Line
	4800 2700 4900 2700
Wire Wire Line
	2450 2500 2600 2500
Wire Wire Line
	1300 2500 1450 2500
Wire Wire Line
	1300 2600 1450 2600
Text Label 3050 4000 3    50   ~ 0
mute_LED
Text Label 1450 2600 0    50   ~ 0
comp_LED
Wire Wire Line
	1300 2000 2600 2000
Wire Wire Line
	1300 2100 2600 2100
Wire Wire Line
	1300 2200 2600 2200
Wire Wire Line
	1300 2300 2600 2300
Wire Wire Line
	1300 2400 2600 2400
Wire Wire Line
	3050 3850 3050 4000
Wire Wire Line
	2950 3850 2950 4000
Text Label 1850 4950 2    50   ~ 0
3V3
Wire Wire Line
	2000 4950 1850 4950
$Comp
L power:GNDD #PWR?
U 1 1 5E6A5A63
P 1050 5550
AR Path="/5E5D9B7F/5E5DB240/5E6A5A63" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E6A5A63" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 1050 5300 50  0001 C CNN
F 1 "GNDD" H 1054 5395 50  0000 C CNN
F 2 "" H 1050 5550 50  0001 C CNN
F 3 "" H 1050 5550 50  0001 C CNN
	1    1050 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C25
U 1 1 5E6AC056
P 3300 5000
F 0 "C25" H 3415 5046 50  0000 L CNN
F 1 "0.1µF" H 3415 4955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3338 4850 50  0001 C CNN
F 3 "~" H 3300 5000 50  0001 C CNN
	1    3300 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C26
U 1 1 5E6B4E85
P 3650 5300
F 0 "C26" H 3765 5346 50  0000 L CNN
F 1 "0.1µF" H 3765 5255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3688 5150 50  0001 C CNN
F 3 "~" H 3650 5300 50  0001 C CNN
	1    3650 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 5150 3150 5150
Wire Wire Line
	3150 5150 3150 5050
Wire Wire Line
	3150 5050 3050 5050
Wire Wire Line
	3050 4950 3150 4950
Wire Wire Line
	3150 4950 3150 4850
Wire Wire Line
	3150 4850 3300 4850
Wire Wire Line
	3050 5250 3500 5250
Wire Wire Line
	3500 5250 3500 5150
Wire Wire Line
	3500 5150 3650 5150
Wire Wire Line
	3650 5450 3500 5450
Wire Wire Line
	3500 5450 3500 5350
Wire Wire Line
	3500 5350 3050 5350
$Comp
L Device:C C23
U 1 1 5E6BE854
P 1400 5150
F 0 "C23" V 1148 5150 50  0000 C CNN
F 1 "0.1µF" V 1239 5150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1438 5000 50  0001 C CNN
F 3 "~" H 1400 5150 50  0001 C CNN
	1    1400 5150
	0    1    1    0   
$EndComp
$Comp
L Device:C C24
U 1 1 5E6BEE85
P 1750 5250
F 0 "C24" V 1498 5250 50  0000 C CNN
F 1 "0.1µF" V 1589 5250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1788 5100 50  0001 C CNN
F 3 "~" H 1750 5250 50  0001 C CNN
	1    1750 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 5150 1550 5150
Wire Wire Line
	1050 5150 1050 5250
Wire Wire Line
	1050 5150 1250 5150
Connection ~ 1050 5250
Wire Wire Line
	1050 5250 1050 5450
Wire Wire Line
	1050 5250 1600 5250
Wire Wire Line
	1900 5250 2000 5250
Wire Wire Line
	2000 5450 1050 5450
Connection ~ 1050 5450
Wire Wire Line
	1050 5450 1050 5550
$Comp
L power:GNDD #PWR?
U 1 1 5E6D3180
P 1650 5950
AR Path="/5E5D9B7F/5E5DB240/5E6D3180" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E6D3180" Ref="#PWR0105"  Part="1" 
F 0 "#PWR0105" H 1650 5700 50  0001 C CNN
F 1 "GNDD" H 1654 5795 50  0000 C CNN
F 2 "" H 1650 5950 50  0001 C CNN
F 3 "" H 1650 5950 50  0001 C CNN
	1    1650 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5950 1650 5950
$Comp
L Connector:Conn_01x06_Male J3
U 1 1 5E6D993D
P 4150 5950
F 0 "J3" H 4122 5832 50  0000 R CNN
F 1 "footswitch" H 4122 5923 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 4150 5950 50  0001 C CNN
F 3 "~" H 4150 5950 50  0001 C CNN
	1    4150 5950
	-1   0    0    1   
$EndComp
Wire Wire Line
	3950 5650 3050 5650
Wire Wire Line
	3050 5750 3950 5750
$Comp
L bass_amplifier:MAX3232 U4
U 1 1 5E6E4CF1
P 2400 4800
F 0 "U4" H 2525 4875 50  0000 C CNN
F 1 "MAX3232" H 2525 4784 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 2400 4800 50  0001 C CNN
F 3 "" H 2400 4800 50  0001 C CNN
	1    2400 4800
	1    0    0    -1  
$EndComp
Text Label 2450 2500 2    50   ~ 0
FS_RX
Text Label 2450 2600 2    50   ~ 0
FS_TX
Text Label 1850 5750 2    50   ~ 0
FS_RX
Text Label 1850 5650 2    50   ~ 0
FS_TX
Wire Wire Line
	1850 5650 2000 5650
Wire Wire Line
	2000 5750 1850 5750
$Comp
L power:GNDD #PWR?
U 1 1 5E6F2C0E
P 3800 6250
AR Path="/5E5D9B7F/5E5DB240/5E6F2C0E" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E6F2C0E" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 3800 6000 50  0001 C CNN
F 1 "GNDD" H 3804 6095 50  0000 C CNN
F 2 "" H 3800 6250 50  0001 C CNN
F 3 "" H 3800 6250 50  0001 C CNN
	1    3800 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 6150 3800 6150
Wire Wire Line
	3800 6150 3800 6250
Wire Wire Line
	3950 6050 3800 6050
Wire Wire Line
	3800 6050 3800 6150
Connection ~ 3800 6150
Text GLabel 3800 5950 0    50   Input ~ 0
D+5V
Wire Wire Line
	3800 5950 3950 5950
Text GLabel 3800 5850 0    50   Input ~ 0
D+12V
Wire Wire Line
	3800 5850 3950 5850
$Comp
L Device:C C27
U 1 1 5E70ED6B
P 2550 6600
F 0 "C27" H 2665 6646 50  0000 L CNN
F 1 "0.1µF" H 2665 6555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2588 6450 50  0001 C CNN
F 3 "~" H 2550 6600 50  0001 C CNN
	1    2550 6600
	1    0    0    -1  
$EndComp
Text Label 2550 6350 2    50   ~ 0
3V3
$Comp
L power:GNDD #PWR?
U 1 1 5E70FB9A
P 2550 6850
AR Path="/5E5D9B7F/5E5DB240/5E70FB9A" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E70FB9A" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 2550 6600 50  0001 C CNN
F 1 "GNDD" H 2554 6695 50  0000 C CNN
F 2 "" H 2550 6850 50  0001 C CNN
F 3 "" H 2550 6850 50  0001 C CNN
	1    2550 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 6350 2550 6450
Wire Wire Line
	2550 6750 2550 6850
NoConn ~ 2000 6050
NoConn ~ 3050 6050
NoConn ~ 3050 5950
Text Label 2950 4000 3    50   ~ 0
comp_LED
Text Label 1450 2500 0    50   ~ 0
mute_LED
$EndSCHEMATC
