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

#define PWM_PIN DDD6
#define PWM_OCR OCR0A
#define DEMUX_PORT PORTB


volatile uint16_t led_pins[3]={PORTB0,PORTB1,PORTB2};
volatile uint8_t *led_ports[3]={&PORTB,&PORTB,&PORTB};
volatile uint8_t pin=0;
volatile uint8_t rgb[3]={200,200,10};

ISR(TIMER0_OVF_vect){
	
	
	uint8_t prv_pin=(pin+2)%3;
	*led_ports[prv_pin] &= ~(1<<led_pins[prv_pin]);	
	*led_ports[pin] |= 1<<led_pins[pin];
	pin=(pin+1)%3;
	PWM_OCR=rgb[pin];
	
}

void pwm_init(){
	DDRD |= 1<< PWM_PIN;
	DDRB |= 1<< PORTB0 | 1<<PORTB1 | 1<<PORTB2 | 1<<PORTB3;
	
	//timer0 A inverting mode fast PWM
	TCCR0A |= 1<<COM0A1 | 1<<COM0A0 | 1<< WGM01 | 1<< WGM00;
	
	PWM_OCR=125;
	
	//enable overflow interrupt
	TIMSK0 |= 1<<TOIE0;
	
	//start timer0 (no-prescaler)
	//TCCR0B |= 1<<CS00;
	
	//start timer0 (256 prescaler)
	TCCR0B |= 1<<CS02;
	
	//start timer0 (1024 prescaler)
	//TCCR0B |= 1<<CS02 | 1<<CS00;
	
	sei();
	//PORTD &=~(1<<PORTD6);
	
}

void check_init(){
	DDRD |= 1<< PWM_PIN;
	DDRB |= 1<< PORTB0 | 1<<PORTB1 | 1<<PORTB2 | 1<<PORTB3;
	PORTD &=~(1<<PORTD6);
}

void check(){
	uint8_t prv_pin=(pin+2)%3;
	*led_ports[prv_pin] &= ~(1<<led_pins[prv_pin]);
	*led_ports[pin] |= 1<<led_pins[pin];
	pin=(pin+1)%3;
	_delay_ms(1000);
}
