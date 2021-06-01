/*
* calib.c
*
* Created: 01-Jun-21 6:45:02 PM
*  Author: CSA
*/
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../libs/usart.h"
#include "calib.h"
#include "sensor.h"

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
double coffs[3][2];

char *colors[5]={"RED","GREEN","BLUE","WHITE","BLACK"};

void print_init(){
	uart_init(BAUD_CALC(9600));
	sei();
}

void print_string(char *str){
	uart_puts(str);
}

void print_int(uint16_t i){
	uart_putint(i);
}

void print_char(char ch){
	uart_putc(ch);
}

void print_int_arr(uint16_t *arr){
	print_int(arr[0]);print_char(',');
	print_int(arr[1]);print_char(',');
	print_int(arr[2]);
}

void println(){	
	uart_puts("\r\n");
}

void calib_init(){
	print_init();
}

void blink(){
	for(uint8_t i=0;i<5;i++){
		print_char('.');
		_delay_ms(1000);
	}
	print_char('*');
	println();
}

uint16_t max(uint16_t v1,uint16_t v2){
	if(v1>v2) return v1;
	return v2;
}

uint8_t trim(double v){
	return 0;
}

void start_calib(){
	for(uint8_t i=0;i<3;i++){
		print_string("Place on ");
		print_string(colors[i]);
		blink();
		get_readings(readings[i]);		
	}
	
	for(uint8_t i=0;i<3;i++){
		print_int_arr(readings[i]);
		println();
	}	
	
	for(uint8_t i=0;i<3;i++){
		uint16_t h=readings[i][i];
		uint16_t l=max(readings[(i+1)%3][i],readings[(i+2)%3][i]);
		
		double m=(double)255/(h-l);
		double c=-m*l;
		
		coffs[i][0]=m;
		coffs[i][1]=c;
	}
	
	
	
	
}

void get_readings(uint16_t *reading){
	PORTC |= 1<<PORTC4; // high red led
	_delay_ms(2000);
	reading[0] = sensor_read(5); // take the ldr value for red
	PORTC &= ~(1<<PORTC4); // low red led
	
	PORTB |= 1<<PORTB4; // high green led
	_delay_ms(2000);
	reading[1]  = sensor_read(5); // ldr value for green
	PORTB &= ~(1<<PORTB4); // low green led
	
	PORTB |= 1<<PORTB5; // blue
	_delay_ms(2000);
	reading[2]  = sensor_read(5);
	PORTB &= ~(1<<PORTB5);
}