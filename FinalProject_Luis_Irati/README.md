# TEAM MEMBERS
# HARDWARE DESCRIPTION
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
