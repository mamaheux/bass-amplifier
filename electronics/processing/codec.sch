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
Text HLabel 1100 850  0    50   Input ~ 0
ADC_input_A
$Comp
L Device:R R54
U 1 1 5E7D1EF9
P 1600 850
F 0 "R54" V 1393 850 50  0000 C CNN
F 1 "2k" V 1484 850 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1530 850 50  0001 C CNN
F 3 "~" H 1600 850 50  0001 C CNN
	1    1600 850 
	0    1    1    0   
$EndComp
$Comp
L Device:R R59
U 1 1 5E7D2378
P 1950 1100
F 0 "R59" H 1880 1054 50  0000 R CNN
F 1 "2k" H 1880 1145 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1880 1100 50  0001 C CNN
F 3 "~" H 1950 1100 50  0001 C CNN
	1    1950 1100
	-1   0    0    1   
$EndComp
$Comp
L Device:C C41
U 1 1 5E7D27CF
P 2300 850
F 0 "C41" V 2048 850 50  0000 C CNN
F 1 "10µF/50V" V 2139 850 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 2338 700 50  0001 C CNN
F 3 "~" H 2300 850 50  0001 C CNN
	1    2300 850 
	0    1    1    0   
$EndComp
$Comp
L Device:C C44
U 1 1 5E7D2D24
P 2650 1100
F 0 "C44" H 2535 1054 50  0000 R CNN
F 1 "220pF/50V" H 2535 1145 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2688 950 50  0001 C CNN
F 3 "~" H 2650 1100 50  0001 C CNN
	1    2650 1100
	-1   0    0    1   
$EndComp
Wire Wire Line
	1450 850  1100 850 
Wire Wire Line
	1750 850  1950 850 
Wire Wire Line
	1950 850  1950 950 
Connection ~ 1950 850 
Wire Wire Line
	1950 850  2150 850 
$Comp
L power:GNDA #PWR065
U 1 1 5E7D33FF
P 1950 1350
F 0 "#PWR065" H 1950 1100 50  0001 C CNN
F 1 "GNDA" H 1955 1177 50  0000 C CNN
F 2 "" H 1950 1350 50  0001 C CNN
F 3 "" H 1950 1350 50  0001 C CNN
	1    1950 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR069
U 1 1 5E7D35CB
P 2650 1350
F 0 "#PWR069" H 2650 1100 50  0001 C CNN
F 1 "GNDA" H 2655 1177 50  0000 C CNN
F 2 "" H 2650 1350 50  0001 C CNN
F 3 "" H 2650 1350 50  0001 C CNN
	1    2650 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1250 1950 1350
Wire Wire Line
	2650 1250 2650 1350
Wire Wire Line
	2650 950  2650 850 
Wire Wire Line
	2650 850  2450 850 
Wire Wire Line
	2650 850  2850 850 
Connection ~ 2650 850 
Text HLabel 1100 1950 0    50   Input ~ 0
ADC_input_B
$Comp
L Device:R R55
U 1 1 5E7D6626
P 1600 1950
F 0 "R55" V 1393 1950 50  0000 C CNN
F 1 "2k" V 1484 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1530 1950 50  0001 C CNN
F 3 "~" H 1600 1950 50  0001 C CNN
	1    1600 1950
	0    1    1    0   
$EndComp
$Comp
L Device:R R60
U 1 1 5E7D662C
P 1950 2200
F 0 "R60" H 1880 2154 50  0000 R CNN
F 1 "2k" H 1880 2245 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1880 2200 50  0001 C CNN
F 3 "~" H 1950 2200 50  0001 C CNN
	1    1950 2200
	-1   0    0    1   
$EndComp
$Comp
L Device:C C42
U 1 1 5E7D6632
P 2300 1950
F 0 "C42" V 2048 1950 50  0000 C CNN
F 1 "10µF/50V" V 2139 1950 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 2338 1800 50  0001 C CNN
F 3 "~" H 2300 1950 50  0001 C CNN
	1    2300 1950
	0    1    1    0   
$EndComp
$Comp
L Device:C C45
U 1 1 5E7D6638
P 2650 2200
F 0 "C45" H 2535 2154 50  0000 R CNN
F 1 "220pF/50V" H 2535 2245 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2688 2050 50  0001 C CNN
F 3 "~" H 2650 2200 50  0001 C CNN
	1    2650 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	1450 1950 1100 1950
Wire Wire Line
	1750 1950 1950 1950
Wire Wire Line
	1950 1950 1950 2050
Connection ~ 1950 1950
Wire Wire Line
	1950 1950 2150 1950
$Comp
L power:GNDA #PWR066
U 1 1 5E7D6643
P 1950 2450
F 0 "#PWR066" H 1950 2200 50  0001 C CNN
F 1 "GNDA" H 1955 2277 50  0000 C CNN
F 2 "" H 1950 2450 50  0001 C CNN
F 3 "" H 1950 2450 50  0001 C CNN
	1    1950 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR070
U 1 1 5E7D6649
P 2650 2450
F 0 "#PWR070" H 2650 2200 50  0001 C CNN
F 1 "GNDA" H 2655 2277 50  0000 C CNN
F 2 "" H 2650 2450 50  0001 C CNN
F 3 "" H 2650 2450 50  0001 C CNN
	1    2650 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 2350 1950 2450
Wire Wire Line
	2650 2350 2650 2450
Wire Wire Line
	2650 2050 2650 1950
Wire Wire Line
	2650 1950 2450 1950
Wire Wire Line
	2650 1950 2850 1950
Connection ~ 2650 1950
$Comp
L Device:C C40
U 1 1 5E7D808C
P 1350 4700
F 0 "C40" V 1098 4700 50  0000 C CNN
F 1 "3.3µF/25V" V 1189 4700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1388 4550 50  0001 C CNN
F 3 "~" H 1350 4700 50  0001 C CNN
	1    1350 4700
	0    1    1    0   
$EndComp
$Comp
L Device:R R56
U 1 1 5E7D83AA
P 1650 4950
F 0 "R56" H 1580 4904 50  0000 R CNN
F 1 "10k" H 1580 4995 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1580 4950 50  0001 C CNN
F 3 "~" H 1650 4950 50  0001 C CNN
	1    1650 4950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R61
U 1 1 5E7D873F
P 1950 4700
F 0 "R61" V 1743 4700 50  0000 C CNN
F 1 "470" V 1834 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1880 4700 50  0001 C CNN
F 3 "~" H 1950 4700 50  0001 C CNN
	1    1950 4700
	0    1    1    0   
$EndComp
$Comp
L power:GNDA #PWR063
U 1 1 5E7D9453
P 1650 5200
F 0 "#PWR063" H 1650 4950 50  0001 C CNN
F 1 "GNDA" H 1655 5027 50  0000 C CNN
F 2 "" H 1650 5200 50  0001 C CNN
F 3 "" H 1650 5200 50  0001 C CNN
	1    1650 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR068
U 1 1 5E7D974F
P 2350 5200
F 0 "#PWR068" H 2350 4950 50  0001 C CNN
F 1 "GNDA" H 2355 5027 50  0000 C CNN
F 2 "" H 2350 5200 50  0001 C CNN
F 3 "" H 2350 5200 50  0001 C CNN
	1    2350 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4700 1650 4700
Wire Wire Line
	1650 4700 1650 4800
Connection ~ 1650 4700
Wire Wire Line
	1650 4700 1800 4700
Wire Wire Line
	1650 5100 1650 5200
Wire Wire Line
	2350 4700 2100 4700
Wire Wire Line
	2350 4700 2350 4800
Wire Wire Line
	2350 5100 2350 5200
$Comp
L Device:C C43
U 1 1 5E7D8C62
P 2350 4950
F 0 "C43" H 2235 4904 50  0000 R CNN
F 1 "3600pF/50V" H 2235 4995 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2388 4800 50  0001 C CNN
F 3 "~" H 2350 4950 50  0001 C CNN
	1    2350 4950
	-1   0    0    1   
$EndComp
Text HLabel 5900 4600 2    50   Output ~ 0
DAC_output
Connection ~ 2350 4700
$Comp
L Device:R R63
U 1 1 5E87C20C
P 3050 4950
F 0 "R63" H 2980 4904 50  0000 R CNN
F 1 "10k" H 2980 4995 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2980 4950 50  0001 C CNN
F 3 "~" H 3050 4950 50  0001 C CNN
	1    3050 4950
	-1   0    0    1   
$EndComp
Wire Wire Line
	2350 4700 3050 4700
Wire Wire Line
	3050 4800 3050 4700
Connection ~ 3050 4700
Wire Wire Line
	3050 4700 3350 4700
$Comp
L power:GNDA #PWR072
U 1 1 5E88E619
P 3050 5200
F 0 "#PWR072" H 3050 4950 50  0001 C CNN
F 1 "GNDA" H 3055 5027 50  0000 C CNN
F 2 "" H 3050 5200 50  0001 C CNN
F 3 "" H 3050 5200 50  0001 C CNN
	1    3050 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 5100 3050 5200
$Comp
L Device:R R?
U 1 1 5E897234
P 3000 4100
AR Path="/5E5D245F/5E897234" Ref="R?"  Part="1" 
AR Path="/5E7D081A/5E897234" Ref="R?"  Part="1" 
AR Path="/5E94EB21/5E897234" Ref="R62"  Part="1" 
F 0 "R62" V 2793 4100 50  0000 C CNN
F 1 "3.09k" V 2884 4100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2930 4100 50  0001 C CNN
F 3 "~" H 3000 4100 50  0001 C CNN
	1    3000 4100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E89723A
P 3400 4100
AR Path="/5E5D245F/5E89723A" Ref="R?"  Part="1" 
AR Path="/5E7D081A/5E89723A" Ref="R?"  Part="1" 
AR Path="/5E94EB21/5E89723A" Ref="R64"  Part="1" 
F 0 "R64" V 3193 4100 50  0000 C CNN
F 1 "15.4k" V 3284 4100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3330 4100 50  0001 C CNN
F 3 "~" H 3400 4100 50  0001 C CNN
	1    3400 4100
	0    1    1    0   
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 5E897240
P 2800 4150
AR Path="/5E5D245F/5E897240" Ref="#PWR?"  Part="1" 
AR Path="/5E7D081A/5E897240" Ref="#PWR?"  Part="1" 
AR Path="/5E94EB21/5E897240" Ref="#PWR071"  Part="1" 
F 0 "#PWR071" H 2800 3900 50  0001 C CNN
F 1 "GNDA" H 2805 3977 50  0000 C CNN
F 2 "" H 2800 4150 50  0001 C CNN
F 3 "" H 2800 4150 50  0001 C CNN
	1    2800 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 4100 2800 4100
Wire Wire Line
	3200 4100 3250 4100
Wire Wire Line
	3200 4100 3200 4500
Wire Wire Line
	3200 4100 3150 4100
Connection ~ 3200 4100
Wire Wire Line
	2800 4100 2800 4150
Wire Wire Line
	3200 4500 3350 4500
Wire Wire Line
	4350 4100 4350 4600
Wire Wire Line
	4350 4600 4150 4600
Wire Wire Line
	3550 4100 4350 4100
$Comp
L Device:C C?
U 1 1 5E8A3ADF
P 4600 4600
AR Path="/5E5D245F/5E8A3ADF" Ref="C?"  Part="1" 
AR Path="/5E7D081A/5E8A3ADF" Ref="C?"  Part="1" 
AR Path="/5E94EB21/5E8A3ADF" Ref="C46"  Part="1" 
F 0 "C46" V 4348 4600 50  0000 C CNN
F 1 "10µF/50V" V 4439 4600 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 4638 4450 50  0001 C CNN
F 3 "~" H 4600 4600 50  0001 C CNN
	1    4600 4600
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 4600 4450 4600
Connection ~ 4350 4600
$Comp
L Device:R R?
U 1 1 5E8A4D26
P 5050 4600
AR Path="/5E5D245F/5E8A4D26" Ref="R?"  Part="1" 
AR Path="/5E7D081A/5E8A4D26" Ref="R?"  Part="1" 
AR Path="/5E94EB21/5E8A4D26" Ref="R67"  Part="1" 
F 0 "R67" V 4843 4600 50  0000 C CNN
F 1 "560" V 4934 4600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4980 4600 50  0001 C CNN
F 3 "~" H 5050 4600 50  0001 C CNN
	1    5050 4600
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 4600 4750 4600
Text GLabel 3950 5400 2    50   Input ~ 0
A+3.3V
Wire Wire Line
	3950 5400 3950 5550
Wire Wire Line
	3550 5750 3400 5750
$Comp
L Device:R R65
U 1 1 5E8B10D0
P 4750 6200
F 0 "R65" H 4680 6154 50  0000 R CNN
F 1 "10k" H 4680 6245 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4680 6200 50  0001 C CNN
F 3 "~" H 4750 6200 50  0001 C CNN
	1    4750 6200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R68
U 1 1 5E8B174C
P 5100 5950
F 0 "R68" V 5307 5950 50  0000 C CNN
F 1 "2k" V 5216 5950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5030 5950 50  0001 C CNN
F 3 "~" H 5100 5950 50  0001 C CNN
	1    5100 5950
	0    -1   -1   0   
$EndComp
Text GLabel 4750 6500 0    50   Input ~ 0
A-15V
Wire Wire Line
	4750 6350 4750 6500
Wire Wire Line
	5350 5950 5250 5950
Wire Wire Line
	4750 5950 4750 6050
Wire Wire Line
	4750 5950 4950 5950
Wire Wire Line
	3950 5950 4750 5950
Connection ~ 4750 5950
$Comp
L power:GNDA #PWR073
U 1 1 5E8F55B0
P 5650 6250
F 0 "#PWR073" H 5650 6000 50  0001 C CNN
F 1 "GNDA" H 5655 6077 50  0000 C CNN
F 2 "" H 5650 6250 50  0001 C CNN
F 3 "" H 5650 6250 50  0001 C CNN
	1    5650 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 6150 5650 6250
Wire Wire Line
	5650 5750 5650 4600
Wire Wire Line
	5650 4600 5200 4600
Wire Wire Line
	5650 4600 5900 4600
Connection ~ 5650 4600
$Comp
L bass_amplifier:CS4270 U9
U 1 1 5E916FEC
P 6500 2100
F 0 "U9" H 6050 1150 50  0000 C CNN
F 1 "CS4270" H 6100 1050 50  0000 C CNN
F 2 "Package_SO:TSSOP-24_4.4x7.8mm_P0.65mm" H 6500 2100 50  0001 C CNN
F 3 "https://statics.cirrus.com/pubs/proDatasheet/CS4270_F1.pdf" V 6500 3100 50  0001 C CNN
	1    6500 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR077
U 1 1 5E9692A0
P 6700 3200
F 0 "#PWR077" H 6700 2950 50  0001 C CNN
F 1 "GNDA" H 6705 3027 50  0000 C CNN
F 2 "" H 6700 3200 50  0001 C CNN
F 3 "" H 6700 3200 50  0001 C CNN
	1    6700 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3000 6600 3100
$Comp
L power:GNDD #PWR075
U 1 1 5E96AB4F
P 6400 3200
F 0 "#PWR075" H 6400 2950 50  0001 C CNN
F 1 "GNDD" H 6404 3045 50  0000 C CNN
F 2 "" H 6400 3200 50  0001 C CNN
F 3 "" H 6400 3200 50  0001 C CNN
	1    6400 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3000 6500 3100
Wire Wire Line
	6500 3100 6400 3100
Wire Wire Line
	6400 3100 6400 3200
Wire Wire Line
	6600 3100 6700 3100
Wire Wire Line
	6700 3100 6700 3200
$Comp
L Device:R R70
U 1 1 5E96EF82
P 6550 3700
F 0 "R70" V 6343 3700 50  0000 C CNN
F 1 "0" V 6434 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6480 3700 50  0001 C CNN
F 3 "~" H 6550 3700 50  0001 C CNN
	1    6550 3700
	0    1    1    0   
$EndComp
$Comp
L power:GNDD #PWR074
U 1 1 5E96F1C2
P 6350 3750
F 0 "#PWR074" H 6350 3500 50  0001 C CNN
F 1 "GNDD" H 6354 3595 50  0000 C CNN
F 2 "" H 6350 3750 50  0001 C CNN
F 3 "" H 6350 3750 50  0001 C CNN
	1    6350 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3750 6350 3700
Wire Wire Line
	6350 3700 6400 3700
Wire Wire Line
	6700 3700 6750 3700
Wire Wire Line
	6750 3700 6750 3750
$Comp
L power:GNDA #PWR078
U 1 1 5E97136A
P 6750 3750
F 0 "#PWR078" H 6750 3500 50  0001 C CNN
F 1 "GNDA" H 6755 3577 50  0000 C CNN
F 2 "" H 6750 3750 50  0001 C CNN
F 3 "" H 6750 3750 50  0001 C CNN
	1    6750 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 4700 1150 4700
Text Label 7250 1900 0    50   ~ 0
OUTA
Text Label 7250 2000 0    50   ~ 0
OUTB
Text Label 1000 4700 2    50   ~ 0
OUTA
Text Label 950  5900 2    50   ~ 0
OUTB
Wire Wire Line
	7250 1900 7100 1900
Wire Wire Line
	7100 2000 7250 2000
$Comp
L Device:C C39
U 1 1 5E99E853
P 1300 5900
F 0 "C39" V 1048 5900 50  0000 C CNN
F 1 "3.3µF/25V" V 1139 5900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1338 5750 50  0001 C CNN
F 3 "~" H 1300 5900 50  0001 C CNN
	1    1300 5900
	0    1    1    0   
$EndComp
$Comp
L Device:R R57
U 1 1 5E99EDD3
P 1650 6150
F 0 "R57" H 1580 6104 50  0000 R CNN
F 1 "10k" H 1580 6195 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1580 6150 50  0001 C CNN
F 3 "~" H 1650 6150 50  0001 C CNN
	1    1650 6150
	-1   0    0    1   
$EndComp
$Comp
L power:GNDA #PWR064
U 1 1 5E99F1B0
P 1650 6400
F 0 "#PWR064" H 1650 6150 50  0001 C CNN
F 1 "GNDA" H 1655 6227 50  0000 C CNN
F 2 "" H 1650 6400 50  0001 C CNN
F 3 "" H 1650 6400 50  0001 C CNN
	1    1650 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 6400 1650 6300
Wire Wire Line
	1650 6000 1650 5900
Wire Wire Line
	1650 5900 1450 5900
Wire Wire Line
	1150 5900 950  5900
$Comp
L Device:R R58
U 1 1 5E9A303E
P 1900 5900
F 0 "R58" V 1693 5900 50  0000 C CNN
F 1 "470" V 1784 5900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1830 5900 50  0001 C CNN
F 3 "~" H 1900 5900 50  0001 C CNN
	1    1900 5900
	0    1    1    0   
$EndComp
$Comp
L power:GNDA #PWR067
U 1 1 5E9A4FD5
P 2300 6200
F 0 "#PWR067" H 2300 5950 50  0001 C CNN
F 1 "GNDA" H 2305 6027 50  0000 C CNN
F 2 "" H 2300 6200 50  0001 C CNN
F 3 "" H 2300 6200 50  0001 C CNN
	1    2300 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 6200 2300 6100
Wire Wire Line
	2300 6100 2400 6100
$Comp
L Connector:Conn_01x03_Male J7
U 1 1 5E9AC650
P 2600 6000
F 0 "J7" H 2572 5932 50  0000 R CNN
F 1 "Conn_01x03_Male" H 2572 6023 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 2600 6000 50  0001 C CNN
F 3 "~" H 2600 6000 50  0001 C CNN
	1    2600 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	2400 6000 2300 6000
Text Label 2300 6000 2    50   ~ 0
~MUTEB
Wire Wire Line
	1750 5900 1650 5900
Connection ~ 1650 5900
Text Label 7250 2300 0    50   ~ 0
~MUTEB
Text Label 7250 2200 0    50   ~ 0
~MUTEA
Text Label 3300 5750 2    50   ~ 0
~MUTEA
Wire Wire Line
	7250 2200 7100 2200
Wire Wire Line
	7100 2300 7250 2300
Text Label 3000 850  0    50   ~ 0
INA
Text Label 3000 1950 0    50   ~ 0
INB
Text Label 5750 1900 2    50   ~ 0
INA
Text Label 5750 2000 2    50   ~ 0
INB
Wire Wire Line
	5750 1900 5900 1900
Wire Wire Line
	5900 2000 5750 2000
Wire Wire Line
	5900 2400 5750 2400
Wire Wire Line
	5900 2500 5750 2500
Wire Wire Line
	5900 2600 5750 2600
Wire Wire Line
	5900 2700 5750 2700
Wire Wire Line
	5900 1700 5750 1700
Wire Wire Line
	5750 1600 5900 1600
Wire Wire Line
	5900 1500 5750 1500
Wire Wire Line
	5750 1400 5900 1400
Text HLabel 4750 2200 0    50   BiDi ~ 0
SDA
Text HLabel 4750 2300 0    50   Input ~ 0
SCL
Text HLabel 5750 2400 0    50   Input ~ 0
AD0
Text HLabel 5750 2500 0    50   Input ~ 0
AD1
Text HLabel 5750 2600 0    50   Input ~ 0
AD2
Text HLabel 5750 2700 0    50   Input ~ 0
~RST
$Comp
L power:GNDD #PWR076
U 1 1 5E9FCA31
P 6400 3200
F 0 "#PWR076" H 6400 2950 50  0001 C CNN
F 1 "GNDD" H 6404 3045 50  0000 C CNN
F 2 "" H 6400 3200 50  0001 C CNN
F 3 "" H 6400 3200 50  0001 C CNN
	1    6400 3200
	1    0    0    -1  
$EndComp
Connection ~ 6400 3200
$Comp
L power:GNDA #PWR080
U 1 1 5EA08634
P 8900 2850
F 0 "#PWR080" H 8900 2600 50  0001 C CNN
F 1 "GNDA" H 8905 2677 50  0000 C CNN
F 2 "" H 8900 2850 50  0001 C CNN
F 3 "" H 8900 2850 50  0001 C CNN
	1    8900 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C48
U 1 1 5EA08EBB
P 7450 3050
F 0 "C48" H 7565 3096 50  0000 L CNN
F 1 "0.1µF/25V" H 7565 3005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7488 2900 50  0001 C CNN
F 3 "~" H 7450 3050 50  0001 C CNN
	1    7450 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C50
U 1 1 5EA09614
P 8200 3050
F 0 "C50" H 8315 3096 50  0000 L CNN
F 1 "10µF/10V" H 8315 3005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8238 2900 50  0001 C CNN
F 3 "~" H 8200 3050 50  0001 C CNN
	1    8200 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C49
U 1 1 5EA09910
P 8200 2550
F 0 "C49" H 8315 2596 50  0000 L CNN
F 1 "47µF/10V" H 8315 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8238 2400 50  0001 C CNN
F 3 "~" H 8200 2550 50  0001 C CNN
	1    8200 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C47
U 1 1 5EA09D47
P 7450 2550
F 0 "C47" H 7565 2596 50  0000 L CNN
F 1 "0.1µF/25V" H 7565 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7488 2400 50  0001 C CNN
F 3 "~" H 7450 2550 50  0001 C CNN
	1    7450 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2700 7200 2700
Wire Wire Line
	7200 2700 7200 3250
Wire Wire Line
	7200 3250 7450 3250
Wire Wire Line
	7450 3200 7450 3250
Wire Wire Line
	7450 2400 7450 2350
Wire Wire Line
	7450 2350 7200 2350
Wire Wire Line
	7200 2350 7200 2600
Wire Wire Line
	7200 2600 7100 2600
Wire Wire Line
	8200 2350 8200 2400
Wire Wire Line
	8200 2700 8200 2800
Connection ~ 8200 2800
Wire Wire Line
	8200 2800 8200 2900
Wire Wire Line
	8200 3200 8200 3250
Text GLabel 8950 650  0    50   Input ~ 0
A+3.3V
Text GLabel 6500 1100 1    50   Input ~ 0
A+3.3V
Wire Wire Line
	6500 1100 6500 1200
Text HLabel 6400 1100 1    50   Input ~ 0
MCU_3.3V
Wire Wire Line
	6400 1100 6400 1200
Text HLabel 6600 1100 1    50   Input ~ 0
MCU_3.3V
Wire Wire Line
	6600 1100 6600 1200
$Comp
L Device:C C53
U 1 1 5EA3DA48
P 9800 900
F 0 "C53" H 9915 946 50  0000 L CNN
F 1 "0.1µF/25V" H 9915 855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9838 750 50  0001 C CNN
F 3 "~" H 9800 900 50  0001 C CNN
	1    9800 900 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C51
U 1 1 5EA3E947
P 9100 900
F 0 "C51" H 9215 946 50  0000 L CNN
F 1 "1µF/6.3V" H 9215 855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9138 750 50  0001 C CNN
F 3 "~" H 9100 900 50  0001 C CNN
	1    9100 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 650  9100 650 
Wire Wire Line
	9100 650  9100 750 
Wire Wire Line
	9800 650  9800 750 
$Comp
L power:GNDA #PWR081
U 1 1 5EA45747
P 9100 1150
F 0 "#PWR081" H 9100 900 50  0001 C CNN
F 1 "GNDA" H 9105 977 50  0000 C CNN
F 2 "" H 9100 1150 50  0001 C CNN
F 3 "" H 9100 1150 50  0001 C CNN
	1    9100 1150
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR083
U 1 1 5EA46509
P 9800 1150
F 0 "#PWR083" H 9800 900 50  0001 C CNN
F 1 "GNDA" H 9805 977 50  0000 C CNN
F 2 "" H 9800 1150 50  0001 C CNN
F 3 "" H 9800 1150 50  0001 C CNN
	1    9800 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 1150 9800 1050
Wire Wire Line
	9100 1050 9100 1150
$Comp
L Device:C C54
U 1 1 5EA59036
P 9800 1750
F 0 "C54" H 9915 1796 50  0000 L CNN
F 1 "0.1µF/25V" H 9915 1705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9838 1600 50  0001 C CNN
F 3 "~" H 9800 1750 50  0001 C CNN
	1    9800 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C52
U 1 1 5EA5903C
P 9100 1750
F 0 "C52" H 9215 1796 50  0000 L CNN
F 1 "1µF/6.3V" H 9215 1705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9138 1600 50  0001 C CNN
F 3 "~" H 9100 1750 50  0001 C CNN
	1    9100 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 1500 9100 1500
Wire Wire Line
	9100 1500 9100 1600
Wire Wire Line
	9800 1500 9800 1600
Wire Wire Line
	9800 2000 9800 1900
Text HLabel 8950 1500 0    50   Input ~ 0
MCU_3.3V
Text HLabel 4950 2850 0    50   Input ~ 0
MCU_3.3V
Wire Wire Line
	9100 1900 9100 2000
$Comp
L power:GNDD #PWR082
U 1 1 5EA644D1
P 9100 2000
F 0 "#PWR082" H 9100 1750 50  0001 C CNN
F 1 "GNDD" H 9104 1845 50  0000 C CNN
F 2 "" H 9100 2000 50  0001 C CNN
F 3 "" H 9100 2000 50  0001 C CNN
	1    9100 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR084
U 1 1 5EA66AD4
P 9800 2000
F 0 "#PWR084" H 9800 1750 50  0001 C CNN
F 1 "GNDD" H 9804 1845 50  0000 C CNN
F 2 "" H 9800 2000 50  0001 C CNN
F 3 "" H 9800 2000 50  0001 C CNN
	1    9800 2000
	1    0    0    -1  
$EndComp
Text HLabel 5750 1400 0    50   Input ~ 0
SDIN
Text HLabel 5750 1500 0    50   Input ~ 0
LRCLK
Text HLabel 5750 1600 0    50   Input ~ 0
MCLK
Text HLabel 5750 1700 0    50   Input ~ 0
SCLK
Text HLabel 8100 1400 2    50   Output ~ 0
SDOUT
$Comp
L Device:R R69
U 1 1 5EA71BEF
P 5300 2600
F 0 "R69" H 5230 2554 50  0000 R CNN
F 1 "2k" H 5230 2645 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5230 2600 50  0001 C CNN
F 3 "~" H 5300 2600 50  0001 C CNN
	1    5300 2600
	-1   0    0    1   
$EndComp
$Comp
L Device:R R66
U 1 1 5EA72438
P 5050 2600
F 0 "R66" H 4980 2554 50  0000 R CNN
F 1 "2k" H 4980 2645 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4980 2600 50  0001 C CNN
F 3 "~" H 5050 2600 50  0001 C CNN
	1    5050 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	4750 2300 5050 2300
Wire Wire Line
	5050 2450 5050 2300
Connection ~ 5050 2300
Wire Wire Line
	5050 2300 5900 2300
Wire Wire Line
	5300 2450 5300 2200
Wire Wire Line
	5300 2200 5900 2200
Wire Wire Line
	5300 2200 4750 2200
Connection ~ 5300 2200
Wire Wire Line
	5050 2750 5050 2850
Wire Wire Line
	5050 2850 4950 2850
Wire Wire Line
	5050 2850 5300 2850
Wire Wire Line
	5300 2850 5300 2750
Connection ~ 5050 2850
$Comp
L power:GNDD #PWR079
U 1 1 5EAECCA4
P 7950 1900
F 0 "#PWR079" H 7950 1650 50  0001 C CNN
F 1 "GNDD" H 7954 1745 50  0000 C CNN
F 2 "" H 7950 1900 50  0001 C CNN
F 3 "" H 7950 1900 50  0001 C CNN
	1    7950 1900
	1    0    0    -1  
$EndComp
Text HLabel 7950 900  1    50   Input ~ 0
MCU_3.3V
$Comp
L Device:R R72
U 1 1 5EAEF6FE
P 7950 1650
F 0 "R72" H 7880 1604 50  0000 R CNN
F 1 "inf or 47k" H 7880 1695 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7880 1650 50  0001 C CNN
F 3 "~" H 7950 1650 50  0001 C CNN
	1    7950 1650
	-1   0    0    1   
$EndComp
$Comp
L Device:R R71
U 1 1 5EAF82EB
P 7950 1150
F 0 "R71" H 7880 1104 50  0000 R CNN
F 1 "inf or 47k" H 7880 1195 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7880 1150 50  0001 C CNN
F 3 "~" H 7950 1150 50  0001 C CNN
	1    7950 1150
	-1   0    0    1   
$EndComp
Wire Wire Line
	7950 1300 7950 1400
Wire Wire Line
	7950 1400 8100 1400
Connection ~ 7950 1400
Wire Wire Line
	7950 1400 7950 1500
Wire Wire Line
	7950 1900 7950 1800
Wire Wire Line
	7950 1000 7950 900 
Text Notes 8050 1900 0    50   ~ 0
47k slave mode\n(stand-alone mode)
Text Notes 8050 1050 0    50   ~ 0
47k master mode\n(stand-alone mode)
Wire Wire Line
	7100 1400 7950 1400
$Comp
L Connector:TestPoint TP?
U 1 1 5E97B106
P 2850 750
AR Path="/5E5D245F/5E97B106" Ref="TP?"  Part="1" 
AR Path="/5E5D245F/5EAAF9C0/5E97B106" Ref="TP?"  Part="1" 
AR Path="/5E94EB21/5E97B106" Ref="TP29"  Part="1" 
F 0 "TP29" H 2908 868 50  0000 L CNN
F 1 "TP" H 2908 777 50  0000 L CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x01_P1.00mm_Vertical" H 3050 750 50  0001 C CNN
F 3 "~" H 3050 750 50  0001 C CNN
	1    2850 750 
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5E97F35A
P 2850 1850
AR Path="/5E5D245F/5E97F35A" Ref="TP?"  Part="1" 
AR Path="/5E5D245F/5EAAF9C0/5E97F35A" Ref="TP?"  Part="1" 
AR Path="/5E94EB21/5E97F35A" Ref="TP30"  Part="1" 
F 0 "TP30" H 2908 1968 50  0000 L CNN
F 1 "TP" H 2908 1877 50  0000 L CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x01_P1.00mm_Vertical" H 3050 1850 50  0001 C CNN
F 3 "~" H 3050 1850 50  0001 C CNN
	1    2850 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 750  2850 850 
Connection ~ 2850 850 
Wire Wire Line
	2850 850  3000 850 
Wire Wire Line
	2850 1850 2850 1950
Connection ~ 2850 1950
Wire Wire Line
	2850 1950 3000 1950
$Comp
L Connector:TestPoint TP?
U 1 1 5E98BFE2
P 1150 4350
AR Path="/5E5D245F/5E98BFE2" Ref="TP?"  Part="1" 
AR Path="/5E5D245F/5EAAF9C0/5E98BFE2" Ref="TP?"  Part="1" 
AR Path="/5E94EB21/5E98BFE2" Ref="TP28"  Part="1" 
F 0 "TP28" H 1208 4468 50  0000 L CNN
F 1 "TP" H 1208 4377 50  0000 L CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x01_P1.00mm_Vertical" H 1350 4350 50  0001 C CNN
F 3 "~" H 1350 4350 50  0001 C CNN
	1    1150 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 4350 1150 4700
Connection ~ 1150 4700
Wire Wire Line
	1150 4700 1200 4700
Wire Wire Line
	2050 5900 2400 5900
$Comp
L Connector:TestPoint TP?
U 1 1 5E99A2BF
P 3400 5600
AR Path="/5E5D245F/5E99A2BF" Ref="TP?"  Part="1" 
AR Path="/5E5D245F/5EAAF9C0/5E99A2BF" Ref="TP?"  Part="1" 
AR Path="/5E94EB21/5E99A2BF" Ref="TP31"  Part="1" 
F 0 "TP31" H 3458 5718 50  0000 L CNN
F 1 "TP" H 3458 5627 50  0000 L CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x01_P1.00mm_Vertical" H 3600 5600 50  0001 C CNN
F 3 "~" H 3600 5600 50  0001 C CNN
	1    3400 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 5600 3400 5750
Connection ~ 3400 5750
Wire Wire Line
	3400 5750 3300 5750
Wire Wire Line
	7450 2700 7450 2800
Wire Wire Line
	7450 3250 8200 3250
Connection ~ 7450 3250
Wire Wire Line
	7450 2800 8200 2800
Connection ~ 7450 2800
Wire Wire Line
	7450 2800 7450 2900
Wire Wire Line
	7450 2350 8200 2350
Connection ~ 7450 2350
Wire Wire Line
	8900 2800 8900 2850
Wire Wire Line
	8200 2800 8900 2800
Wire Wire Line
	9100 1500 9800 1500
Connection ~ 9100 1500
Wire Wire Line
	9100 650  9800 650 
Connection ~ 9100 650 
$Comp
L Device:Q_PNP_BEC_BRT Q3
U 1 1 5EA39591
P 3900 5750
F 0 "Q3" H 4040 5704 50  0000 L CNN
F 1 "MMUN2111LT1" H 4040 5795 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3900 5750 50  0001 C CNN
F 3 "~" H 3900 5750 50  0001 C CNN
	1    3900 5750
	1    0    0    1   
$EndComp
$Comp
L Device:Q_NPN_BEC Q4
U 1 1 5EA45A3B
P 5550 5950
F 0 "Q4" H 5740 5996 50  0000 L CNN
F 1 "MMBT2222A" H 5740 5905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5750 6050 50  0001 C CNN
F 3 "~" H 5550 5950 50  0001 C CNN
	1    5550 5950
	1    0    0    -1  
$EndComp
$Comp
L bass_amplifier:TL072 U10
U 1 1 5E9BC3DB
P 3600 4600
F 0 "U10" H 3800 4800 50  0000 L CNN
F 1 "TL072" H 3850 4450 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3600 4600 50  0001 C CNN
F 3 "" H 3600 4600 50  0001 C CNN
	1    3600 4600
	1    0    0    -1  
$EndComp
Text GLabel 3700 4250 0    50   Input ~ 0
A+15V
Text GLabel 3700 4950 0    50   Input ~ 0
A-15V
Text Notes 4050 4200 0    50   ~ 0
6x gain
$EndSCHEMATC
