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

#define PWM_PIN DDB3
#define PWM_DDR DDRB
#define PWM_PORT PORTB
#define PWM_OCR OCR2A

#define DEMUX_PORT PORTD
#define DEMUX_DDR DDRD


volatile uint16_t led_pins[3]={PORTD4,PORTD5,PORTD6};
//volatile uint8_t *led_ports[3]={&PORTB,&PORTB,&PORTB};
volatile uint8_t pin=0;
volatile uint8_t gbr[3]={255,0,255};

ISR(TIMER2_OVF_vect){
	
	DEMUX_PORT = (DEMUX_PORT & 0b10011111) | pin<<5 ;
	pin=(pin+1)%3;
	PWM_OCR=gbr[pin];
	
}

void pwm_init(){
	PWM_DDR |= 1<< PWM_PIN;
	DEMUX_DDR |= 1<< DDD4| 1<<DDD5| 1<<DDD6;
	
	//timer2 A inverting mode fast PWM | TOV on 0xff
	TCCR2A |= 1<<COM2A1 | 1<<COM2A0 | 1<< WGM21 | 1<< WGM20;
	
	//setup Fast PWM on OC2A (timer2)
	//TCCR2A |= 1<<COM2A1 | 1<<WGM21 | 1<<WGM20;
	
	PWM_OCR=100;
	
	//enable overflow interrupt
	TIMSK2 |= 1<<TOIE2;
	
	//start timer0 (no-prescaler)
	//TCCR0B |= 1<<CS00;
	
	//start timer2 (64 prescaler)
	//TCCR2B |= 1<<CS22;
	
	//start timer2 (1024 prescaler)
	//TCCR0B |= 1<<CS22 | 1<<CS21 | 1<<CS20;
	
	sei();
	
	
	//start timer2 (128 prescaler)
	TCCR2B |= 1<<CS22 | 1<<CS20;
	//DEMUX_PORT|=1<<PORTD4;
	
}

void check_init(){
	PWM_DDR |= 1<< PWM_PIN;
	DEMUX_DDR |= 1<< DDD4| 1<<DDD5| 1<<DDD6;
	PWM_PORT &=~(1<<PWM_PIN);
}

void check(){
	uint8_t prv_pin=(pin+2)%3;
	DEMUX_PORT &= ~(1<<led_pins[prv_pin]);
	DEMUX_PORT |= 1<<led_pins[pin];
	pin=(pin+1)%3;
	_delay_ms(1000);
}

void check_tr(){	
	DEMUX_PORT = (DEMUX_PORT & 0b10011111) | pin<<5 ;
	pin = (pin+1)%3;
	_delay_ms(1000);
}
