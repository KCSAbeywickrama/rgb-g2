/*
* avr.c
*
* Created: 07-May-21 5:12:49 PM
* Author : CSA
*/


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "cores/pwm.h"

int main(void)
{
	pwm_init();
	
	pwm_start();	
	
	pwm_set_args(255,0,0);
	_delay_ms(1000);	
	
	
	pwm_set_args(255,127,0);
	_delay_ms(1000);
	
	pwm_set_args(100,30,110);
	_delay_ms(1000);
	
	pwm_stop();
	_delay_ms(1000);
	
	pwm_start();
	pwm_set_args(255,0,0);
	_delay_ms(1000);
	
	pwm_stop();
	_delay_ms(1000);
	
	pwm_start();
	pwm_set_args(255,100,0);
	_delay_ms(1000);
	
	pwm_stop();
	//check_init();
	//while(1){
		//check();
	//}
	while(1);
}




