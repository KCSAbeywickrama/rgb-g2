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


