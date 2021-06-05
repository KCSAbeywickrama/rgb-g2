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

void lcd_init(void)			/* LCD Initialize function */
{
	//LCD_Dir = 0xFF;			/* Make LCD port direction as o/p */
	LCD_Dir |= 0b110111;
	DDRD |= 1<<EN;
	_delay_ms(20);			/* Delay to power on the LCD */
	
	lcd_command(0x02);				/* send for 4 bit initialization  */
	lcd_command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	lcd_command(0x0c);              /* Display on cursor off*/
	lcd_command(0x06);              /* Increment cursor (shift cursor to right)*/
	lcd_command(0x01);              /* Clear display screen*/
	_delay_ms(2);
}

void lcd_setcursor(int row_index,int col_index){
	if (row_index==0){
		lcd_command(0x80);
	}
	if (row_index==1){
		lcd_command(0xC0);
	}
	for (int temp=0;temp<col_index;temp++){
		lcd_command(0x14);
	}
}


void lcd_char( unsigned char data )
{
	//LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port = (LCD_Port & 0b1001) | (data & 0b110000)>>3 | (data & 0b11000000)>>2;
	LCD_Port |= (1<<RS);		/* RS=1 */
	LCD_EN|= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);

	_delay_us(200);

	//LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	data<<=4;
	LCD_Port = (LCD_Port & 0b1001) | (data & 0b110000)>>3 | (data & 0b11000000)>>2;
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);
	_delay_ms(2);
}

void lcd_string(char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char */
	{
		lcd_char(str[i]);
	}
}

void lcd_int(uint8_t i)
{
	lcd_char(i+'0');
}


