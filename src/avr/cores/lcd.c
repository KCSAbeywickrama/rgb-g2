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

#define LCD_EN PORTD
#define RS PB0				/* Define Register Select pin */
#define EN PD7				/* Define Enable signal pin */


void LCD_Command( unsigned char cmnd )
{
	PORTB = (PORTB & 0b11111001) | (cmnd & 0b110000)>>3;
	PORTD = (PORTD & 0b11111100)| (cmnd & 0b11000000)>>6;
	PORTB &= ~ (1<<RS);		/* RS=0*/
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);

	_delay_us(200);

	cmnd<<=4;
	PORTB = (PORTB & 0b11111001) | (cmnd & 0b110000)>>3;
	PORTD = (PORTD & 0b11111100)| (cmnd & 0b11000000)>>6;
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_Char( unsigned char data )
{
	PORTB = (PORTB & 0b11111001) | (data & 0b110000)>>3;
	PORTD = (PORTD & 0b11111100)| (data & 0b11000000)>>6;
	PORTB |= (1<<RS);		/* RS=1 */
	LCD_EN|= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);

	_delay_us(200);

	data<<=4;
	PORTB = (PORTB & 0b11111001) | (data & 0b110000)>>3;
	PORTD = (PORTD & 0b11111100)| (data & 0b11000000)>>6;
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Init (void)			/* LCD Initialize function */
{
	DDRB |= 0b0111;
	DDRD |= 0b0011;
	DDRD |= 1<<EN;
	_delay_ms(20);			/* Delay to power on the LCD */
	
	LCD_Command(0x02);				/* send for 4 bit initialization  */
	LCD_Command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0x0c);              /* Display on cursor off*/
	LCD_Command(0x06);              /* Increment cursor (shift cursor to right)*/
	LCD_Command(0x01);              /* Clear display screen*/
	_delay_ms(2);
}


void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char */
	{
		LCD_Char (str[i]);
	}
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
}