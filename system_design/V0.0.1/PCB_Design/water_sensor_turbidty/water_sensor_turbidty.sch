EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Sensor_Optical:LDR03 R3
U 1 1 612C6C75
P 4850 3000
F 0 "R3" V 4525 3000 50  0000 C CNN
F 1 "LDR03" V 4616 3000 50  0000 C CNN
F 2 "OptoDevice:R_LDR_10x8.5mm_P7.6mm_Vertical" V 5025 3000 50  0001 C CNN
F 3 "http://www.elektronica-componenten.nl/WebRoot/StoreNL/Shops/61422969/54F1/BA0C/C664/31B9/2173/C0A8/2AB9/2AEF/LDR03IMP.pdf" H 4850 2950 50  0001 C CNN
	1    4850 3000
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 612C796F
P 4850 2400
F 0 "R2" V 4643 2400 50  0000 C CNN
F 1 "470" V 4734 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4780 2400 50  0001 C CNN
F 3 "~" H 4850 2400 50  0001 C CNN
	1    4850 2400
	0    1    1    0   
$EndComp
$Comp
L Device:LED D1
U 1 1 612C7C63
P 4200 2400
F 0 "D1" H 4193 2617 50  0000 C CNN
F 1 "LED" H 4193 2526 50  0000 C CNN
F 2 "LED_THT:LED_D2.0mm_W4.8mm_H2.5mm_FlatTop" H 4200 2400 50  0001 C CNN
F 3 "~" H 4200 2400 50  0001 C CNN
	1    4200 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2400 4350 2400
Wire Wire Line
	4050 2400 3850 2400
Wire Wire Line
	4050 3000 3850 3000
Wire Wire Line
	4350 3000 4550 3000
Wire Wire Line
	5000 2400 5000 2700
Wire Wire Line
	5000 2700 5450 2700
Wire Wire Line
	5000 3000 5200 3000
Wire Wire Line
	5200 3000 5200 2500
Wire Wire Line
	5200 2500 5450 2500
Wire Wire Line
	4550 3000 4550 3100
Connection ~ 4550 3000
Wire Wire Line
	4550 3000 4700 3000
$Comp
L Misc:railsforturbity U1
U 1 1 612CD71A
P 5600 2750
F 0 "U1" H 5778 2826 50  0000 L CNN
F 1 "railsforturbity" H 5778 2735 50  0000 L CNN
F 2 "water_sensor_turbidty:Rails" H 5600 2750 50  0001 C CNN
F 3 "" H 5600 2750 50  0001 C CNN
	1    5600 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 2900 5250 2900
Wire Wire Line
	5250 2900 5250 3100
Wire Wire Line
	5250 3100 4550 3100
Wire Wire Line
	3850 2400 3850 3000
Wire Wire Line
	3850 3000 3850 3250
Wire Wire Line
	3850 3250 5450 3250
Wire Wire Line
	5450 3250 5450 3050
Connection ~ 3850 3000
$Comp
L Device:R R1
U 1 1 612C73FA
P 4200 3000
F 0 "R1" V 3993 3000 50  0000 C CNN
F 1 "1K" V 4084 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4130 3000 50  0001 C CNN
F 3 "~" H 4200 3000 50  0001 C CNN
	1    4200 3000
	0    1    1    0   
$EndComp
$EndSCHEMATC
