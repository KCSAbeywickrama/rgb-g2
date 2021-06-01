/*
* calib.c
*
* Created: 01-Jun-21 6:45:02 PM
*  Author: CSA
*/

<<<<<<< HEAD
=======
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lib/usart.h"
#include "calib.h"

>>>>>>> 18V
#define RED 0
#define GREEN 1
#define BLUE 2

uint16_t expected[5][3]={
	{255,0,0},
	{0,255,0},
	{0,0,255},
	{0,0,0},
	{255,255,255}
};

uint16_t readings[5][3];

void lcd_init(){
	uart_init(BAUD_CALC(9600)); // 8n1 transmission is set as default
	
	sei(); // enable interrupts, library wouldn't work without this
}

void lcd_string(char *str){
	uart_puts(str);	
}

void lcd_int(uint8_t i){
	uart_putint(i);
}

void lcd_char(char ch){
	uart_putc(ch);
}

void lcd_int_arr(uint8_t *arr){
	lcd_int(arr[0]);lcd_char(',');
	lcd_int(arr[1]);lcd_char(',');
	lcd_int(arr[2]);	
}

void get_readings(){
	lcd_init();
	lcd_init(5);
	lcd_char('a');
	lcd_string("hello");
}