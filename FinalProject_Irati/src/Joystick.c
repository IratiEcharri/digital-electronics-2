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

    /* Rotary Encoder */
    #define OutputA PB2 //arduino pin of A output and CLK
    #define OutputB PB3 //arduino pin of B output and DT
    #define EncPushbutton PB5 //arduino pin of encoder's pushbutton

    /* Joystick */
    //#define VRx PC5 //arduino pin 
    //#define VRy PC4 //arduino pin
    #define JSpushbutton PB4 //arduino pin
/*************************************************************************
 * use rotary encoder to increase value of displayed characters
 * /
 


/* Defines */


/*Variables*/

/* Rotary Encoder */

    int Charactervalue = 3; //variable that will store amount of characters to display
    int Astate; //Variable to store current value of A input
    int A_last_state; //variable to store previous value of A input
    int Bstate; //variable to store current value of B input
    int Encpush; //variable to see if encoder's pushbutton has been pressed

/* Joystick */
    uint16_t value=0;
    //int Charactervalue = 3; //variable that will store amount of characters to display
    
    
    //int Xposition = 0;
    //int Yposition = 0;

    //char x=0; //X position of our letter in LCD
    //char y=0; // y position of our letter in LCD


/* **************************************************************************************************************************************/

/* Main function */

int main (void){
    lcd_init(LCD_DISP_ON);   
//charactervalue is already set

/* ******************************************************************************************************************************** */
/* Part 1: ROTARY ENCODER*/

//include gpio library from previous labs (lab2 eg)
//Set the OutputA, OutputB and EncPushbutton values as inputs
GPIO_mode_input_pullup(&DDRB, OutputA);
GPIO_mode_input_pullup(&DDRB, OutputB);
GPIO_mode_input_pullup(&DDRB, EncPushbutton);
Encpush=GPIO_read(&PINB, EncPushbutton);

A_last_state = GPIO_read(&PINB, OutputA); // read initial value of outputA

while(Encpush==1){
Astate = GPIO_read(&PINB, OutputA); //read current value of outputA
//if previous state of A different from current one pulse has occurred
    if(Astate != A_last_state){
        Bstate = GPIO_read (&PINB, OutputB);
        if(Bstate != Astate){

            if(Charactervalue<7){
                Charactervalue++;
            }
        }
        else{
            if(Charactervalue>3){
                Charactervalue--;
            }  
        }
    }
    A_last_state = Astate;


char string[2];
itoa(Charactervalue, string, 10);  // Convert decimal value to string

lcd_init(LCD_DISP_ON);// put on the LCD 
lcd_gotoxy(14, 1);
lcd_puts("x");           
lcd_gotoxy(15, 1);
lcd_puts(string);

Encpush = GPIO_read(&PINB, EncPushbutton);
}

/* ******************************************************************************************************************************* */

/*PART 2: JOYSTICK*/

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
    
    static uint8_t no_of_overflows = 0;
    //static uint8_t value = 0;
    no_of_overflows++;
        if (no_of_overflows >= 3){ // Do this every 3 x 33 ms = 100 ms
            if(value==0){
                ADMUX = ADMUX & ~ ( 1<<MUX0); // hemen iual 0 daonez 1 ea invertitzeu aurreneko aldin asike KONTUZ!!!!!!!!!!!!!!!!
                value++;
            }
            else{
                ADMUX = ADMUX | ( 1<<MUX0);
                value--;

}
            no_of_overflows = 0;
            ADCSRA = ADCSRA | (1<<ADSC); // Start ADC conversion
        }
}

ISR(ADC_vect){

uint16_t Xposition;
uint16_t Yposition;
uint16_t X;
uint16_t Y;
//int Yposition = 0;
char stringX[4];
char stringY[4];

    if(value==0){
        Xposition= ADC;
        if(Xposition<512){
            lcd_gotoxy(1,0);
            lcd_puts("Left :");
        }
        if(Xposition>512){
            lcd_gotoxy(1,0);
            lcd_puts("Right:");
        }
        X=Xposition*Charactervalue;
        itoa( X, stringX, 10);
        lcd_gotoxy(8,0);
        lcd_puts(stringX);
    }
    else{
        Yposition= ADC;
        if(Yposition<512){
            lcd_gotoxy(1,1);
            lcd_puts("Down:");
        }
        if(Yposition>512){
            lcd_gotoxy(1,1);
            lcd_puts("Up:  ");
        }
        Y=Yposition*Charactervalue;
        itoa( Y, stringY, 10);
        lcd_gotoxy(7,1);
        lcd_puts(stringY);

    }
}
//main
//define pins as inputs
//GPIO_mode_input_pullup(&DDRB, VRx);
//GPIO_mode_input_pullup(&DDRB, VRy);
//GPIO_mode_input_pullup(&DDRB, JSpushbutton);

//while(SW == 0){
    //read values from pins
    //Xposition = GPIO_read(&DDRB, VRx);
    //Yposition = GPIO_read(&DDRB, VRy);
    //SW = GPIO_read(&DDRB, JSpushbutton);


    //convert values into string

