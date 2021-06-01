/*
 * sensor.c
 *
 * Created: 19/05/2021 03:18:54
 *  Author: Lakdilu
 */ 

#include <avr/io.h>
#include "sensor.h"


void sensor_init(){
	DDRC |= 1<<PORTC4; 					//set the red led PC4 pin as a output
	DDRB |= (1<<PORTB4) | (1<<PORTB5); 	// set PB5 and PB4 as output pins
	DDRC &= ~(1<<PORTC5); 				// set PC5 as a input pin

	
	ADMUX |= ~((1 << REFS0) | (1 << REFS1)) ; //REFS = 0
	// REFS - Initialize ADC reference selection (Power/ Voltage for the ADC conversation)
	// REFS = 0 (00) ---> Use internal 5V (AREF off)
	// REFS = 1 (01) ---> External 5V voltage with cpasitor in AREF pin
	// REFS = 2 (10) ---> Reserved
	// REFS = 3 (11) ---> Internal 2.56V with external capasitor in AREF pin

	
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); 
	// ADEN ---> Enable ADC
	// ADC clock frequency must be in a range of 50kHz - 200kHz
	// ADC result is more accurate in lower frequencies.
	// Eneble ADC & set divition factor to 128(111) ----> F_ADC = F_CPU/d 
	// For 16MHz microchip best accurate frequency is 125kHz (when devition factor is 128 [Max])
	// For 8MHz microchip best accurate frequency is 62.5kH (When devition factor is 128) this ADC result accuracy is more than 16MHz microchip.
	
	
}
uint16_t sensor_read (uint8_t _pin){
	_pin &= 0b111; 				// convert pin value to binary
	
	ADMUX |= _pin; 				// Initialize pin which is going to ADC (active the pin which we are going top get analog reading)
	
	ADCSRA |= (1<<ADSC); 		// begin the ADC
	
	while(ADCSRA & (1<<ADSC)); // delay the function till ADC complete (ADSC = 1 until ADC circule complete)
	
	return (ADC); 				// return ADC value
}
