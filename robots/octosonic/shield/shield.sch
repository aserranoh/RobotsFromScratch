EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:rfs
LIBS:arduino
LIBS:shield-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Octosonic shield"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Conn_01x04 HC-SR04_1
U 1 1 5BB4D1AC
P 9350 4250
F 0 "HC-SR04_1" H 9350 4450 50  0000 C CNN
F 1 "*" H 9350 3950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x04_Pitch2.54mm" H 9350 4250 50  0001 C CNN
F 3 "" H 9350 4250 50  0001 C CNN
	1    9350 4250
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 HC-SR04_8
U 1 1 5BB4D1DD
P 9350 4900
F 0 "HC-SR04_8" H 9350 5100 50  0000 C CNN
F 1 "*" H 9350 4600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 9350 4900 50  0001 C CNN
F 3 "" H 9350 4900 50  0001 C CNN
	1    9350 4900
	1    0    0    -1  
$EndComp
$Comp
L D D6
U 1 1 5BB4DC52
P 8300 4350
F 0 "D6" H 8300 4450 50  0000 C CNN
F 1 "1N4148" H 8300 4250 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P2.54mm_Vertical_AnodeUp" H 8300 4350 50  0001 C CNN
F 3 "" H 8300 4350 50  0001 C CNN
	1    8300 4350
	1    0    0    -1  
$EndComp
$Comp
L D D7
U 1 1 5BB4DC93
P 8300 5000
F 0 "D7" H 8300 5100 50  0000 C CNN
F 1 "1N4148" H 8300 4900 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P2.54mm_Vertical_AnodeUp" H 8300 5000 50  0001 C CNN
F 3 "" H 8300 5000 50  0001 C CNN
	1    8300 5000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5BB4FD49
P 8700 5300
F 0 "#PWR01" H 8700 5050 50  0001 C CNN
F 1 "GND" H 8700 5150 50  0000 C CNN
F 2 "" H 8700 5300 50  0001 C CNN
F 3 "" H 8700 5300 50  0001 C CNN
	1    8700 5300
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 5BB6E55F
P 9350 1300
F 0 "#FLG02" H 9350 1375 50  0001 C CNN
F 1 "PWR_FLAG" H 9350 1450 50  0000 C CNN
F 2 "" H 9350 1300 50  0001 C CNN
F 3 "" H 9350 1300 50  0001 C CNN
	1    9350 1300
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG03
U 1 1 5BB6E5AD
P 9900 1300
F 0 "#FLG03" H 9900 1375 50  0001 C CNN
F 1 "PWR_FLAG" H 9900 1450 50  0000 C CNN
F 2 "" H 9900 1300 50  0001 C CNN
F 3 "" H 9900 1300 50  0001 C CNN
	1    9900 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5BB6E5FB
P 9350 1700
F 0 "#PWR04" H 9350 1450 50  0001 C CNN
F 1 "GND" H 9350 1550 50  0000 C CNN
F 2 "" H 9350 1700 50  0001 C CNN
F 3 "" H 9350 1700 50  0001 C CNN
	1    9350 1700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 5BB6E649
P 9900 1700
F 0 "#PWR05" H 9900 1550 50  0001 C CNN
F 1 "+5V" H 9900 1840 50  0000 C CNN
F 2 "" H 9900 1700 50  0001 C CNN
F 3 "" H 9900 1700 50  0001 C CNN
	1    9900 1700
	1    0    0    -1  
$EndComp
$Comp
L Arduino_Uno_Shield XA1
U 1 1 5BBCC55F
P 5700 4600
F 0 "XA1" V 5800 4600 60  0000 C CNN
F 1 "Arduino_Uno_Shield" V 5600 4600 60  0000 C CNN
F 2 "Arduino:Arduino_Uno_Shield" H 7500 8350 60  0001 C CNN
F 3 "" H 7500 8350 60  0001 C CNN
	1    5700 4600
	1    0    0    -1  
$EndComp
NoConn ~ 4400 5450
NoConn ~ 4400 3850
NoConn ~ 4400 3950
NoConn ~ 7000 5550
NoConn ~ 7000 5650
NoConn ~ 7000 4850
NoConn ~ 7000 4950
NoConn ~ 7000 5050
NoConn ~ 7000 5150
NoConn ~ 7000 5250
NoConn ~ 7000 5350
NoConn ~ 7000 4450
NoConn ~ 7000 4550
NoConn ~ 7000 4650
NoConn ~ 4400 4850
$Comp
L +5V #PWR06
U 1 1 5BBF7188
P 8950 3900
F 0 "#PWR06" H 8950 3750 50  0001 C CNN
F 1 "+5V" H 8950 4040 50  0000 C CNN
F 2 "" H 8950 3900 50  0001 C CNN
F 3 "" H 8950 3900 50  0001 C CNN
	1    8950 3900
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 HC-SR04_6
U 1 1 5BBF7475
P 2300 2900
F 0 "HC-SR04_6" H 2300 3100 50  0000 C CNN
F 1 "*" H 2300 2600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x04_Pitch2.54mm" H 2300 2900 50  0001 C CNN
F 3 "" H 2300 2900 50  0001 C CNN
	1    2300 2900
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x04 HC-SR04_7
U 1 1 5BBF7557
P 2300 3650
F 0 "HC-SR04_7" H 2300 3850 50  0000 C CNN
F 1 "*" H 2300 3350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2300 3650 50  0001 C CNN
F 3 "" H 2300 3650 50  0001 C CNN
	1    2300 3650
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x04 HC-SR04_5
U 1 1 5BBF76AF
P 2300 4400
F 0 "HC-SR04_5" H 2300 4600 50  0000 C CNN
F 1 "*" H 2300 4100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x04_Pitch2.54mm" H 2300 4400 50  0001 C CNN
F 3 "" H 2300 4400 50  0001 C CNN
	1    2300 4400
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x04 HC-SR04_4
U 1 1 5BBF76F7
P 2300 5100
F 0 "HC-SR04_4" H 2300 5300 50  0000 C CNN
F 1 "*" H 2300 4800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2300 5100 50  0001 C CNN
F 3 "" H 2300 5100 50  0001 C CNN
	1    2300 5100
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x04 HC-SR04_2
U 1 1 5BBF7753
P 2300 5800
F 0 "HC-SR04_2" H 2300 6000 50  0000 C CNN
F 1 "*" H 2300 5500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x04_Pitch2.54mm" H 2300 5800 50  0001 C CNN
F 3 "" H 2300 5800 50  0001 C CNN
	1    2300 5800
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x04 HC-SR04_3
U 1 1 5BBF779D
P 2300 6500
F 0 "HC-SR04_3" H 2300 6700 50  0000 C CNN
F 1 "*" H 2300 6200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2300 6500 50  0001 C CNN
F 3 "" H 2300 6500 50  0001 C CNN
	1    2300 6500
	-1   0    0    -1  
$EndComp
$Comp
L D D2
U 1 1 5BBF7F79
P 2850 3750
F 0 "D2" H 2850 3850 50  0000 C CNN
F 1 "1N4148" H 2850 3650 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P2.54mm_Vertical_AnodeUp" H 2850 3750 50  0001 C CNN
F 3 "" H 2850 3750 50  0001 C CNN
	1    2850 3750
	-1   0    0    1   
$EndComp
$Comp
L D D1
U 1 1 5BBF7FE9
P 2850 3000
F 0 "D1" H 2850 3100 50  0000 C CNN
F 1 "1N4148" H 2850 2900 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P2.54mm_Vertical_AnodeUp" H 2850 3000 50  0001 C CNN
F 3 "" H 2850 3000 50  0001 C CNN
	1    2850 3000
	-1   0    0    1   
$EndComp
$Comp
L D D5
U 1 1 5BBF804B
P 2850 5900
F 0 "D5" H 2850 6000 50  0000 C CNN
F 1 "1N4148" H 2850 5800 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P2.54mm_Vertical_AnodeUp" H 2850 5900 50  0001 C CNN
F 3 "" H 2850 5900 50  0001 C CNN
	1    2850 5900
	-1   0    0    1   
$EndComp
$Comp
L D D3
U 1 1 5BBF80B5
P 2850 4500
F 0 "D3" H 2850 4600 50  0000 C CNN
F 1 "1N4148" H 2850 4400 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P2.54mm_Vertical_AnodeUp" H 2850 4500 50  0001 C CNN
F 3 "" H 2850 4500 50  0001 C CNN
	1    2850 4500
	-1   0    0    1   
$EndComp
$Comp
L D D8
U 1 1 5BBF8113
P 2850 6600
F 0 "D8" H 2850 6700 50  0000 C CNN
F 1 "1N4148" H 2850 6500 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P2.54mm_Vertical_AnodeUp" H 2850 6600 50  0001 C CNN
F 3 "" H 2850 6600 50  0001 C CNN
	1    2850 6600
	-1   0    0    1   
$EndComp
$Comp
L D D4
U 1 1 5BBF8181
P 2850 5200
F 0 "D4" H 2850 5300 50  0000 C CNN
F 1 "1N4148" H 2850 5100 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P2.54mm_Vertical_AnodeUp" H 2850 5200 50  0001 C CNN
F 3 "" H 2850 5200 50  0001 C CNN
	1    2850 5200
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR07
U 1 1 5BBF914C
P 2600 6800
F 0 "#PWR07" H 2600 6550 50  0001 C CNN
F 1 "GND" H 2600 6650 50  0000 C CNN
F 2 "" H 2600 6800 50  0001 C CNN
F 3 "" H 2600 6800 50  0001 C CNN
	1    2600 6800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR08
U 1 1 5BBF941D
P 2700 2550
F 0 "#PWR08" H 2700 2400 50  0001 C CNN
F 1 "+5V" H 2700 2690 50  0000 C CNN
F 2 "" H 2700 2550 50  0001 C CNN
F 3 "" H 2700 2550 50  0001 C CNN
	1    2700 2550
	1    0    0    -1  
$EndComp
$Comp
L TB6612FNG U1
U 1 1 5BBFA41C
P 5050 850
F 0 "U1" H 5700 -450 60  0000 C CNN
F 1 "TB6612FNG" H 5700 650 60  0000 C CNN
F 2 "rfs:TB6612FNG" H 5050 850 60  0001 C CNN
F 3 "" H 5050 850 60  0001 C CNN
	1    5050 850 
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 MOTOR1
U 1 1 5BBFB175
P 4250 1450
F 0 "MOTOR1" H 4250 1550 50  0000 C CNN
F 1 "Conn_01x02" H 4250 1250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 4250 1450 50  0001 C CNN
F 3 "" H 4250 1450 50  0001 C CNN
	1    4250 1450
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x02 MOTOR2
U 1 1 5BBFB263
P 4250 2050
F 0 "MOTOR2" H 4250 2150 50  0000 C CNN
F 1 "Conn_01x02" H 4250 1850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 4250 2050 50  0001 C CNN
F 3 "" H 4250 2050 50  0001 C CNN
	1    4250 2050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR09
U 1 1 5BBFB85B
P 4250 5150
F 0 "#PWR09" H 4250 4900 50  0001 C CNN
F 1 "GND" H 4250 5000 50  0000 C CNN
F 2 "" H 4250 5150 50  0001 C CNN
F 3 "" H 4250 5150 50  0001 C CNN
	1    4250 5150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR010
U 1 1 5BBFBA95
P 4250 5550
F 0 "#PWR010" H 4250 5400 50  0001 C CNN
F 1 "+5V" H 4250 5690 50  0000 C CNN
F 2 "" H 4250 5550 50  0001 C CNN
F 3 "" H 4250 5550 50  0001 C CNN
	1    4250 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 5BBFBFDF
P 5000 1150
F 0 "#PWR011" H 5000 900 50  0001 C CNN
F 1 "GND" H 5000 1000 50  0000 C CNN
F 2 "" H 5000 1150 50  0001 C CNN
F 3 "" H 5000 1150 50  0001 C CNN
	1    5000 1150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR012
U 1 1 5BBFC175
P 4800 1300
F 0 "#PWR012" H 4800 1150 50  0001 C CNN
F 1 "+5V" H 4800 1440 50  0000 C CNN
F 2 "" H 4800 1300 50  0001 C CNN
F 3 "" H 4800 1300 50  0001 C CNN
	1    4800 1300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR013
U 1 1 5BBFC99F
P 6550 2100
F 0 "#PWR013" H 6550 1950 50  0001 C CNN
F 1 "+5V" H 6550 2240 50  0000 C CNN
F 2 "" H 6550 2100 50  0001 C CNN
F 3 "" H 6550 2100 50  0001 C CNN
	1    6550 2100
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5BBFD075
P 5000 6250
F 0 "R1" V 5080 6250 50  0000 C CNN
F 1 "5K" V 5000 6250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 4930 6250 50  0001 C CNN
F 3 "" H 5000 6250 50  0001 C CNN
	1    5000 6250
	0    1    1    0   
$EndComp
$Comp
L GND #PWR014
U 1 1 5BBFD2B9
P 5350 6250
F 0 "#PWR014" H 5350 6000 50  0001 C CNN
F 1 "GND" H 5350 6100 50  0000 C CNN
F 2 "" H 5350 6250 50  0001 C CNN
F 3 "" H 5350 6250 50  0001 C CNN
	1    5350 6250
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 BATTERY1
U 1 1 5BC068F2
P 2150 1250
F 0 "BATTERY1" H 2150 1350 50  0000 C CNN
F 1 "Conn_01x02" H 2150 1050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2150 1250 50  0001 C CNN
F 3 "" H 2150 1250 50  0001 C CNN
	1    2150 1250
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 5BC06A0D
P 2500 1550
F 0 "#PWR015" H 2500 1300 50  0001 C CNN
F 1 "GND" H 2500 1400 50  0000 C CNN
F 2 "" H 2500 1550 50  0001 C CNN
F 3 "" H 2500 1550 50  0001 C CNN
	1    2500 1550
	1    0    0    -1  
$EndComp
$Comp
L SW_DPST_x2 SW1
U 1 1 5BC06B0A
P 2850 1250
F 0 "SW1" H 2850 1375 50  0000 C CNN
F 1 "SW_DPST_x2" H 2850 1150 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_CuK_JS202011CQN_DPDT_Straight" H 2850 1250 50  0001 C CNN
F 3 "" H 2850 1250 50  0001 C CNN
	1    2850 1250
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5BC07331
P 4000 2750
F 0 "R2" V 4080 2750 50  0000 C CNN
F 1 "10M" V 4000 2750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3930 2750 50  0001 C CNN
F 3 "" H 4000 2750 50  0001 C CNN
	1    4000 2750
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 5BC07521
P 4500 2750
F 0 "R3" V 4580 2750 50  0000 C CNN
F 1 "10M" V 4500 2750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 4430 2750 50  0001 C CNN
F 3 "" H 4500 2750 50  0001 C CNN
	1    4500 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	8950 4800 9150 4800
Connection ~ 8950 4800
Wire Wire Line
	8950 4150 9150 4150
Connection ~ 8950 4150
Wire Wire Line
	8700 4450 9150 4450
Connection ~ 8700 4450
Wire Wire Line
	8700 5100 9150 5100
Connection ~ 8700 5100
Wire Wire Line
	8450 4350 9150 4350
Wire Wire Line
	8450 5000 9150 5000
Wire Wire Line
	9350 1300 9350 1700
Wire Wire Line
	9900 1300 10100 1300
Wire Wire Line
	10100 1300 10100 1700
Wire Wire Line
	10100 1700 9900 1700
Wire Wire Line
	8000 5000 8150 5000
Wire Wire Line
	8150 4350 8000 4350
Connection ~ 8000 4350
Wire Wire Line
	7000 4250 9150 4250
Wire Wire Line
	7000 4350 7650 4350
Wire Wire Line
	7650 4350 7650 4900
Wire Wire Line
	7650 4900 9150 4900
Wire Wire Line
	8700 5300 8700 4450
Wire Wire Line
	8000 4150 8000 5950
Wire Wire Line
	8000 4150 7000 4150
Wire Wire Line
	8950 3900 8950 4800
Wire Wire Line
	2500 2900 3200 2900
Wire Wire Line
	3200 2900 3200 3550
Wire Wire Line
	3200 3550 4400 3550
Wire Wire Line
	2500 3650 4400 3650
Wire Wire Line
	2500 4400 3200 4400
Wire Wire Line
	3200 4400 3200 4250
Wire Wire Line
	3200 4250 4400 4250
Wire Wire Line
	2500 5100 3300 5100
Wire Wire Line
	3300 5100 3300 4350
Wire Wire Line
	3300 4350 4400 4350
Wire Wire Line
	2500 5800 3400 5800
Wire Wire Line
	3400 5800 3400 4650
Wire Wire Line
	3400 4650 4400 4650
Wire Wire Line
	2500 6500 3500 6500
Wire Wire Line
	3500 6500 3500 4750
Wire Wire Line
	3500 4750 4400 4750
Wire Wire Line
	3000 3000 3000 6600
Connection ~ 3000 3750
Connection ~ 3000 4500
Connection ~ 3000 5200
Connection ~ 3000 5900
Wire Wire Line
	3000 6600 6700 6600
Wire Wire Line
	6700 6600 6700 5950
Wire Wire Line
	6700 5950 8000 5950
Connection ~ 8000 5000
Wire Wire Line
	2500 3000 2700 3000
Wire Wire Line
	2500 3750 2700 3750
Wire Wire Line
	2500 4500 2700 4500
Wire Wire Line
	2500 5200 2700 5200
Wire Wire Line
	2500 5900 2700 5900
Wire Wire Line
	2500 6600 2700 6600
Wire Wire Line
	2500 2800 2700 2800
Wire Wire Line
	2500 3100 2600 3100
Connection ~ 2600 3100
Wire Wire Line
	2500 3850 2600 3850
Connection ~ 2600 3850
Wire Wire Line
	2500 4600 2600 4600
Connection ~ 2600 4600
Wire Wire Line
	2500 5300 2600 5300
Connection ~ 2600 5300
Wire Wire Line
	2500 6000 2600 6000
Connection ~ 2600 6000
Wire Wire Line
	2500 6700 2600 6700
Connection ~ 2600 6700
Wire Wire Line
	2700 2550 2700 6400
Wire Wire Line
	2700 6400 2500 6400
Connection ~ 2700 2800
Wire Wire Line
	2600 3100 2600 6800
Wire Wire Line
	2500 3550 2700 3550
Connection ~ 2700 3550
Wire Wire Line
	2500 4300 2700 4300
Connection ~ 2700 4300
Wire Wire Line
	2500 5000 2700 5000
Connection ~ 2700 5000
Wire Wire Line
	2500 5700 2700 5700
Connection ~ 2700 5700
Wire Wire Line
	4450 1950 5150 1950
Wire Wire Line
	4450 2050 5150 2050
Wire Wire Line
	4450 1550 4450 1850
Wire Wire Line
	4450 1850 5150 1850
Wire Wire Line
	4450 1450 4550 1450
Wire Wire Line
	4550 1450 4550 1750
Wire Wire Line
	4550 1750 5150 1750
Wire Wire Line
	4250 5150 4400 5150
Wire Wire Line
	4400 5150 4400 5350
Connection ~ 4400 5250
Wire Wire Line
	4250 5550 4400 5550
Wire Wire Line
	5000 1150 5150 1150
Wire Wire Line
	5150 1150 5150 1350
Connection ~ 5150 1250
Wire Wire Line
	4800 1300 4800 1450
Wire Wire Line
	4800 1450 5150 1450
Wire Wire Line
	7000 4050 8450 4050
Wire Wire Line
	7000 3750 8150 3750
Wire Wire Line
	8150 3750 8150 1500
Wire Wire Line
	8150 1500 6250 1500
Wire Wire Line
	7000 3650 8050 3650
Wire Wire Line
	8050 3650 8050 1700
Wire Wire Line
	8050 1700 6250 1700
Wire Wire Line
	7000 3550 7950 3550
Wire Wire Line
	7950 3550 7950 1800
Wire Wire Line
	7950 1800 6250 1800
Wire Wire Line
	6250 1900 6250 2100
Wire Wire Line
	6250 2100 6550 2100
Wire Wire Line
	7000 3850 8250 3850
Wire Wire Line
	8250 3850 8250 1400
Wire Wire Line
	8250 1400 6250 1400
Wire Wire Line
	7000 3950 8350 3950
Wire Wire Line
	8350 3950 8350 1300
Wire Wire Line
	8350 1300 6250 1300
Wire Wire Line
	8450 4050 8450 1600
Wire Wire Line
	8450 1600 6250 1600
Wire Wire Line
	4850 6250 4600 6250
Wire Wire Line
	4600 6250 4600 6600
Connection ~ 4600 6600
Wire Wire Line
	5150 6250 5350 6250
Wire Wire Line
	2350 1350 2500 1350
Wire Wire Line
	2500 1350 2500 1550
Wire Wire Line
	2350 1250 2650 1250
Wire Wire Line
	3050 1250 3700 1250
Wire Wire Line
	3700 1250 3700 5650
Wire Wire Line
	3700 5650 4400 5650
Wire Wire Line
	3700 2450 4800 2450
Wire Wire Line
	4800 2450 4800 1550
Wire Wire Line
	4800 1550 5150 1550
Connection ~ 3700 2450
Wire Wire Line
	3700 2750 3850 2750
Connection ~ 3700 2750
Wire Wire Line
	4150 2750 4350 2750
Wire Wire Line
	4400 4550 3950 4550
Wire Wire Line
	3950 4550 3950 3000
Wire Wire Line
	3950 3000 4350 3000
Wire Wire Line
	4250 3000 4250 2750
Connection ~ 4250 2750
$Comp
L GND #PWR016
U 1 1 5BC078AA
P 4800 3000
F 0 "#PWR016" H 4800 2750 50  0001 C CNN
F 1 "GND" H 4800 2850 50  0000 C CNN
F 2 "" H 4800 3000 50  0001 C CNN
F 3 "" H 4800 3000 50  0001 C CNN
	1    4800 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2750 4800 2750
Wire Wire Line
	4800 2750 4800 3000
$Comp
L LED_ALT D9
U 1 1 5BC07CCF
P 5650 3050
F 0 "D9" H 5650 3150 50  0000 C CNN
F 1 "LED_ALT" H 5650 2950 50  0000 C CNN
F 2 "LEDs:LED_D3.0mm" H 5650 3050 50  0001 C CNN
F 3 "" H 5650 3050 50  0001 C CNN
	1    5650 3050
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 5BC07FCC
P 6150 3050
F 0 "R4" V 6230 3050 50  0000 C CNN
F 1 "220" V 6150 3050 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6080 3050 50  0001 C CNN
F 3 "" H 6150 3050 50  0001 C CNN
	1    6150 3050
	0    1    1    0   
$EndComp
$Comp
L C C1
U 1 1 5BC08104
P 4500 3000
F 0 "C1" H 4525 3100 50  0000 L CNN
F 1 "0.1uF" H 4525 2900 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 4538 2850 50  0001 C CNN
F 3 "" H 4500 3000 50  0001 C CNN
	1    4500 3000
	0    1    1    0   
$EndComp
Connection ~ 4250 3000
Wire Wire Line
	4800 3000 4650 3000
$Comp
L GND #PWR017
U 1 1 5BC0846A
P 6450 3050
F 0 "#PWR017" H 6450 2800 50  0001 C CNN
F 1 "GND" H 6450 2900 50  0000 C CNN
F 2 "" H 6450 3050 50  0001 C CNN
F 3 "" H 6450 3050 50  0001 C CNN
	1    6450 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 3050 6300 3050
Wire Wire Line
	6000 3050 5800 3050
Wire Wire Line
	5500 3050 5500 3300
Wire Wire Line
	5500 3300 4200 3300
Wire Wire Line
	4200 3300 4200 4450
Wire Wire Line
	4200 4450 4400 4450
$EndSCHEMATC