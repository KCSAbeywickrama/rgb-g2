/*
 * lcd.c
 *
 * Created: 6/13/2021 8:08:28 PM
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


void LCD_Command( unsigned char cmnd )
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


void LCD_Char( unsigned char data )
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

void LCD_Init (void)			/* LCD Initialize function */
{
	//LCD_Dir = 0xFF;			/* Make LCD port direction as o/p */
	LCD_Dir |= 0b110111;
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

void LCD_SetCursor(int row_index,int col_index){
	if (row_index==0){
		LCD_Command(0x80);
	}
	if (row_index==1){
		LCD_Command(0xC0);
	}
	for (int temp=0;temp<col_index;temp++){
		LCD_Command(0x14);
	}
}