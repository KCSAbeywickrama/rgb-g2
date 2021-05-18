/*
 * avr.c
 *
 * Created: 07-May-21 5:12:49 PM
 * Author : CSA
 */ 

#include <avr/io.h>
#include "cores/led.h"

int main(void)
{
	led_init();
	led_on_args(0,200,0);
 
	
    while (1) 
    {
    }
}

