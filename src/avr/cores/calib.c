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
	{255, 0, 0},
	{0, 255, 0},
	{0, 0, 255},
	{0, 0, 0},
	{255, 255, 255}
};

uint16_t readings[5][3]={
	{660, 131, 125},
	{397, 236, 126},
	{303, 161, 214},
	{306, 104, 98},
	{663, 337, 306},
};

uint16_t rd_i[36][3]={
	{579, 113, 111},
	{506, 111, 103},
	{414, 104, 98},
	{354, 93, 92},
	{658, 180, 108},
	{590, 149, 100},
	{513, 130, 97},
	{430, 115, 100},
	{357, 105, 92},
	{661, 326, 121},
	{623, 293, 118},
	{528, 220, 104},
	{420, 152, 95},
	{333, 115, 90},
	{367, 223, 120},
	{360, 212, 116},
	{341, 178, 112},
	{310, 124, 101},
	{297, 138, 186},
	{295, 127, 153},
	{294, 112, 122},
	{293, 103, 101},
	{325, 129, 182},
	{323, 120, 164},
	{304, 110, 128},
	{302, 106, 112},
	{308, 104, 104},
	{401, 136, 189},
	{390, 133, 189},
	{351, 119, 176},
	{321, 117, 145},
	{305, 104, 104},
	{611, 286, 262},
	{528, 216, 194},
	{414, 144, 129},
	{334, 109, 100}
};

float coffs[3][2];

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

void print_float(float v){
	uart_putfloat(v);
}

void print_uint16_arr(uint16_t *arr){
	print_int(arr[0]);print_char(',');
	print_int(arr[1]);print_char(',');
	print_int(arr[2]);
}

void print_uint8_arr(uint8_t *arr){
	print_int(arr[0]);print_char(',');
	print_int(arr[1]);print_char(',');
	print_int(arr[2]);
}

void println(){
	uart_puts("\r\n");
}

