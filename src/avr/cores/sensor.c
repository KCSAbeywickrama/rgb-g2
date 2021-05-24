/*
 * sensor.c
 *
 * Created: 19/05/2021 03:18:54
 *  Author: Lakdilu
 */ 

#include <avr/io.h>
#include "sensor.h"


void adc_init(){
	ADMUX |= (1 << REFS0); 
	// Initialize ADC reference selection (voltage for ADC) to "VCC +5V with cap"
	
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); 
	// Eneble ADC & set divition factor to 128(111) ----> F_ADC = F_CPU/d = 125000 (when F_CPU is 16M)
}
uint16_t analog_read (uint8_t _pin){
	_pin &= 0b111; // convert pin to binary
	
	ADMUX |= _pin; // Initialize pin which is going to ADC
	
	ADCSRA |= (1<<ADSC); // begin the ADC
	
	while(ADCSRA & (1<<ADSC)); // delay the function till ADC complete
	
	return (ADC); // return ADC value
}

int calib(uint8_t val, uint8_t clr){
	const float R_MAX = 400;
	const float R_MIN = 150;
	const float G_MAX = 365;
	const float G_MIN = 98;
	const float B_MAX = 517;
	const float B_MIN = 175;
	
	if (clr == 0){
		val = limit(val,R_MAX,R_MIN);
		val = (val - R_MIN)*(255/(R_MAX - R_MIN));
	}
	
	else if (clr == 1){
		val = limit(val,G_MAX,G_MIN);
		val = (val - G_MIN)*(255/(G_MAX - G_MIN));
	}
	
	else if (clr == 2){
		val = limit(val,B_MAX,B_MIN);
		val = (val - B_MIN)*(255/(B_MAX - B_MIN));
	}
	
	return val;
	
}

int limit (uint8_t _val, uint8_t _max, uint8_t _min){
	if (_val > _max)
	_val = _max;
	
	else if (_val < _min)
	_val = _min;
	
	return _val;
}
