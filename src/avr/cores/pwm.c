/*
* pwm.c
*
* Created: 15-Jun-21 6:37:17 PM
*  Author: K. C. S. Abeywickrama
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pwm.h"

#define PWM_PIN DDD5
#define PWM_DDR DDRD
#define PWM_PORT PORTD
#define PWM_OCR OCR0B

#define DEMUX_PORT PORTD
#define DEMUX_DDR DDRD

volatile uint8_t pin=0;
volatile uint8_t gbr[3]={0,0,50};

ISR(TIMER0_OVF_vect){
	
	DEMUX_PORT = (DEMUX_PORT & 0b00111111) | pin<<6 ;
	pin=(pin+1)%3;
	PWM_OCR=gbr[pin];
	
}

void pwm_init(){
	//define output pins
	PWM_DDR |= 1<< PWM_PIN;
	DEMUX_DDR |= 1<< DDD6 | 1<< DDD7;
	PWM_PORT|=1<<PWM_PIN;
}

void pwm_start(){
	//timer0 B inverting mode fast PWM | TOV on 0xff
	TCCR0A |= 1<<COM0B1 | 1<<COM0B0 | 1<< WGM01 | 1<< WGM00;
	
	//enable overflow interrupt
	TIMSK0 |= 1<<TOIE0;
	sei();
	
	//start timer2
	
	TCCR0B |= 1<<CS00; //(no prescaler)
	TCCR0B |= 1<<CS01 | 1<<CS00; //(64 prescaler)
	//TCCR0B |= 1<<CS02; //(256 prescaler)
	//TCCR0B |= 1<<CS02 | 1<<CS00; //(1024 prescaler)
}

void pwm_stop(){
	cli();
	
	TCCR0B=0;
	TIMSK0 =0;
	TCCR0A =0;
	
	PWM_PORT|=1<<PWM_PIN;
	
}

void pwm_set(uint8_t *rgb){
	gbr[0]=rgb[1];
	gbr[1]=rgb[2];
	gbr[2]=rgb[0];
}

void pwm_set_args(uint8_t red,uint8_t green,uint8_t blue){
	gbr[0]=green;
	gbr[1]=blue;
	gbr[2]=red;
}

void pwm_check(){
	uint8_t _colors[7][3]={{255,0,0},{0,255,0},{0,0,255},
	{255,255,0},{0,255,255},{255,0,255},{255,165,0}};
	
	pwm_start();
	
	for(uint8_t i=0;i<7;i++){
		pwm_set(_colors[i]);
		_delay_ms(1000);
	}
	
	pwm_stop();
}

//void check_init(){
//PWM_DDR |= 1<< PWM_PIN;
//DEMUX_DDR |= 1<< DDD4| 1<<DDD5| 1<<DDD6;
//PWM_PORT &=~(1<<PWM_PIN);
//}
//
//void check(){
//uint8_t prv_pin=(pin+2)%3;
//DEMUX_PORT &= ~(1<<led_pins[prv_pin]);
//DEMUX_PORT |= 1<<led_pins[pin];
//pin=(pin+1)%3;
//_delay_ms(1000);
//}
//
void check_tr(){
DEMUX_PORT = (DEMUX_PORT & 0b00111111) | pin<<6 ;
pin = (pin+1)%3;
_delay_ms(1000);
}
