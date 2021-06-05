/*
 * lcd.c
 *
 * Created: 5/19/2021 12:49:00 AM
 *  Author: Yohan Abeysinghe 1
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define LCD_EN PORTD
#define RS PB0				/* Define Register Select pin */
#define EN PD7				/* Define Enable signal pin */

void lcd_command( unsigned char cmnd )
{
	//LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port = (LCD_Port & 0b1001) | (cmnd & 0b110000)>>3 | (cmnd & 0b11000000)>>2;
	LCD_Port &= ~ (1<<RS);		/* RS=0*/
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);

	_delay_us(200);

	//LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	cmnd<<=4;
	LCD_Port = (LCD_Port & 0b1001) | (cmnd & 0b110000)>>3 | (cmnd & 0b11000000)>>2;
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);
	_delay_ms(2);
}



