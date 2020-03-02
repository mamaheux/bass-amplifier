EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
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
L bass_amplifier:Teensy_LC U4
U 1 1 5E5D9C58
P 4000 1400
F 0 "U4" H 4700 1565 50  0000 C CNN
F 1 "Teensy_LC" H 4700 1474 50  0000 C CNN
F 2 "" H 4000 1400 50  0001 C CNN
F 3 "" H 4000 1400 50  0001 C CNN
	1    4000 1400
	1    0    0    -1  
$EndComp
$Sheet
S 6350 1500 2050 1750
U 5E5DB240
F0 "MCU_control_elements" 50
F1 "MCU_control_elements.sch" 50
F2 "MCU_3.3V" I L 6350 1700 50 
F3 "contour_pot" O L 6350 2700 50 
F4 "presence_pot" O L 6350 2600 50 
F5 "EQ_low_pot" O L 6350 2500 50 
F6 "EQ_low_mid_pot" O L 6350 2400 50 
F7 "EQ_high_mid_pot" O L 6350 2300 50 
F8 "EQ_high_pot" O L 6350 2200 50 
F9 "comp_ratio_pot" O L 6350 2100 50 
F10 "comp_threshold_pot" O L 6350 2000 50 
F11 "overdrive_gain_pot" O L 6350 1900 50 
F12 "overdrive_tone_pot" O L 6350 1800 50 
F13 "octaver_down_pot" O R 8400 1750 50 
F14 "octaver_up_pot" O R 8400 1850 50 
F15 "delay_vol_pot" O R 8400 1950 50 
F16 "reverb_vol_pot" O R 8400 2050 50 
F17 "mute_sw" O R 8400 2700 50 
F18 "delay_tap_button" O R 8400 2800 50 
$EndSheet
$Comp
L bass_amplifier:MCP3208 U5
U 1 1 5E747D2B
P 9700 1600
F 0 "U5" H 9875 1675 50  0000 C CNN
F 1 "MCP3208" H 9875 1584 50  0000 C CNN
F 2 "" H 9700 1600 50  0001 C CNN
F 3 "" H 9700 1600 50  0001 C CNN
	1    9700 1600
	1    0    0    -1  
$EndComp
Text Label 8500 2700 0    50   ~ 0
mute_sw
Text Label 8500 2800 0    50   ~ 0
delay_tap_button
Wire Wire Line
	3600 2800 3450 2800
Wire Wire Line
	3600 2700 3450 2700
Wire Wire Line
	3600 2600 3450 2600
Wire Wire Line
	5800 2800 5900 2800
Text Label 5900 2800 0    50   ~ 0
ADC_SCK
Text Label 10550 2050 0    50   ~ 0
ADC_SCK
Wire Wire Line
	10550 2050 10450 2050
Wire Wire Line
	10450 2150 10550 2150
Wire Wire Line
	10450 2250 10550 2250
Wire Wire Line
	10450 2350 10550 2350
Wire Wire Line
	5800 1700 6100 1700
Wire Wire Line
	5800 1800 6350 1800
Wire Wire Line
	5800 1900 6350 1900
Wire Wire Line
	5800 2000 6350 2000
Wire Wire Line
	5800 2100 6350 2100
Wire Wire Line
	5800 2200 6350 2200
Wire Wire Line
	5800 2300 6350 2300
Wire Wire Line
	5800 2400 6350 2400
Wire Wire Line
	5800 2500 6350 2500
Wire Wire Line
	5800 2600 6350 2600
Wire Wire Line
	5800 2700 6350 2700
Text Label 3450 2600 2    50   ~ 0
ADC_CS
Text Label 10550 2350 0    50   ~ 0
ADC_CS
Text Label 3450 2700 2    50   ~ 0
ADC_MOSI
Text Label 10550 2250 0    50   ~ 0
ADC_MOSI
Text Label 3450 2800 2    50   ~ 0
ADC_MISO
Text Label 10550 2150 0    50   ~ 0
ADC_MISO
Wire Wire Line
	9300 1750 8400 1750
Wire Wire Line
	8400 1850 9300 1850
Wire Wire Line
	9300 1950 8400 1950
Wire Wire Line
	8400 2050 9300 2050
Wire Wire Line
	8500 2700 8400 2700
Wire Wire Line
	8400 2800 8500 2800
Wire Wire Line
	5800 1500 5950 1500
Wire Wire Line
	5950 1500 5950 1200
Text GLabel 5950 1200 0    50   Input ~ 0
D+5V
$Comp
L power:GNDD #PWR?
U 1 1 5E77C2E4
P 3000 1500
AR Path="/5E5D9B7F/5E5DB240/5E77C2E4" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E77C2E4" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3000 1250 50  0001 C CNN
F 1 "GNDD" H 3004 1345 50  0000 C CNN
F 2 "" H 3000 1500 50  0001 C CNN
F 3 "" H 3000 1500 50  0001 C CNN
	1    3000 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1500 3000 1500
Wire Wire Line
	6100 1700 6100 1250
Wire Wire Line
	6100 1250 10750 1250
Connection ~ 6100 1700
Wire Wire Line
	6100 1700 6350 1700
Wire Wire Line
	10450 1750 10600 1750
Wire Wire Line
	10600 1750 10600 1850
Connection ~ 10600 1850
Wire Wire Line
	10600 1850 10450 1850
Wire Wire Line
	10750 1850 10750 1250
Wire Wire Line
	10750 1850 10600 1850
$Comp
L power:GNDD #PWR?
U 1 1 5E780006
P 11050 2600
AR Path="/5E5D9B7F/5E5DB240/5E780006" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E780006" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 11050 2350 50  0001 C CNN
F 1 "GNDD" H 11054 2445 50  0000 C CNN
F 2 "" H 11050 2600 50  0001 C CNN
F 3 "" H 11050 2600 50  0001 C CNN
	1    11050 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 2450 11050 2450
Wire Wire Line
	11050 2450 11050 2600
Wire Wire Line
	10450 1950 11050 1950
Wire Wire Line
	11050 1950 11050 2450
Connection ~ 11050 2450
$Comp
L power:GNDD #PWR?
U 1 1 5E781FEB
P 8850 2300
AR Path="/5E5D9B7F/5E5DB240/5E781FEB" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E781FEB" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8850 2050 50  0001 C CNN
F 1 "GNDD" H 8854 2145 50  0000 C CNN
F 2 "" H 8850 2300 50  0001 C CNN
F 3 "" H 8850 2300 50  0001 C CNN
	1    8850 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2150 9100 2150
Wire Wire Line
	8850 2150 8850 2300
Wire Wire Line
	9300 2250 9100 2250
Wire Wire Line
	9100 2250 9100 2150
Connection ~ 9100 2150
Wire Wire Line
	9100 2150 8850 2150
Wire Wire Line
	9300 2350 9100 2350
Wire Wire Line
	9100 2350 9100 2250
Connection ~ 9100 2250
Wire Wire Line
	9300 2450 9100 2450
Wire Wire Line
	9100 2450 9100 2350
Connection ~ 9100 2350
Text Label 3500 1800 2    50   ~ 0
mute_sw
Text Label 3500 1900 2    50   ~ 0
delay_tap_button
Wire Wire Line
	3600 1800 3500 1800
Wire Wire Line
	3500 1900 3600 1900
Wire Wire Line
	3600 1600 3500 1600
Wire Wire Line
	3600 1700 3500 1700
Text HLabel 3500 1600 0    50   Input ~ 0
DSP_TX
Text HLabel 3500 1700 0    50   Output ~ 0
DSP_RX
$Sheet
S 1900 1900 750  750 
U 5E78D2F2
F0 "MCU_LED" 50
F1 "MCU_LED.sch" 50
F2 "mute_LED" I R 2650 2000 50 
F3 "comp_LED" I R 2650 2100 50 
F4 "overdrive_LED" I R 2650 2200 50 
F5 "octaver_LED" I R 2650 2300 50 
F6 "delay_LED" I R 2650 2400 50 
F7 "reverb_LED" I R 2650 2500 50 
$EndSheet
Wire Wire Line
	2650 2000 3600 2000
Wire Wire Line
	3600 2100 2650 2100
Wire Wire Line
	2650 2200 3600 2200
Wire Wire Line
	3600 2300 2650 2300
Wire Wire Line
	2650 2400 3600 2400
Wire Wire Line
	3600 2500 2650 2500
$EndSCHEMATC
