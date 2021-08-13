/*
* lcd.c
*
* Created: 5/19/2021 12:49:00 AM
*  Author: Yohan Abeysinghe 1
*/

#define F_CPU 16000000UL


#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define DATA_PORT0 PORTB
#define DATA_PORT1 PORTD
#define DATA_DDR0 DDRB
#define DATA_DDR1 DDRD
#define EN_DDR DDRB
#define LCD_EN PORTB
#define LCD_RS PORTB
#define RS PORTB0				/* Define Register Select pin */
#define EN PORTB1				/* Define Enable signal pin */

void lcd_command( unsigned char cmnd )
{
	DATA_PORT0 = (DATA_PORT0 & 0b11110011) | (cmnd & 0b110000)>>2;
	DATA_PORT1 = (DATA_PORT1 & 0b11111100) | (cmnd & 0b11000000)>>6;
	LCD_RS &= ~ (1<<RS);		/* RS=0*/
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);

	_delay_us(200);

	cmnd<<=4;
	DATA_PORT0 = (DATA_PORT0 & 0b11110011) | (cmnd & 0b110000)>>2;
	DATA_PORT1 = (DATA_PORT1 & 0b11111100)| (cmnd & 0b11000000)>>6;
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);
	_delay_ms(2);
}


void lcd_char( unsigned char data )
{
	DATA_PORT0 = (DATA_PORT0 & 0b11110011) | (data & 0b110000)>>2;
	DATA_PORT1 = (DATA_PORT1 & 0b11111100)| (data & 0b11000000)>>6;
	LCD_RS |= (1<<RS);		/* RS=1 */
	LCD_EN|= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);

	_delay_us(200);

	data<<=4;
	DATA_PORT0 = (DATA_PORT0 & 0b11110011) | (data & 0b110000)>>2;
	DATA_PORT1 = (DATA_PORT1 & 0b11111100)| (data & 0b11000000)>>6;
	LCD_EN |= (1<<EN);
	_delay_us(1);
	LCD_EN &= ~ (1<<EN);
	_delay_ms(2);
}

void lcd_init (void)			/* LCD Initialize function */
{
	DATA_DDR0 |= 0b1111;
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

void lcd_set_cursor(int row_index,int col_index){
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

void lcd_clear_line(int row){
	lcd_set_cursor(row,0);
	for (int position=0;position<16;position++){
		lcd_char(' ');
	}
	lcd_set_cursor(row,0);
}

void lcd_int(int value){
	int length;
	int divider;
	if (value>=100){
		length=3;
		divider=100;
	}
	else if(value>=10){
		length=2;
		divider=10;
	}
	else if(value>=0){
		length=1;
		divider=1;
	}
	for (int bit=0;bit<length;bit++){
		int quocient=value/divider;
		lcd_char(quocient+'0');
		value%=(quocient*divider);
		divider/=10;
	}
}

void lcd_float(float value){
	int a=value;
	int b=(value-a)*1000;
	lcd_int(a);
	lcd_char('.');
	lcd_int(b);
}

void lcd_delete(){
	lcd_command(0x10);
	lcd_char(' ');
	lcd_command(0x10);
}

void lcd_string_blink(char *word,int iter,int row,int column){
	lcd_clear_line(row);
	for (int blink_iter=0;blink_iter<iter;blink_iter++){
		lcd_set_cursor(row,column);
		lcd_string(word);
		_delay_ms(500);
		lcd_clear_line(row);
		_delay_ms(500);
	}
}

void lcd_uint8_arr(uint8_t *values){
	for (int color=0;color<2;color++){
		lcd_int(values[color]);
		lcd_char(',');
	}
	lcd_int(values[2]);
}

void lcd_uint16_arr(uint16_t *values){
	for (int color=0;color<2;color++){
		lcd_int(values[color]);
		lcd_char(',');
	}
	lcd_int(values[2]);
}

void lcd_check(){
	lcd_clear();
	lcd_set_cursor(0,5);
	lcd_string("LCD is");
	lcd_set_cursor(1,7);
	lcd_string("OK");
	_delay_ms(2000);
}