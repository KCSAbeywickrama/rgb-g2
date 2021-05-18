/*
* led.c
*
* Created: 18-May-21 5:14:34 PM
*  Author: K.C.S. Abeywickrama
*/

#include <avr/io.h>
#include "led.h"

#define OCR_RED OCR2A
#define OCR_GREEN OCR0A
#define OCR_BLUE OCR0B

void _port_init(){	
	DDRD| = 1<<DDD5 | 1<<DDD6;
	DDRB| = 1<<DDB3;
}

void _pwm_init(){
	//setup Fast PWM on OC0A & OC0B (timer0)
	TCCR0A |= 1<<COM0A1 | 1<<COM0B1  | 1<<WGM01 | 1<<WGM00;
	
	//setup Fast PWM on OC2A (timer2)
	TCCR2A |= 1<<COM2A1 | 1<<WGM21 | 1<<WGM20
}

void _timer_start(){
	//start timer0 (no-prescaler)
	TCCR0B |= 1<<CS00;
	
	//start timer2 (no-prescaler)
	TCCR2B |= 1<<CS20;
}

void _timer_stop(){
	//stop timer0
	TCCR0B &= ~(1<<CS00);
	
	//stop timer2
	TCCR2B &= ~(1<<CS20);
}

void led_init(){
	_port_init();
	_pwm_init();
}

void led_on(uint8_t *rgb){
	OCR_RED=rgb[0];
	OCR_GREEN=rgb[1];
	OCR_BLUE=rgb[2];
	
	_timer_start();
}

void led_on(uint8_t red,uint8_t green,uint8_t blue){
	uint8_t rgb[3]={red,green,blue};
	led_on(rgb);
}

void led_off(){
	_timer_stop();
}
