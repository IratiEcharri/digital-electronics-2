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

//JOSTICK
/*Defines*/
#define Xvalue PB //arduino pin 
#define Yvalue PB //arduino pin
#define JSpushbutton PB //arduino pin

/*Variables*/
int Xposition = 0;
int Yposition = 0;
int SW = 0;


//main
//define pins as inputs
GPIO_mode_input_pullup(&DDRB, Xvalue);
GPIO_mode_input_pullup(&DDRB, Yvalue);
GPIO_mode_input_pullup(&DDRB, JSpushbutton);

//read values from pins
Xposition = GPIO_read(&DDRB, Xvalue);
Yposition = GPIO_read(&DDRB, Yvalue);
SW = GPIO_read(&DDRB, JSpushbutton);

//convert values into string
char stringX[4];
char stringY[4];

itoa(Xvalue, string, 10);
    if (Xvalue <= 255){
      lcd_gotoxy(8,1); //X goes down 1 position
      lcd_puts("      ");
      lcd_gotoxy(8,1);
      lcd_puts("Right");
    }
    elseif (Xvalue >=767){
      //X goes up 1 position
    }
    elseif (255 < Xvalue < 767){
      if( Yvalue < 255){
        //y goes left one position
      }
      elseif( Yvalue > 767){
        //y goes right one position
      }
    }

