/*
 * avr.c
 *
 * Created: 07-May-21 5:12:49 PM
 * Author : CSA
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include "cores/lcd.h"

int main()
{
	lcd_init();
	lcd_string("Welcome");
	lcd_command(0xC0);
	lcd_string("Group 2");
	while(1);
}
