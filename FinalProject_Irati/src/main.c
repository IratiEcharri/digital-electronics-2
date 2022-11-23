/*************************************************************************
 * use rotary encoder to increase value of displayed characters
 * /
 
/* Includes ------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions
/* Defines */
 #define OutputA  PB2//arduino pin 
 #define OutputB PB3//arduino pin

/*Declaration of variables */
int Charactervalue = 3;
int Astate;
int A_last_state;
int Bstate;


int main (void){
//include gpio library from previous labs (lab2 eg)
//Set the OutputA and OutputB values as inputs
//this should be defined as a function of its own and called when initializing (setup function)
GPIO_mode_input_pullup(&DDRB, OutputA);
GPIO_mode_input_pullup(&DDRB, OutputB);
A_last_state = GPIO_read(&DDRB, OutputA); // read initial value of outputA

//another function to see if it is being rotated to left or right (increase/decrease)
Astate = GPIO_read(&DDRB, OutputA); //read current value of outputA
//if previous state of A different from current one pulse has occurred
if(Astate != A_last_state){
  Bstate = GPIO_read (&DDRB, OutputB);
  
  if(Bstate != Astate){
    Charactervalue ++;

  }
  else{
    Charactervalue --;
  }
}
A_last_state = Astate;
lcd_init(LCD_DISP_ON);
char string[2];
itoa(Charactervalue, string, 10);  // Convert decimal value to string
        // Display "00:00.tenths"
        
        lcd_gotoxy(7, 0);
        lcd_puts(string);
}