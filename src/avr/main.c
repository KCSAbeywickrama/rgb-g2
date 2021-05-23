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
	
	DDRC |= 1<<PORTC4; //set the red led PC4 pin as a output
	DDRB |= (1<<PORTB4) | (1<<PORTB5); // set PB5 and PB4 as output pins
	DDRC &= ~(1<<PORTC5); // set PC5 as a input pin
	
	adc_init();
	
    while (1) 
    {
		PORTC |= 1<<PORTC; // high red led
		_delay_ms(2000);
		int red_read = analog_read(5); // take the ldr value for red
		PORTC &= ~(1<<PORTC4); // low red led
		
		PORTB |= 1<<PORTB4; // high green led
		_delay_ms(2000);
		int green_read = analog_read(5); // ldr value for green
		PORTB &= ~(1<<PORTB4); // low green led
		
		PORTB |= 1<<PORTB5; // blue
		_delay_ms(2000);
		int blue_read = analog_read(5); 
		PORTB &= ~(1<<PORTB5);
		
		int red_val = calib(red_read,0); // final red value
		int green_val = calib(green_read,1); // final green value
		int blue_val = calib(blue_read,2); // final blue value
		
    }
}

