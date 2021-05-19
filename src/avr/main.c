/*
 * avr.c
 *
 * Created: 07-May-21 5:12:49 PM
 * Author : CSA
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "cores/sensor.h"

int main(void)
{
    /* Replace with your application code */
	//pin_mode(&DDRB,PORTB0,0);
	//digital_write(&PORTB,PORTB0,1);
	//PORTB|=1<<PORTB0;
	//_delay_ms(1000);
	//digital_write(&PORTB,PORTB0,0);
	
	DDRC |= 1<<PORTC4; //set the red led PC4 pin as a output
	DDRB |= (1<<PORTB4) | (1<<PORTB5); // set PB5 and PB4 as output pins
    while (1) 
    {
		PORTC |= 1<<PORTC; // high red led
		_delay_ms(2000);
		int red_read = analog_read(); // take the ldr value for red
		PORTC &= ~(1<<PORTC4); // low red led
		
		PORTB |= 1<<PORTB4; // high green led
		_delay_ms(2000);
		int green_read = analog_read(); // ldr value for green
		PORTB &= ~(1<<PORTB4); // low green led
		
		PORTB |= 1<<PORTB5; // blue
		_delay_ms(2000);
		int blue_read = analog_read(); 
		PORTB &= ~(1<<PORTB5);
		
		red_val = calib(red_read,0); // final red value
		green_val = calib(green_read,1); // final green value
		blue_val = calib(blue_read,2); // final blue value
		
    }
}

