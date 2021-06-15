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
	//check_init();
	//while(1){
		//check();
	//}
	while(1);
}




