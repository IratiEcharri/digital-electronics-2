# TEAM MEMBERS
# HARDWARE DESCRIPTION
## Digilent PmodCLP LCD module connections

PmodCLP LCD module a 16×2 character LCD module that uses a 8-bit parallel data interface. The PmodCLP utilizes a Samsung KS0066 LCD controller to display information to a Sunlike LCD panel. This is its pinout description table:

![PmodCLP LCD](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/LCD.PNG)

In our case, we have interfaced our LCD in 4-bit mode. We heve used nine pins: 4 data bits (DB4, DB5, DB6, DB7), GND, VCC, RS, R/W, E

![PmodCLP LCD](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/4bit%20mode.PNG)
## Joystick connections
The joystick has five ports: GND, 5V, VRx, VRy and SW
- GND is connected to ground node
- 5V is connected to Vcc node
- VRx is an analog output that gives voltage proportional to X axis
- VRy is an analog output that gives voltage proportional to Y axis
- SW is the digital output of the pushbutton
- ![Joystick](https://components101.com/sites/default/files/component_pin/Joystick-Module-Pinout.png)
## Rotary encoder connections
The rotary encoder has five ports: CLK, DT, SW, +, GND
- GND is connected to ground node
- + is connected to Vcc node
- CLK gives digital value of A output
- DT gives digital value of B output
- SW gives digital value of pushbutton
- ![Rotary encoder](https://components101.com/sites/default/files/component_pin/KY-04-Rotary-Encoder-Pinout.jpg)
# SOFTWARE DESCRIPTION
## Main program flowchart
![Main flowchart](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/Main%20flowchart.png)
## Timer overflow flowchart
![Timer overflow flowchart](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/Timer%20overflow%20flowchart.png)
## ADC vector flowchart
![ADC vector flowchart](https://github.com/IratiEcharri/digital-electronics-2/blob/main/FinalProject_Luis_Irati/ADC%20vector%20flowchart.png)
# VIDEO
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
