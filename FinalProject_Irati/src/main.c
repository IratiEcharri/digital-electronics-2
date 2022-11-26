/*************************************************************************
 * use rotary encoder to increase value of displayed characters
 * /
 
/* Includes ------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions
/* Defines */
 #define OutputA  PB2 //arduino pin of A output 
 #define OutputB PB3 //arduino pin of B output
 #define EncPushbutton PB //arduino pin of encoder's pushbutton

/*Declaration of variables */
int Charactervalue = 3; //variable that will store amount of characters to display
int Astate; //Variable to store current value of A input
int A_last_state; //variable to store previous value of A input
int Bstate; //variable to store current value of B input
int Encpush=0; //variable to see if encoder's pushbutton has been pressed


int main (void){
//include gpio library from previous labs (lab2 eg)
//Set the OutputA, OutputB and EncPushbutton values as inputs
GPIO_mode_input_pullup(&DDRB, OutputA);
GPIO_mode_input_pullup(&DDRB, OutputB);
GPIO_mode_input_pullup(&DDRB, EncPushbutton);


A_last_state = GPIO_read(&DDRB, OutputA); // read initial value of outputA

while(Encpush==0){
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
        
        lcd_gotoxy(7, 0);
        lcd_puts(string);

Encpush = GPIO_read(&DDRB, EncPushbutton);
}

//charactervalue is already set
//display characters and start moving them with joystick

// Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADMUX= ADMUX | (1<<REFS0);
    // Select input channel ADC0 (voltage divider pin)
    ADMUX = ADMUX & ~ (1<<MUX3 | 1<<MUX2 | 1<<MUX1 | 1<<MUX0);
    // Enable ADC module
    ADCSRA = ADCSRA | (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA = ADCSRA | (1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA = ADCSRA | (1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0);

    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Set prescaler to 33 ms and enable overflow interrupt
    TIM1_overflow_33ms();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;

}


ISR(TIMER1_OVF_vect)
{
    // make conversion every 100ms
    //static uint8_t no_of_overflows = 0;
    //no_of_overflows++;
    //if (no_of_overflows >= 3)
    //{
        // Do this every 3 x 33 ms = 100 ms
       // no_of_overflows = 0;
    // Start ADC conversion
    ADCSRA = ADCSRA | (1<<ADSC);
    //}
}


ISR(ADC_vect){
//JOSTICK
/*Defines*/
#define VRx PB //arduino pin 
#define VRy PB //arduino pin
#define JSpushbutton PB //arduino pin

/*Variables*/
int Xposition = 0;
int Yposition = 0;
int SW = 0;


//main
//define pins as inputs
GPIO_mode_input_pullup(&DDRB, VRx);
GPIO_mode_input_pullup(&DDRB, VRy);
GPIO_mode_input_pullup(&DDRB, JSpushbutton);

while(SW == 0){
//read values from pins
Xposition = GPIO_read(&DDRB, VRx);
Yposition = GPIO_read(&DDRB, VRy);
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
}
}

