/*
 * sensor.c
 *
 * Created: 19/05/2021 03:18:54
 *  Author: Lakdilu
 */ 

#include <avr/io.h>
#include "sensor.h"


void sensor_init(){
	DDRC |= 1<<PORTC4; //set the red led PC4 pin as a output	DDRB |= (1<<PORTB4) | (1<<PORTB5); // set PB5 and PB4 as output pins	DDRC &= ~(1<<PORTC5); // set PC5 as a input pin

	
	ADMUX |= (1 << REFS0); 
	// Initialize ADC reference selection (voltage for ADC) to "VCC +5V with cap"
	
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); 
	// Eneble ADC & set divition factor to 128(111) ----> F_ADC = F_CPU/d = 125000 (when F_CPU is 16M)
}
uint16_t sensor_read (uint8_t _pin){
	_pin &= 0b111; // convert pin to binary
	
	ADMUX |= _pin; // Initialize pin which is going to ADC
	
	ADCSRA |= (1<<ADSC); // begin the ADC
	
	while(ADCSRA & (1<<ADSC)); // delay the function till ADC complete
	
	return (ADC); // return ADC value
}
