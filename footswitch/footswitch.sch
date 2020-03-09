EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
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
L Connector:Conn_01x06_Male J1
U 1 1 5E666EBC
P 3950 1850
F 0 "J1" H 3922 1732 50  0000 R CNN
F 1 "control" H 3922 1823 50  0000 R CNN
F 2 "" H 3950 1850 50  0001 C CNN
F 3 "~" H 3950 1850 50  0001 C CNN
	1    3950 1850
	-1   0    0    1   
$EndComp
$Comp
L power:GNDD #PWR08
U 1 1 5E668115
P 3600 2150
F 0 "#PWR08" H 3600 1900 50  0001 C CNN
F 1 "GNDD" H 3604 1995 50  0000 C CNN
F 2 "" H 3600 2150 50  0001 C CNN
F 3 "" H 3600 2150 50  0001 C CNN
	1    3600 2150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3750 1950 3600 1950
Wire Wire Line
	3600 1950 3600 2050
Wire Wire Line
	3750 2050 3600 2050
Connection ~ 3600 2050
Wire Wire Line
	3600 2050 3600 2150
Text GLabel 3600 1850 0    50   Input ~ 0
D+5V
Wire Wire Line
	3600 1850 3750 1850
Text GLabel 3600 1750 0    50   Input ~ 0
D+12V
Wire Wire Line
	3600 1750 3750 1750
$Comp
L bass_amplifier:MAX3232 U4
U 1 1 5E66B73E
P 2450 700
F 0 "U4" H 2575 775 50  0000 C CNN
F 1 "MAX3232" H 2575 684 50  0000 C CNN
F 2 "" H 2450 700 50  0001 C CNN
F 3 "" H 2450 700 50  0001 C CNN
	1    2450 700 
	1    0    0    -1  
$EndComp
$Comp
L bass_amplifier:Teensy_LC U1
U 1 1 5E66C1D4
P 7500 850
F 0 "U1" H 8200 1015 50  0000 C CNN
F 1 "Teensy_LC" H 8200 924 50  0000 C CNN
F 2 "" H 7500 850 50  0001 C CNN
F 3 "" H 7500 850 50  0001 C CNN
	1    7500 850 
	1    0    0    -1  
$EndComp
Text GLabel 9450 950  2    50   Input ~ 0
D+5V
Wire Wire Line
	9450 950  9300 950 
Wire Wire Line
	9300 1150 9450 1150
$Comp
L power:GNDD #PWR09
U 1 1 5E66D03D
P 6500 1000
F 0 "#PWR09" H 6500 750 50  0001 C CNN
F 1 "GNDD" H 6504 845 50  0000 C CNN
F 2 "" H 6500 1000 50  0001 C CNN
F 3 "" H 6500 1000 50  0001 C CNN
	1    6500 1000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6500 1000 6500 950 
Wire Wire Line
	6500 950  7100 950 
Text Label 9450 1150 0    50   ~ 0
3V3
Text Label 1850 850  2    50   ~ 0
3V3
Wire Wire Line
	2050 850  1850 850 
NoConn ~ 2050 1950
$Comp
L power:GNDD #PWR01
U 1 1 5E66F175
P 900 1450
F 0 "#PWR01" H 900 1200 50  0001 C CNN
F 1 "GNDD" H 904 1295 50  0000 C CNN
F 2 "" H 900 1450 50  0001 C CNN
F 3 "" H 900 1450 50  0001 C CNN
	1    900  1450
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E66FA41
P 1400 1050
F 0 "C2" V 1148 1050 50  0000 C CNN
F 1 "0.1µF" V 1239 1050 50  0000 C CNN
F 2 "" H 1438 900 50  0001 C CNN
F 3 "~" H 1400 1050 50  0001 C CNN
	1    1400 1050
	0    1    1    0   
$EndComp
$Comp
L Device:C C5
U 1 1 5E670161
P 1750 1150
F 0 "C5" V 1498 1150 50  0000 C CNN
F 1 "0.1µF" V 1589 1150 50  0000 C CNN
F 2 "" H 1788 1000 50  0001 C CNN
F 3 "~" H 1750 1150 50  0001 C CNN
	1    1750 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	1250 1050 900  1050
Wire Wire Line
	900  1050 900  1150
Wire Wire Line
	1550 1050 2050 1050
Wire Wire Line
	2050 1150 1900 1150
Connection ~ 900  1150
Wire Wire Line
	900  1150 900  1350
Wire Wire Line
	900  1150 1600 1150
Wire Wire Line
	2050 1350 900  1350
Connection ~ 900  1350
Wire Wire Line
	900  1350 900  1450
$Comp
L power:GNDD #PWR05
U 1 1 5E672D84
P 1850 1950
F 0 "#PWR05" H 1850 1700 50  0001 C CNN
F 1 "GNDD" H 1854 1795 50  0000 C CNN
F 2 "" H 1850 1950 50  0001 C CNN
F 3 "" H 1850 1950 50  0001 C CNN
	1    1850 1950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1850 1950 1850 1850
Wire Wire Line
	1850 1850 2050 1850
NoConn ~ 3100 1950
NoConn ~ 3100 1850
Wire Wire Line
	3750 1550 3100 1550
Wire Wire Line
	3100 1650 3750 1650
$Comp
L Device:C C8
U 1 1 5E6802EE
P 3400 900
F 0 "C8" H 3285 854 50  0000 R CNN
F 1 "0.1µF" H 3285 945 50  0000 R CNN
F 2 "" H 3438 750 50  0001 C CNN
F 3 "~" H 3400 900 50  0001 C CNN
	1    3400 900 
	-1   0    0    1   
$EndComp
$Comp
L Device:C C9
U 1 1 5E68078A
P 3850 1200
F 0 "C9" H 3735 1154 50  0000 R CNN
F 1 "0.1µF" H 3735 1245 50  0000 R CNN
F 2 "" H 3888 1050 50  0001 C CNN
F 3 "~" H 3850 1200 50  0001 C CNN
	1    3850 1200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3400 1050 3200 1050
Wire Wire Line
	3200 1050 3200 950 
Wire Wire Line
	3200 950  3100 950 
Wire Wire Line
	3100 850  3200 850 
Wire Wire Line
	3200 850  3200 750 
Wire Wire Line
	3200 750  3400 750 
Wire Wire Line
	3550 1050 3550 1150
Wire Wire Line
	3550 1150 3100 1150
Wire Wire Line
	3550 1050 3850 1050
Wire Wire Line
	3100 1250 3550 1250
Wire Wire Line
	3550 1250 3550 1350
Wire Wire Line
	3550 1350 3850 1350
Wire Wire Line
	1950 1550 2050 1550
Wire Wire Line
	1950 1650 2050 1650
Text Label 1950 1550 2    50   ~ 0
control_TX
Text Label 1950 1650 2    50   ~ 0
control_RX
Text Label 7100 1050 2    50   ~ 0
control_RX
Text Label 7100 1150 2    50   ~ 0
control_TX
$Comp
L Device:CP C3
U 1 1 5E689D4F
P 1550 2950
F 0 "C3" H 1668 2996 50  0000 L CNN
F 1 "1000µF/25V" H 1668 2905 50  0000 L CNN
F 2 "" H 1588 2800 50  0001 C CNN
F 3 "~" H 1550 2950 50  0001 C CNN
	1    1550 2950
	1    0    0    -1  
$EndComp
Text GLabel 1150 2700 0    50   Input ~ 0
D+5V
$Comp
L power:GNDD #PWR03
U 1 1 5E68B45B
P 1550 3250
F 0 "#PWR03" H 1550 3000 50  0001 C CNN
F 1 "GNDD" H 1554 3095 50  0000 C CNN
F 2 "" H 1550 3250 50  0001 C CNN
F 3 "" H 1550 3250 50  0001 C CNN
	1    1550 3250
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5E68B84A
P 2350 2950
F 0 "C6" H 2465 2996 50  0000 L CNN
F 1 "2.2µF/25V/UL low ESR" H 2465 2905 50  0000 L CNN
F 2 "" H 2388 2800 50  0001 C CNN
F 3 "~" H 2350 2950 50  0001 C CNN
	1    2350 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 2700 1550 2700
Wire Wire Line
	1550 2700 1550 2800
Wire Wire Line
	1550 2700 2350 2700
Wire Wire Line
	2350 2700 2350 2800
Connection ~ 1550 2700
Wire Wire Line
	1550 3100 1550 3250
$Comp
L power:GNDD #PWR06
U 1 1 5E68DF05
P 2350 3250
F 0 "#PWR06" H 2350 3000 50  0001 C CNN
F 1 "GNDD" H 2354 3095 50  0000 C CNN
F 2 "" H 2350 3250 50  0001 C CNN
F 3 "" H 2350 3250 50  0001 C CNN
	1    2350 3250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2350 3250 2350 3100
$Comp
L Device:CP C4
U 1 1 5E69F003
P 1550 3900
F 0 "C4" H 1668 3946 50  0000 L CNN
F 1 "1000µF/25V" H 1668 3855 50  0000 L CNN
F 2 "" H 1588 3750 50  0001 C CNN
F 3 "~" H 1550 3900 50  0001 C CNN
	1    1550 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR04
U 1 1 5E69F00A
P 1550 4200
F 0 "#PWR04" H 1550 3950 50  0001 C CNN
F 1 "GNDD" H 1554 4045 50  0000 C CNN
F 2 "" H 1550 4200 50  0001 C CNN
F 3 "" H 1550 4200 50  0001 C CNN
	1    1550 4200
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5E69F010
P 2350 3900
F 0 "C7" H 2465 3946 50  0000 L CNN
F 1 "2.2µF/25V/UL low ESR" H 2465 3855 50  0000 L CNN
F 2 "" H 2388 3750 50  0001 C CNN
F 3 "~" H 2350 3900 50  0001 C CNN
	1    2350 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 3650 1550 3650
Wire Wire Line
	1550 3650 1550 3750
Wire Wire Line
	1550 3650 2350 3650
Wire Wire Line
	2350 3650 2350 3750
Connection ~ 1550 3650
Wire Wire Line
	1550 4050 1550 4200
$Comp
L power:GNDD #PWR07
U 1 1 5E69F01C
P 2350 4200
F 0 "#PWR07" H 2350 3950 50  0001 C CNN
F 1 "GNDD" H 2354 4045 50  0000 C CNN
F 2 "" H 2350 4200 50  0001 C CNN
F 3 "" H 2350 4200 50  0001 C CNN
	1    2350 4200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2350 4200 2350 4050
Text GLabel 1150 3650 0    50   Input ~ 0
D+12V
$Comp
L Device:C C1
U 1 1 5E6A1EE8
P 900 2000
F 0 "C1" H 785 1954 50  0000 R CNN
F 1 "0.1µF" H 785 2045 50  0000 R CNN
F 2 "" H 938 1850 50  0001 C CNN
F 3 "~" H 900 2000 50  0001 C CNN
	1    900  2000
	-1   0    0    1   
$EndComp
Text Label 900  1800 2    50   ~ 0
3V3
$Comp
L power:GNDD #PWR02
U 1 1 5E6A31EE
P 900 2250
F 0 "#PWR02" H 900 2000 50  0001 C CNN
F 1 "GNDD" H 904 2095 50  0000 C CNN
F 2 "" H 900 2250 50  0001 C CNN
F 3 "" H 900 2250 50  0001 C CNN
	1    900  2250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	900  1800 900  1850
Wire Wire Line
	900  2150 900  2250
$Sheet
S 9450 1450 850  800 
U 5E6AE89A
F0 "MCU_LED" 50
F1 "MCU_LED.sch" 50
F2 "mute_LED" I L 9450 1550 50 
F3 "comp_LED" I L 9450 1650 50 
F4 "overdrive_LED" I L 9450 1750 50 
F5 "octaver_LED" I L 9450 1850 50 
F6 "delay_LED" I L 9450 1950 50 
F7 "reverb_LED" I L 9450 2050 50 
F8 "clipping_LED" I L 9450 2150 50 
$EndSheet
Wire Wire Line
	9300 2150 9450 2150
Wire Wire Line
	9450 2050 9300 2050
Wire Wire Line
	9300 1950 9450 1950
Wire Wire Line
	9450 1850 9300 1850
Wire Wire Line
	9300 1750 9450 1750
Wire Wire Line
	9450 1650 9300 1650
Wire Wire Line
	9300 1550 9450 1550
NoConn ~ 9300 1050
NoConn ~ 9300 1250
NoConn ~ 9300 1350
NoConn ~ 9300 1450
NoConn ~ 8650 3300
NoConn ~ 8300 3300
NoConn ~ 8200 3300
NoConn ~ 8100 3300
NoConn ~ 7750 3300
NoConn ~ 7650 3300
NoConn ~ 7550 3300
NoConn ~ 7450 3300
$Sheet
S 5100 1050 950  1750
U 5E6FEBFE
F0 "MCU_switchs" 50
F1 "MCU_switchs.sch" 50
F2 "MCU_3.3V" I R 6050 1150 50 
F3 "mute_sw" O R 6050 1250 50 
F4 "comp_sw" O R 6050 1350 50 
F5 "overdrive_sw" O R 6050 1450 50 
F6 "octaver_sw" O R 6050 1550 50 
F7 "delay_sw" O R 6050 1650 50 
F8 "delay_tap_button" O R 6050 1750 50 
F9 "reverb_sw" O R 6050 1850 50 
F10 "opt_1_sw" O R 6050 1950 50 
F11 "opt_2_sw" O R 6050 2050 50 
F12 "opt_3_sw" O R 6050 2150 50 
F13 "opt_4_sw" O R 6050 2250 50 
F14 "opt_5_sw" O R 6050 2350 50 
$EndSheet
Wire Wire Line
	6050 1250 7100 1250
Wire Wire Line
	6050 1350 7100 1350
Wire Wire Line
	7100 1450 6050 1450
Wire Wire Line
	6050 1550 7100 1550
Wire Wire Line
	7100 1650 6050 1650
Wire Wire Line
	6050 1750 7100 1750
Wire Wire Line
	7100 1850 6050 1850
Wire Wire Line
	6050 1150 6200 1150
Text Label 6200 1150 0    50   ~ 0
3V3
Wire Wire Line
	6050 1950 7100 1950
Wire Wire Line
	7100 2050 6050 2050
Wire Wire Line
	6050 2150 7100 2150
Wire Wire Line
	7100 2250 6050 2250
Wire Wire Line
	7050 2350 7050 3600
Wire Wire Line
	7050 3600 9350 3600
Wire Wire Line
	9350 3600 9350 2250
Wire Wire Line
	9350 2250 9300 2250
Wire Wire Line
	6050 2350 7050 2350
$EndSCHEMATC
