/*************************************************************************
 * use rotary encoder to increase value of displayed characters
 * display direction to wich joystick is being pushed 
 * display analog value of joisticks direction multiplied by number of 
 * characters selected with rotary encoder
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



/*************************************************************************
  * use rotary encoder to increase value of displayed characters
*/

/*Variables*/

/* Rotary Encoder */

    int Charactervalue = 3; //variable that will store multiplication value
    int Astate; //Variable to store current value of A input
    int A_last_state; //variable to store previous value of A input
    int Bstate; //variable to store current value of B input
    int Encpush; //variable to see if encoder's pushbutton has been pressed

/* Joystick */
    uint16_t value=0; //value to switch ADC channel
      

/* ****************************************************************************/

/* Main function */

int main (void){
    lcd_init(LCD_DISP_ON); //turn on LCD  

/* Part 1: ROTARY ENCODER*/

//Set the OutputA, OutputB and EncPushbutton values as inputs
GPIO_mode_input_pullup(&DDRB, OutputA);
GPIO_mode_input_pullup(&DDRB, OutputB);
GPIO_mode_input_pullup(&DDRB, EncPushbutton);

Encpush=GPIO_read(&PINB, EncPushbutton); //read current value of encoder's pushbutton

A_last_state = GPIO_read(&PINB, OutputA); // read initial value of outputA

while(Encpush==1){
  
  // loop that will keep going while encoder's pushbutton is not pressed
  
  Astate = GPIO_read(&PINB, OutputA); //read current value of outputA
  
  //if previous state of A different from current one pulse has occurred (encoder is rotating)
    
    if(Astate != A_last_state){
        Bstate = GPIO_read (&PINB, OutputB); //read value of outputB
        if(Bstate != Astate){

            if(Charactervalue<7){ //increase value to max amount of 7
                Charactervalue++;
            }
        }
        else{
            if(Charactervalue>3){ //decrease value to min amount of 3
                Charactervalue--;
            }  
        }
    }
    
    //Define current state of A as last to read state again and compare
    A_last_state = Astate;


  char string[2];
  itoa(Charactervalue, string, 10);  // Convert decimal value to string

  lcd_init(LCD_DISP_ON);// put on the LCD 
  
  //display value of multiplication (charactervalue)
  lcd_gotoxy(14, 1);
  lcd_puts("x");           
  lcd_gotoxy(15, 1);
  lcd_puts(string);

  
  Encpush = GPIO_read(&PINB, EncPushbutton);//read value of encoders pushbutton again
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
    
    no_of_overflows++;
        if (no_of_overflows >= 3){ // Do this every 3 x 33 ms = 100 ms
            if(value==0){
                ADMUX = ADMUX & ~ ( 1<<MUX0); //set first channel
                value++; //increase value to switch conversion channel
            }
            else{
                ADMUX = ADMUX | ( 1<<MUX0); //set second conversion channel
                value--; //decrease value to switch conversion channel

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

char stringX[4];
char stringY[4];

    if(value==0){ //conversion in firs channel (X variable)
        //display X direction of joystick
        Xposition= ADC;
        if(Xposition<512){
            lcd_gotoxy(1,0);
            lcd_puts("Left :");
        }
        if(Xposition>512){
            lcd_gotoxy(1,0);
            lcd_puts("Right:");
        }
        //display multiplied value of analog signal X
        X=Xposition*Charactervalue;
        itoa( X, stringX, 10);
        lcd_gotoxy(8,0);
        lcd_puts(stringX);
    }
    else{ //conversion of second channel (Y variable)
        //display Y direction of Joystick
        Yposition= ADC;
        if(Yposition<512){
            lcd_gotoxy(1,1);
            lcd_puts("Down:");
        }
        if(Yposition>512){
            lcd_gotoxy(1,1);
            lcd_puts("Up:  ");
        }
        //display multiplied value of analog signal Y
        Y=Yposition*Charactervalue;
        itoa( Y, stringY, 10);
        lcd_gotoxy(7,1);
        lcd_puts(stringY);

    }
}


