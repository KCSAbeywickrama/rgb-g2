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
	
	lcd_custom_char(0, ch_correction);
	lcd_custom_char(1, ch_for);
	lcd_custom_char(2, ch_back);
	lcd_custom_char(3, ch_bulbon);
	lcd_custom_char(4, ch_bulboff);
	
	lcd_command(0xC0);
	lcd_char(0);
	lcd_char(1);
	lcd_char(2);
	lcd_char(3);
	lcd_char(4);
	
	while(1);
}
