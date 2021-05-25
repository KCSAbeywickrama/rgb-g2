/*
* timer.c
*
* Created: 25-May-21 12:10:18 PM
*  Author: K.C.S. Abeywickrama
*/

#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#include "timer.h"

#ifndef F_CPU
# warning "F_CPU not defined for timer. 8000000UL is default"
# define F_CPU 8000000UL
#endif

#define _INC 10
#define _PRE_SCL 64
#define _COUNT (_INC*F_CPU)/(_PRE_SCL*1000UL)-1

volatile uint32_t _millis=0;

ISR(TIMER1_COMPA_vect){
	_millis+=_INC;
}

void timer_init(){
	//start timer1 with CTC mode,64 pre-scaler
	TCCR1B|=1<<WGM12 | 1<<CS11 | 1<<CS10;
	
	cli();
	OCR1A=_COUNT;
	
	//enable interrupts on compare match OCR1A
	TIMSK1|=1<<OCIE1A;
	sei();
}

uint32_t timer_millis(){
	uint8_t sreg=SREG;
	cli();
	uint32_t millis=_millis;
	SREG=sreg;
	return millis;
}

void timer_reset(){
	uint8_t sreg=SREG;
	cli();
	_millis=0;
	SREG=sreg;
}


