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

#define DATA_PORT0 PORTB
#define DATA_PORT1 PORTD
#define DATA_DDR0 DDRB
#define DATA_DDR1 DDRD
#define EN_DDR DDRD
#define LCD_EN PORTD
#define LCD_RS PORTB
#define RS PB0				/* Define Register Select pin */
#define EN PD7				/* Define Enable signal pin */


void lcd_command( unsigned char cmnd )
{
	DATA_PORT0 = (DATA_PORT0 & 0b11111001) | (cmnd & 0b110000)>>3;
	DATA_PORT1 = (DATA_PORT1 & 0b11111100) | (cmnd & 0b11000000)>>6;
	LCD_RS &= ~ (1<<RS);		/* RS=0*/
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);

	_delay_us(200);

	cmnd<<=4;
	DATA_PORT0 = (DATA_PORT0 & 0b11111001) | (cmnd & 0b110000)>>3;
	DATA_PORT1 = (DATA_PORT1 & 0b11111100)| (cmnd & 0b11000000)>>6;
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);
	_delay_ms(2);
}


void lcd_char( unsigned char data )
{
	DATA_PORT0 = (DATA_PORT0 & 0b11111001) | (data & 0b110000)>>3;
	DATA_PORT1 = (DATA_PORT1 & 0b11111100)| (data & 0b11000000)>>6;
	LCD_RS |= (1<<RS);		/* RS=1 */
	LCD_EN|= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);

	_delay_us(200);

	data<<=4;
	DATA_PORT0 = (DATA_PORT0 & 0b11111001) | (data & 0b110000)>>3;
	DATA_PORT1 = (DATA_PORT1 & 0b11111100)| (data & 0b11000000)>>6;
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);
	_delay_ms(2);
}

void lcd_init (void)			/* LCD Initialize function */
{
	DATA_DDR0 |= 0b0111;
	DATA_DDR1 |= 0b0011;
	EN_DDR |= 1<<EN;
	_delay_ms(20);			/* Delay to power on the LCD */
	
	lcd_command(0x02);				/* send for 4 bit initialization  */
	lcd_command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	lcd_command(0x0c);              /* Display on cursor off*/
	lcd_command(0x06);              /* Increment cursor (shift cursor to right)*/
	lcd_command(0x01);              /* Clear display screen*/
	_delay_ms(2);
}


void lcd_string (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char */
	{
		lcd_char (str[i]);
	}
}

void lcd_clear()
{
	lcd_command (0x01);		/* Clear display */
	_delay_ms(2);
	lcd_command (0x80);		/* Cursor at home position */
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