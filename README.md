# LEDcontrol

This program was created as an assignment for CSCI-SHU 350 - Embedded Computer Systems at NYU Shanghai. The program uses an STM32F746NG Discovery Board microcontroller. 

Specifications:
Program the µC board so that the LEDs LED5 through LED0 turn on or off according to the switches’ position
s. The equations describing the behavior are:

LED0 = S0.S1.S2.S3+S5.S6+/S7
LED1 = S0.S6./S7+S4./S5.S6
LED2 = S1.S2.S3.S4+/S6./S7
LED3 = S2./S4.S6+S0./S7+S4.S5
LED4 = S1.S3+S5.S6
LED5 = S0.S1

1) Create a C program to generate the described behavior processing the input each time.
2) Create a truth table.

Performance analysis:
The truth table is definitely an improvement, because the time for 1,000,000
iterations of the truth table method is 6.189 seconds, so an average of 6.189
microseconds/iteration, whereas the time for 1,000,000 iterations of the processing method is
8.375 seconds (avg. 8.375 microseconds/iteration).
The processing method hasn't been tested for variable loop time.
