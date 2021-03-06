EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
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
L Device:R R?
U 1 1 5E69BC1F
P 1150 1800
AR Path="/5E66D107/5E69BC1F" Ref="R?"  Part="1" 
AR Path="/5E699B57/5E69BC1F" Ref="R8"  Part="1" 
F 0 "R8" V 943 1800 50  0000 C CNN
F 1 "0" V 1034 1800 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1080 1800 50  0001 C CNN
F 3 "~" H 1150 1800 50  0001 C CNN
	1    1150 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	1350 1800 1300 1800
Wire Wire Line
	1000 1800 950  1800
Wire Wire Line
	950  1800 950  1900
$Comp
L power:GNDD #PWR?
U 1 1 5E69BC28
P 950 1900
AR Path="/5E66D107/5E69BC28" Ref="#PWR?"  Part="1" 
AR Path="/5E699B57/5E69BC28" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 950 1650 50  0001 C CNN
F 1 "GNDD" H 954 1745 50  0000 C CNN
F 2 "" H 950 1900 50  0001 C CNN
F 3 "" H 950 1900 50  0001 C CNN
	1    950  1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1800 1350 1900
$Comp
L power:GNDA #PWR0125
U 1 1 5E69C115
P 1350 1900
F 0 "#PWR0125" H 1350 1650 50  0001 C CNN
F 1 "GNDA" H 1355 1727 50  0000 C CNN
F 2 "" H 1350 1900 50  0001 C CNN
F 3 "" H 1350 1900 50  0001 C CNN
	1    1350 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E69DBFC
P 8700 1350
AR Path="/5E69DBFC" Ref="C?"  Part="1" 
AR Path="/5E65B39F/5E69DBFC" Ref="C?"  Part="1" 
AR Path="/5E699B57/5E69DBFC" Ref="C23"  Part="1" 
F 0 "C23" H 8815 1396 50  0000 L CNN
F 1 "2.2µF/25V/UL ESR" H 8815 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8738 1200 50  0001 C CNN
F 3 "~" H 8700 1350 50  0001 C CNN
	1    8700 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 1100 8700 1200
Wire Wire Line
	7350 1100 6550 1100
Wire Wire Line
	8700 1100 8350 1100
Wire Wire Line
	8700 1500 8700 1900
Wire Wire Line
	6550 1950 6550 2350
Text HLabel 9250 1100 2    50   Output ~ 0
A+9V
$Comp
L bass_amplifier:MC7809 U5
U 1 1 5E69E335
P 7750 950
F 0 "U5" H 7850 1025 50  0000 C CNN
F 1 "MC7809" H 7850 934 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-263-2" H 7750 950 50  0001 C CNN
F 3 "" H 7750 950 50  0001 C CNN
	1    7750 950 
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0126
U 1 1 5E69EE56
P 6550 2350
F 0 "#PWR0126" H 6550 2100 50  0001 C CNN
F 1 "GNDA" H 6555 2177 50  0000 C CNN
F 2 "" H 6550 2350 50  0001 C CNN
F 3 "" H 6550 2350 50  0001 C CNN
	1    6550 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0127
U 1 1 5E6A08E3
P 7850 1900
F 0 "#PWR0127" H 7850 1650 50  0001 C CNN
F 1 "GNDA" H 7855 1727 50  0000 C CNN
F 2 "" H 7850 1900 50  0001 C CNN
F 3 "" H 7850 1900 50  0001 C CNN
	1    7850 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0128
U 1 1 5E6A0B39
P 8700 1900
F 0 "#PWR0128" H 8700 1650 50  0001 C CNN
F 1 "GNDA" H 8705 1727 50  0000 C CNN
F 2 "" H 8700 1900 50  0001 C CNN
F 3 "" H 8700 1900 50  0001 C CNN
	1    8700 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 1750 7850 1900
$Comp
L Device:C C?
U 1 1 5E6B2D70
P 6550 1800
AR Path="/5E6B2D70" Ref="C?"  Part="1" 
AR Path="/5E65B39F/5E6B2D70" Ref="C?"  Part="1" 
AR Path="/5E699B57/5E6B2D70" Ref="C22"  Part="1" 
F 0 "C22" H 6665 1846 50  0000 L CNN
F 1 "2.2µF/25V/UL ESR" H 6665 1755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6588 1650 50  0001 C CNN
F 3 "~" H 6550 1800 50  0001 C CNN
	1    6550 1800
	1    0    0    -1  
$EndComp
Text HLabel 1650 1100 0    50   Input ~ 0
D+12V
$Comp
L Device:CP C?
U 1 1 5E6B4621
P 1950 1300
AR Path="/5E6B4621" Ref="C?"  Part="1" 
AR Path="/5E699B57/5E6B4621" Ref="C21"  Part="1" 
F 0 "C21" H 2068 1346 50  0000 L CNN
F 1 "470µF/16V" H 2068 1255 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 1988 1150 50  0001 C CNN
F 3 "~" H 1950 1300 50  0001 C CNN
	1    1950 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0129
U 1 1 5E6B56BB
P 1950 1900
F 0 "#PWR0129" H 1950 1650 50  0001 C CNN
F 1 "GNDA" H 1955 1727 50  0000 C CNN
F 2 "" H 1950 1900 50  0001 C CNN
F 3 "" H 1950 1900 50  0001 C CNN
	1    1950 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1450 1950 1900
Wire Wire Line
	1950 1100 1650 1100
Connection ~ 1950 1100
Wire Wire Line
	1950 1150 1950 1100
$Comp
L bass_amplifier:NIS5112 U7
U 1 1 5EB3AB2F
P 5400 1250
F 0 "U7" H 5425 1625 50  0000 C CNN
F 1 "NIS5112" H 5425 1534 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5200 1250 50  0001 C CNN
F 3 "" H 5200 1250 50  0001 C CNN
	1    5400 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 5EB3C253
P 6250 1450
F 0 "R15" V 6457 1450 50  0000 C CNN
F 1 "309" V 6366 1450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6180 1450 50  0001 C CNN
F 3 "~" H 6250 1450 50  0001 C CNN
	1    6250 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6100 1450 6000 1450
Wire Wire Line
	6400 1450 6550 1450
Wire Wire Line
	6550 1450 6550 1100
$Comp
L power:GNDA #PWR09
U 1 1 5EB3DA5C
P 4050 1500
F 0 "#PWR09" H 4050 1250 50  0001 C CNN
F 1 "GNDA" H 4055 1327 50  0000 C CNN
F 2 "" H 4050 1500 50  0001 C CNN
F 3 "" H 4050 1500 50  0001 C CNN
	1    4050 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 1100 8700 1100
Connection ~ 8700 1100
Wire Wire Line
	6000 1100 6550 1100
Connection ~ 6550 1100
$Comp
L Device:R R14
U 1 1 5EB4C5F5
P 4950 1850
F 0 "R14" H 5020 1896 50  0000 L CNN
F 1 "inf" H 5020 1805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4880 1850 50  0001 C CNN
F 3 "~" H 4950 1850 50  0001 C CNN
	1    4950 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 5EB4C85F
P 4650 1850
F 0 "R13" H 4720 1896 50  0000 L CNN
F 1 "inf" H 4720 1805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4580 1850 50  0001 C CNN
F 3 "~" H 4650 1850 50  0001 C CNN
	1    4650 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR011
U 1 1 5EB4CF36
P 4950 2050
F 0 "#PWR011" H 4950 1800 50  0001 C CNN
F 1 "GNDA" H 4955 1877 50  0000 C CNN
F 2 "" H 4950 2050 50  0001 C CNN
F 3 "" H 4950 2050 50  0001 C CNN
	1    4950 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 1700 4650 1600
Wire Wire Line
	4650 1600 4800 1600
Wire Wire Line
	4950 1600 4950 1700
Wire Wire Line
	4650 2000 3650 2000
Wire Wire Line
	3650 2000 3650 1100
Connection ~ 3650 1100
Wire Wire Line
	3650 1100 4850 1100
Wire Wire Line
	4850 1450 4800 1450
Wire Wire Line
	4800 1450 4800 1600
Connection ~ 4800 1600
Wire Wire Line
	4800 1600 4950 1600
Wire Wire Line
	4950 2000 4950 2050
$Comp
L Device:C C28
U 1 1 5EB5158E
P 4350 1550
F 0 "C28" H 4465 1596 50  0000 L CNN
F 1 "1µF" H 4465 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4388 1400 50  0001 C CNN
F 3 "~" H 4350 1550 50  0001 C CNN
	1    4350 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 1250 4050 1500
Wire Wire Line
	4050 1250 4850 1250
$Comp
L power:GNDA #PWR010
U 1 1 5EB5366A
P 4350 1750
F 0 "#PWR010" H 4350 1500 50  0001 C CNN
F 1 "GNDA" H 4355 1577 50  0000 C CNN
F 2 "" H 4350 1750 50  0001 C CNN
F 3 "" H 4350 1750 50  0001 C CNN
	1    4350 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1750 4350 1700
Wire Wire Line
	4350 1400 4350 1350
Wire Wire Line
	1950 1100 3650 1100
Wire Wire Line
	6550 1450 6550 1650
Connection ~ 6550 1450
Wire Wire Line
	4350 1350 4850 1350
$EndSCHEMATC
