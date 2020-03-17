EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 900  800  0    50   Input ~ 0
D+12V
$Comp
L power:GNDD #PWR?
U 1 1 5E7ACF25
P 2850 2050
AR Path="/5E5D9B7F/5E5DB240/5E7ACF25" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E78D2F2/5E7ACF25" Ref="#PWR031"  Part="1" 
AR Path="/5E6AE89A/5E7ACF25" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 2850 1800 50  0001 C CNN
F 1 "GNDD" H 2854 1895 50  0000 C CNN
F 2 "" H 2850 2050 50  0001 C CNN
F 3 "" H 2850 2050 50  0001 C CNN
	1    2850 2050
	1    0    0    -1  
$EndComp
Text HLabel 2500 1750 0    50   Input ~ 0
mute_LED
Wire Wire Line
	2550 1750 2500 1750
$Comp
L bass_amplifier:LED_4X D1
U 2 1 5E7ADE6D
P 2850 1300
F 0 "D1" V 2889 1182 50  0000 R CNN
F 1 "LED" V 2798 1182 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 2850 1300 50  0001 C CNN
F 3 "~" H 2850 1300 50  0001 C CNN
	2    2850 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2850 1450 2850 1550
Wire Wire Line
	2850 1950 2850 2050
Wire Wire Line
	2850 1150 2850 800 
$Comp
L power:GNDD #PWR?
U 1 1 5E7B2D72
P 4300 2050
AR Path="/5E5D9B7F/5E5DB240/5E7B2D72" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E78D2F2/5E7B2D72" Ref="#PWR032"  Part="1" 
AR Path="/5E6AE89A/5E7B2D72" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 4300 1800 50  0001 C CNN
F 1 "GNDD" H 4304 1895 50  0000 C CNN
F 2 "" H 4300 2050 50  0001 C CNN
F 3 "" H 4300 2050 50  0001 C CNN
	1    4300 2050
	1    0    0    -1  
$EndComp
Text HLabel 3950 1750 0    50   Input ~ 0
comp_LED
Wire Wire Line
	4000 1750 3950 1750
$Comp
L bass_amplifier:LED_4X D1
U 3 1 5E7B2D7A
P 4300 1300
F 0 "D1" V 4339 1182 50  0000 R CNN
F 1 "LED" V 4248 1182 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 4300 1300 50  0001 C CNN
F 3 "~" H 4300 1300 50  0001 C CNN
	3    4300 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 1450 4300 1550
Wire Wire Line
	4300 1950 4300 2050
Wire Wire Line
	4300 1150 4300 800 
Wire Wire Line
	4300 800  2850 800 
Connection ~ 2850 800 
$Comp
L power:GNDD #PWR?
U 1 1 5E7B63C5
P 5850 2050
AR Path="/5E5D9B7F/5E5DB240/5E7B63C5" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E78D2F2/5E7B63C5" Ref="#PWR033"  Part="1" 
AR Path="/5E6AE89A/5E7B63C5" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 5850 1800 50  0001 C CNN
F 1 "GNDD" H 5854 1895 50  0000 C CNN
F 2 "" H 5850 2050 50  0001 C CNN
F 3 "" H 5850 2050 50  0001 C CNN
	1    5850 2050
	1    0    0    -1  
$EndComp
Text HLabel 5500 1750 0    50   Input ~ 0
overdrive_LED
Wire Wire Line
	5550 1750 5500 1750
$Comp
L bass_amplifier:LED_4X D1
U 4 1 5E7B63CD
P 5850 1300
F 0 "D1" V 5889 1182 50  0000 R CNN
F 1 "LED" V 5798 1182 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 5850 1300 50  0001 C CNN
F 3 "~" H 5850 1300 50  0001 C CNN
	4    5850 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5850 1450 5850 1550
Wire Wire Line
	5850 1950 5850 2050
Wire Wire Line
	5850 1150 5850 800 
$Comp
L power:GNDD #PWR?
U 1 1 5E7B73CE
P 7400 2050
AR Path="/5E5D9B7F/5E5DB240/5E7B73CE" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E78D2F2/5E7B73CE" Ref="#PWR034"  Part="1" 
AR Path="/5E6AE89A/5E7B73CE" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 7400 1800 50  0001 C CNN
F 1 "GNDD" H 7404 1895 50  0000 C CNN
F 2 "" H 7400 2050 50  0001 C CNN
F 3 "" H 7400 2050 50  0001 C CNN
	1    7400 2050
	1    0    0    -1  
$EndComp
Text HLabel 7050 1750 0    50   Input ~ 0
octaver_LED
Wire Wire Line
	7100 1750 7050 1750
$Comp
L bass_amplifier:LED_4X D2
U 1 1 5E7B73D6
P 7400 1300
F 0 "D2" V 7439 1182 50  0000 R CNN
F 1 "LED" V 7348 1182 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 7400 1300 50  0001 C CNN
F 3 "~" H 7400 1300 50  0001 C CNN
	1    7400 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7400 1450 7400 1550
Wire Wire Line
	7400 1950 7400 2050
Wire Wire Line
	7400 1150 7400 800 
$Comp
L power:GNDD #PWR?
U 1 1 5E7B869C
P 8900 2050
AR Path="/5E5D9B7F/5E5DB240/5E7B869C" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E78D2F2/5E7B869C" Ref="#PWR035"  Part="1" 
AR Path="/5E6AE89A/5E7B869C" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 8900 1800 50  0001 C CNN
F 1 "GNDD" H 8904 1895 50  0000 C CNN
F 2 "" H 8900 2050 50  0001 C CNN
F 3 "" H 8900 2050 50  0001 C CNN
	1    8900 2050
	1    0    0    -1  
$EndComp
Text HLabel 8550 1750 0    50   Input ~ 0
delay_LED
Wire Wire Line
	8600 1750 8550 1750
$Comp
L bass_amplifier:LED_4X D2
U 2 1 5E7B86A4
P 8900 1300
F 0 "D2" V 8939 1182 50  0000 R CNN
F 1 "LED" V 8848 1182 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 8900 1300 50  0001 C CNN
F 3 "~" H 8900 1300 50  0001 C CNN
	2    8900 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8900 1450 8900 1550
Wire Wire Line
	8900 1950 8900 2050
Wire Wire Line
	8900 1150 8900 800 
$Comp
L power:GNDD #PWR?
U 1 1 5E7BB5DF
P 10350 2050
AR Path="/5E5D9B7F/5E5DB240/5E7BB5DF" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E78D2F2/5E7BB5DF" Ref="#PWR036"  Part="1" 
AR Path="/5E6AE89A/5E7BB5DF" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 10350 1800 50  0001 C CNN
F 1 "GNDD" H 10354 1895 50  0000 C CNN
F 2 "" H 10350 2050 50  0001 C CNN
F 3 "" H 10350 2050 50  0001 C CNN
	1    10350 2050
	1    0    0    -1  
$EndComp
Text HLabel 10000 1750 0    50   Input ~ 0
reverb_LED
Wire Wire Line
	10050 1750 10000 1750
$Comp
L bass_amplifier:LED_4X D2
U 3 1 5E7BB5E7
P 10350 1300
F 0 "D2" V 10389 1182 50  0000 R CNN
F 1 "LED" V 10298 1182 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 10350 1300 50  0001 C CNN
F 3 "~" H 10350 1300 50  0001 C CNN
	3    10350 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10350 1450 10350 1550
Wire Wire Line
	10350 1950 10350 2050
Wire Wire Line
	10350 1150 10350 800 
Wire Wire Line
	4300 800  5850 800 
Connection ~ 4300 800 
Wire Wire Line
	7400 800  5850 800 
Connection ~ 5850 800 
Wire Wire Line
	7400 800  8900 800 
Connection ~ 7400 800 
Wire Wire Line
	8900 800  10350 800 
Connection ~ 8900 800 
$Comp
L bass_amplifier:TD9944 Q1
U 1 1 5E5E3ADE
P 2750 1750
F 0 "Q1" H 2955 1796 50  0000 L CNN
F 1 "TD9944" H 2955 1705 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 2950 1850 50  0001 C CNN
F 3 "~" H 2750 1750 50  0001 C CNN
	1    2750 1750
	1    0    0    -1  
$EndComp
$Comp
L bass_amplifier:TD9944 Q2
U 1 1 5E5E6B5B
P 4200 1750
F 0 "Q2" H 4405 1796 50  0000 L CNN
F 1 "TD9944" H 4405 1705 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4400 1850 50  0001 C CNN
F 3 "~" H 4200 1750 50  0001 C CNN
	1    4200 1750
	1    0    0    -1  
$EndComp
$Comp
L bass_amplifier:TD9944 Q2
U 2 1 5E5E7BD1
P 5750 1750
F 0 "Q2" H 5955 1796 50  0000 L CNN
F 1 "TD9944" H 5955 1705 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5950 1850 50  0001 C CNN
F 3 "~" H 5750 1750 50  0001 C CNN
	2    5750 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  800  1500 800 
$Comp
L bass_amplifier:TD9944 Q1
U 2 1 5E66CE4F
P 1400 1750
F 0 "Q1" H 1605 1796 50  0000 L CNN
F 1 "TD9944" H 1605 1705 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1600 1850 50  0001 C CNN
F 3 "~" H 1400 1750 50  0001 C CNN
	2    1400 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1950 1500 2050
Wire Wire Line
	1500 1450 1500 1550
$Comp
L bass_amplifier:LED_4X D1
U 1 1 5E66CE45
P 1500 1300
F 0 "D1" V 1539 1182 50  0000 R CNN
F 1 "LED" V 1448 1182 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 1500 1300 50  0001 C CNN
F 3 "~" H 1500 1300 50  0001 C CNN
	1    1500 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1200 1750 1150 1750
Text HLabel 1150 1750 0    50   Input ~ 0
clipping_LED
$Comp
L power:GNDD #PWR?
U 1 1 5E66CE3D
P 1500 2050
AR Path="/5E5D9B7F/5E5DB240/5E66CE3D" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E78D2F2/5E66CE3D" Ref="#PWR0103"  Part="1" 
AR Path="/5E6AE89A/5E66CE3D" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 1500 1800 50  0001 C CNN
F 1 "GNDD" H 1504 1895 50  0000 C CNN
F 2 "" H 1500 2050 50  0001 C CNN
F 3 "" H 1500 2050 50  0001 C CNN
	1    1500 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 800  1500 1150
Connection ~ 1500 800 
Wire Wire Line
	1500 800  2850 800 
$Comp
L bass_amplifier:LED_4X D2
U 4 1 5E6DA068
P 1500 2800
F 0 "D2" V 1539 2682 50  0000 R CNN
F 1 "LED" V 1448 2682 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 1500 2800 50  0001 C CNN
F 3 "~" H 1500 2800 50  0001 C CNN
	4    1500 2800
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 5E6DCFC5
P 1500 3050
AR Path="/5E5D9B7F/5E5DB240/5E6DCFC5" Ref="#PWR?"  Part="1" 
AR Path="/5E5D9B7F/5E78D2F2/5E6DCFC5" Ref="#PWR?"  Part="1" 
AR Path="/5E6AE89A/5E6DCFC5" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 1500 2800 50  0001 C CNN
F 1 "GNDD" H 1504 2895 50  0000 C CNN
F 2 "" H 1500 3050 50  0001 C CNN
F 3 "" H 1500 3050 50  0001 C CNN
	1    1500 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3050 1500 2950
Text GLabel 1400 2500 0    50   Input ~ 0
D+12V
Wire Wire Line
	1400 2500 1500 2500
Wire Wire Line
	1500 2500 1500 2650
$Comp
L bass_amplifier:TD9944 Q3
U 2 1 5E5F39B5
P 10250 1750
F 0 "Q3" H 10455 1796 50  0000 L CNN
F 1 "TD9944" H 10455 1705 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 10450 1850 50  0001 C CNN
F 3 "~" H 10250 1750 50  0001 C CNN
	2    10250 1750
	1    0    0    -1  
$EndComp
$Comp
L bass_amplifier:TD9944 Q3
U 1 1 5E5E9242
P 7300 1750
F 0 "Q3" H 7505 1796 50  0000 L CNN
F 1 "TD9944" H 7505 1705 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 7500 1850 50  0001 C CNN
F 3 "~" H 7300 1750 50  0001 C CNN
	1    7300 1750
	1    0    0    -1  
$EndComp
$Comp
L bass_amplifier:TD9944 Q4
U 1 1 5E5F4A21
P 8800 1750
F 0 "Q4" H 9005 1796 50  0000 L CNN
F 1 "TD9944" H 9005 1705 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9000 1850 50  0001 C CNN
F 3 "~" H 8800 1750 50  0001 C CNN
	1    8800 1750
	1    0    0    -1  
$EndComp
$EndSCHEMATC