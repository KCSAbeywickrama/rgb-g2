/*
 * sensor.c
 *
 * Created: 19/05/2021 03:18:54
 *  Author: Lakdilu
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "sensor.h"
#include "lcd.h"

#define LDR_PIN 5

volatile uint8_t *led_ddrs[3] = {&DDRC, &DDRB, &DDRB};
volatile uint8_t *led_ports[3] = {&PORTC, &PORTB, &PORTB};
uint8_t led_pins[3] = {PORTC4, PORTB4, PORTB5};

void sensor_init()
{	
	for (uint8_t i = 0; i < 3; i++)
		*led_ddrs[i] |= 1 << led_pins[i]; //set led_pins as output

	DDRC &= ~(1 << LDR_PIN); // set LDR_PIN as a input pin

	ADMUX |= (1 << REFS0); //REFS = 1 : External 5V voltage with cpasitor in AREF pin
	
	ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // Enable ADC,	Frequency is 125kHz	
		
	DIDR0 = (1 << LDR_PIN); // Digital input buffer is disabled
}
uint16_t _adc_read(uint8_t pin)
{
	pin &= 0b111; // convert pin value to binary

	ADMUX |= pin; // Initialize pin which is going to ADC (active the pin which we are going top get analog reading)

	ADCSRA |= (1 << ADSC); // begin the ADC

	// delay the function till ADC complete (ADSC = 1 until ADC circule complete)
	while (ADCSRA & (1 << ADSC));	

	return (ADC); // return ADC value
}

void sensor_read(uint16_t *reading)
{
	lcd_clear();
	lcd_set_cursor(0,0);
	lcd_string("Reading");
	for (int i = 0; i < 3; i++)
	{
		*led_ports[i] |= 1 << led_pins[i];	  // Turn on LED
		lcd_char('.');
		_delay_ms(2000);					  // Wait until LDR reading is stable
		reading[i] = _adc_read(LDR_PIN);	  // Get LDR reading (corresponding function in sensor.c)
		*led_ports[i] &= ~(1 << led_pins[i]); // Turn off LED
	}										  // LED pins ---> RED = C4 / GREEN = B4 / BLUE = B2
	
}
