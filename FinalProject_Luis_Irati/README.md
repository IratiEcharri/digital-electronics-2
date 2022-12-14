# TEAM MEMBERS
## Luis Izaguirre Imaz
- Write ISR (ADC_vect)
- Write ISR (Timer_ovf) together with Irati
- Created main schematic of application
- Edit application's video
## Irati Echarri Legarra
- Write main loop of the program
- Write ISR(Timer_ovf) together with Luis
- Created main loop's flowchart
- Created timer overflow's flowchart
# HARDWARE DESCRIPTION
## General schematic

In the schematic below are shown needed conections in order to implement an Analog joy-stick, a rotary encoder, a Digilent PmodCLP LCD module and an Arduino Uno michrocontroller:

![General Schematic](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/u_flowchart_schematics/Scheme%201.png) 

## Digilent PmodCLP LCD module connections

PmodCLP LCD module is a 16×2 character LCD module that uses a 8-bit parallel data interface. The PmodCLP utilizes a Samsung KS0066 LCD controller to display information to a Sunlike LCD panel. This is its pinout description table:

![PmodCLP LCD](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/u_flowchart_schematics/LCD.PNG)

In our case, we have interfaced our LCD in 4-bit mode. We heve used nine ports: 4 data bits (DB4, DB5, DB6, DB7), GND, VCC, RS, R/W and E

- DB4: data bit 4, connected to digital port PD4
- DB5: data bit 5, connected to digital port PD5
- DB6: data bit 6, connected to digital port PD6
- DB7: data bit 7, connected to digital port PD7
- GND: connected to ground node
- VCC: connected to VCC node
- RS: Register Select (High for Data Transfer, Low for Instruction Transfer), connected to digital port PB0
- R/W: Read/Write signal ( High or Read mode, Low for Write mode), connected to GND.
- E: Read/Write Enable (High for Read, falling edge writes data) connected to PB1

![PmodCLP LCD](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/u_flowchart_schematics/4bit%20mode.PNG)
## Joystick connections
The joystick has five ports: GND, 5V, VRx, VRy and SW
- GND is connected to ground node
- 5V is connected to Vcc node
- VRx is an analog output that gives voltage proportional to X axis, connected to analog port PC0
- VRy is an analog output that gives voltage proportional to Y axis, connected to analog port PC1
- SW is the digital output of the pushbutton, connected to digital port PB4
- ![Joystick](https://components101.com/sites/default/files/component_pin/Joystick-Module-Pinout.png)
## Rotary encoder connections
The rotary encoder has five ports: CLK, DT, SW, +, GND
- GND is connected to ground node
- + is connected to Vcc node
- CLK gives digital value of A output, connected to digital port PB2
- DT gives digital value of B output, connected to digital port PB3
- SW gives digital value of pushbutton, connected to digital port PB5
- ![Rotary encoder](https://components101.com/sites/default/files/component_pin/KY-04-Rotary-Encoder-Pinout.jpg)
# SOFTWARE DESCRIPTION
## Main program flowchart
![Main flowchart](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/u_flowchart_schematics/Main%20flowchart.png)
## Timer overflow flowchart
![Timer overflow flowchart](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/u_flowchart_schematics/Timer%20overflow%20flowchart.png)
## ADC vector flowchart
![ADC vector flowchart](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/u_flowchart_schematics/ADC%20vector%20flowchart.png)
## Project Files

The project has the following structure:

```
├── include
│   └── timer.h
├── lib
│   └── lcd
│   │   ├── lcd.c
│   │   ├── lcd.h
│   │   └── lcd_definitions.h
│   └── gpio
|       ├── gpio.c
|       └── gpio.h
└── src
    └── main.c
```


### Library files

For clarity and efficiency of the code, apart from the source file, we have used GPIO and LCD libraries, where user defined functions can be found written by other programmers. In a library we can find two parts:

- Function prototype or Function declaration (*.h file)
- Function definition (*.c file)

#### LCD library

We used LCD library for HD44780 based LCDs, developed by Peter Fleury.

The main defined funtions are:

- lcd_init(type of cursor): Initialize display and select type of cursor: in our case LCD_DISP_ON (display on, cursor off)
- lcd_gotoxy(uint8_t x, uint8_t y): Set cursor to specified position ( horizontal position (x) and vertical position (y)
- lcd_putc( char c): Display character at current cursor position. ( we haveen't use it)
- lcd_puts(	const char * s): Display string without auto linefeed.

Links to LCD library files:
- [lcd.c](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/lib/lcd/lcd.c).
- [lcd.h](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/lib/lcd/lcd.h).
- [lcd_definitions.h](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/lib/lcd/lcd_definitions.h).

#### GPIO library

The GPIO library defines the following functions:

![GPIO library](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/u_flowchart_schematics/GPIO%20library.PNG)

In our project, the following functions were used:

- GPIO_mode_input_pullup(): To set encoder's port signals as input.
- GPIO_read (): To read digital values from encoder's ports.

Links to GPIO library files:
- [gpio.c](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/lib/gpio/gpio.c).
- [gpio.h](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/lib/gpio/gpio.h).

### Source file

The main parts of our Source file are:

1. Include libraries 
2. Define variables
3. Main function: int main (void)
4. Interrupt routines: TIMER_OVF_vect and ADC_vect
   
 More descriptive texts of the source file can be found in the source code, where most of the steps are commented.
 
 Link to the source file: [src.c](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/src/main.c).
 
# VIDEO

A general explanation, the functionality and two simulations of our program are shown in the video below.
[![Watch the video](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/u_flowchart_schematics/Portada1.PNG)](https://youtu.be/h7OlzBp_UPY)




# REFERENCES
## Joystick
- [Joystick connection](https://components101.com/modules/joystick-module).
- [Example code 1](https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-joystick-with-serial-monitor-1f04f0).
- [Example code 2](https://arduinogetstarted.com/tutorials/arduino-joystick).

## Rotary encoder
- [Rotary encoder connection](https://components101.com/modules/KY-04-rotary-encoder-pinout-features-datasheet-working-application-alternative).
- [Example code 1](https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/).
- [Example code 2](https://howtomechatronics.com/tutorials/arduino/rotary-encoder-works-use-arduino/).
## LCD
- [LCD schematic](https://projects.digilentinc.com/56004/using-the-pmod-clp-with-arduino-uno-95c040).
