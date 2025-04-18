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
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 62AE0AA1
P 6000 3600
F 0 "A1" H 6000 2511 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 6000 2420 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6000 3600 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 6000 3600 50  0001 C CNN
	1    6000 3600
	1    0    0    -1  
$EndComp
$Comp
L water_sensor:SWITCH U4
U 1 1 62AE3032
P 5300 2100
F 0 "U4" H 5478 1963 50  0000 L CNN
F 1 "SWITCH" H 5478 1872 50  0000 L CNN
F 2 "Water_Quality_Sensor:slide_switch" H 5300 2100 50  0001 C CNN
F 3 "" H 5300 2100 50  0001 C CNN
	1    5300 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 2400 5900 2400
Wire Wire Line
	5900 2400 5900 2600
NoConn ~ 5200 2400
$Comp
L water_sensor:BATTERY U3
U 1 1 62AE56C9
P 4800 2250
F 0 "U3" H 4708 2225 50  0000 C CNN
F 1 "BATTERY" H 4708 2134 50  0000 C CNN
F 2 "Water_Quality_Sensor:battery_input" H 4650 2200 50  0001 C CNN
F 3 "" H 4650 2200 50  0001 C CNN
	1    4800 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2600 5300 2600
Wire Wire Line
	5300 2600 5300 2400
$Comp
L power:GND #PWR02
U 1 1 62AE69BF
P 4900 2500
F 0 "#PWR02" H 4900 2250 50  0001 C CNN
F 1 "GND" V 4905 2372 50  0000 R CNN
F 2 "" H 4900 2500 50  0001 C CNN
F 3 "" H 4900 2500 50  0001 C CNN
	1    4900 2500
	0    -1   -1   0   
$EndComp
$Comp
L water_sensor:PH U5
U 1 1 62AE78A0
P 7200 3050
F 0 "U5" H 7378 2913 50  0000 L CNN
F 1 "PH" H 7378 2822 50  0000 L CNN
F 2 "Water_Quality_Sensor:phraails" H 7400 2950 50  0001 C CNN
F 3 "" H 7400 2950 50  0001 C CNN
	1    7200 3050
	1    0    0    -1  
$EndComp
$Comp
L water_sensor:TDS U7
U 1 1 62AE9C64
P 8000 3050
F 0 "U7" H 8178 2913 50  0000 L CNN
F 1 "TDS" H 8178 2822 50  0000 L CNN
F 2 "Water_Quality_Sensor:sensor_rails" H 8200 2950 50  0001 C CNN
F 3 "" H 8200 2950 50  0001 C CNN
	1    8000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3600 6500 3600
$Comp
L power:GND #PWR05
U 1 1 62AEA937
P 7300 3350
F 0 "#PWR05" H 7300 3100 50  0001 C CNN
F 1 "GND" H 7305 3177 50  0000 C CNN
F 2 "" H 7300 3350 50  0001 C CNN
F 3 "" H 7300 3350 50  0001 C CNN
	1    7300 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 3700 6500 3700
Wire Wire Line
	7100 3350 7100 3600
Wire Wire Line
	7900 3350 7900 3700
$Comp
L power:GND #PWR06
U 1 1 62AEC4AB
P 8100 3350
F 0 "#PWR06" H 8100 3100 50  0001 C CNN
F 1 "GND" H 8105 3177 50  0000 C CNN
F 2 "" H 8100 3350 50  0001 C CNN
F 3 "" H 8100 3350 50  0001 C CNN
	1    8100 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3350 7200 3600
Wire Wire Line
	7200 3600 7650 3600
Wire Wire Line
	7650 3600 7650 2500
Wire Wire Line
	7650 2500 6200 2500
Wire Wire Line
	6200 2500 6200 2600
Wire Wire Line
	8500 2500 7650 2500
Connection ~ 7650 2500
$Comp
L water_sensor:RTC U8
U 1 1 62AEEE59
P 8400 3700
F 0 "U8" H 8728 3563 50  0000 L CNN
F 1 "RTC" H 8728 3472 50  0000 L CNN
F 2 "Water_Quality_Sensor:RTC" H 8750 3600 50  0001 C CNN
F 3 "" H 8750 3600 50  0001 C CNN
	1    8400 3700
	1    0    0    -1  
$EndComp
NoConn ~ 8100 4050
NoConn ~ 8200 4050
Wire Wire Line
	8000 3350 8000 3600
Wire Wire Line
	8000 3600 8500 3600
Wire Wire Line
	8500 3600 8500 2500
Wire Wire Line
	8300 4050 8300 4100
Wire Wire Line
	8300 4100 6500 4100
Wire Wire Line
	8400 4050 8400 4200
Wire Wire Line
	8400 4200 7400 4200
Wire Wire Line
	7400 4200 7400 4000
Wire Wire Line
	7400 4000 6500 4000
$Comp
L power:GND #PWR07
U 1 1 62AF5E42
P 8600 4050
F 0 "#PWR07" H 8600 3800 50  0001 C CNN
F 1 "GND" H 8605 3877 50  0000 C CNN
F 2 "" H 8600 4050 50  0001 C CNN
F 3 "" H 8600 4050 50  0001 C CNN
	1    8600 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4050 8500 4300
Wire Wire Line
	8500 4300 9000 4300
Wire Wire Line
	9000 4300 9000 2350
Wire Wire Line
	9000 2350 6200 2350
Wire Wire Line
	6200 2350 6200 2500
Connection ~ 6200 2500
$Comp
L water_sensor:TURBIDITY U6
U 1 1 62AF8F9D
P 7200 4150
F 0 "U6" H 7328 3951 50  0000 L CNN
F 1 "TURBIDITY" H 7328 3860 50  0000 L CNN
F 2 "Water_Quality_Sensor:turbidity_rails" H 7350 3950 50  0001 C CNN
F 3 "" H 7350 3950 50  0001 C CNN
	1    7200 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 4300 6500 4300
$Comp
L power:GND #PWR04
U 1 1 62AFA267
P 7050 4500
F 0 "#PWR04" H 7050 4250 50  0001 C CNN
F 1 "GND" V 7055 4372 50  0000 R CNN
F 2 "" H 7050 4500 50  0001 C CNN
F 3 "" H 7050 4500 50  0001 C CNN
	1    7050 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	7050 4400 6700 4400
Wire Wire Line
	6700 4400 6700 4650
Wire Wire Line
	6700 4650 9000 4650
Wire Wire Line
	9000 4650 9000 4300
Connection ~ 9000 4300
$Comp
L power:GND #PWR03
U 1 1 62AFBDD6
P 6050 4950
F 0 "#PWR03" H 6050 4700 50  0001 C CNN
F 1 "GND" H 6055 4777 50  0000 C CNN
F 2 "" H 6050 4950 50  0001 C CNN
F 3 "" H 6050 4950 50  0001 C CNN
	1    6050 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 4950 6000 4950
Wire Wire Line
	6000 4950 6000 4600
Wire Wire Line
	6100 4600 6100 4950
Wire Wire Line
	6100 4950 6050 4950
Connection ~ 6050 4950
$Comp
L water_sensor:SD U2
U 1 1 62AFDFDA
P 4450 4300
F 0 "U2" H 4728 4079 50  0000 L CNN
F 1 "SD" H 4728 3988 50  0000 L CNN
F 2 "Water_Quality_Sensor:SD" H 3900 4050 50  0001 C CNN
F 3 "" H 3900 4050 50  0001 C CNN
	1    4450 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 4400 5000 4400
Wire Wire Line
	5000 4400 5000 5300
Wire Wire Line
	5000 5300 9250 5300
Wire Wire Line
	9250 5300 9250 2100
Wire Wire Line
	9250 2100 6100 2100
Wire Wire Line
	6100 2100 6100 2600
Wire Wire Line
	4500 4400 4500 4000
Wire Wire Line
	4500 4000 5500 4000
Wire Wire Line
	4400 4400 4400 4100
Wire Wire Line
	4400 4100 5500 4100
Wire Wire Line
	4300 4400 4300 4300
Wire Wire Line
	4300 4300 5500 4300
Wire Wire Line
	4200 4400 4200 4200
Wire Wire Line
	4200 4200 5500 4200
$Comp
L power:GND #PWR01
U 1 1 62B066E8
P 4100 4400
F 0 "#PWR01" H 4100 4150 50  0001 C CNN
F 1 "GND" H 4105 4227 50  0000 C CNN
F 2 "" H 4100 4400 50  0001 C CNN
F 3 "" H 4100 4400 50  0001 C CNN
	1    4100 4400
	-1   0    0    1   
$EndComp
NoConn ~ 6500 3800
NoConn ~ 6500 3900
NoConn ~ 6500 3400
NoConn ~ 6500 3100
NoConn ~ 6500 3000
NoConn ~ 5500 3000
NoConn ~ 5500 3100
NoConn ~ 5500 3200
NoConn ~ 5500 3300
NoConn ~ 5500 3400
NoConn ~ 5500 3500
NoConn ~ 5500 3600
NoConn ~ 5500 3700
NoConn ~ 5500 3800
NoConn ~ 5500 3900
NoConn ~ 6500 4200
$EndSCHEMATC
