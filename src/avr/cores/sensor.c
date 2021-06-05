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

#define LDR_PIN 5

volatile uint8_t *led_ddrs[3] = {&DDRC, &DDRB, &DDRB};
volatile uint8_t *led_ports[3] = {&PORTC, &PORTB, &PORTB};
uint8_t led_pins[3] = {PORTC4, PORTB4, PORTB5};

void sensor_init()
{	
	for (uint8_t i = 0; i < 3; i++)
		*led_ddrs[i] |= 1 << led_pins[i]; //set led_pins as output

	DDRC &= ~(1 << LDR_PIN); // set LDR_PIN as a input pin

	ADMUX |= (1 << REFS0);
	; //REFS = 1
	// REFS - Initialize ADC reference selection (Power/ Voltage for the ADC conversation)
	// REFS = 0 (00) ---> Use internal 5V (AREF off)
	// REFS = 1 (01) ---> External 5V voltage with cpasitor in AREF pin
	// REFS = 2 (10) ---> Reserved
	// REFS = 3 (11) ---> Internal 2.56V with external capasitor in AREF pin

	ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	// ADEN ---> Enable ADC
	// ADC clock frequency must be in a range of 50kHz - 200kHz
	// ADC result is more accurate in lower frequencies.
	// Eneble ADC & set divition factor to 128(111) ----> F_ADC = F_CPU/d
	// For 16MHz microchip best accurate frequency is 125kHz (when devition factor is 128 [Max])
	// For 8MHz microchip best accurate frequency is 62.5kH (When devition factor is 128) this ADC result is more accuracy than 16MHz microchip.
}

