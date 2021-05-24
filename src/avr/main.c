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
	LCD_Init();
	LCD_String("Welcome");
	LCD_Command(0xC0);
	LCD_String("Group 2");
	while(1);
}                                                        