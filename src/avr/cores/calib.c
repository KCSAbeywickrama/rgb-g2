/*
* calib.c
*
* Created: 01-Jun-21 6:45:02 PM
*  Author: K.C.S. Abeywickrama
*/
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../libs/usart.h"
#include "calib.h"
//#include "sensor.h"

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

void calib_init(){
	print_init();
	//while(1){
		//print_int(sensor_read(5));
		//println();
		//_delay_ms(500);
	//}
	
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

uint8_t trim(float v){
	if(v<0) return 0;
	if(v>255) return 255;
	return (uint8_t)v;
}

void calib_start(){
	
	print_string("Calibration started\r\n");
	
	for(uint8_t i=0;i<3;i++){
		print_string("Place on ");
		print_string(colors[i]);
		blink();
		get_reading(readings[i]);
	}
	
	for(uint8_t i=0;i<3;i++){
		print_uint16_arr(readings[i]);
		println();
	}
	println();
	
	
	for(uint8_t i=0;i<3;i++){
		uint16_t h=readings[i][i];
		uint16_t l=max(readings[(i+1)%3][i],readings[(i+2)%3][i]);
		
		float m=255.0/(h-l);
		float c=-m*l;
		
		coffs[i][0]=m;
		coffs[i][1]=c;
		
		print_float(m);
		print_char(',');
		print_float(c);
		println();
	}
	
	println();
	
	print_string("Calibration finished\r\n");
}

void calc(uint16_t *reading,uint8_t *color){
	
	for(uint8_t i=0;i<3;i++){
		uint8_t value=trim(coffs[i][0]*reading[i]+coffs[i][1]);
		color[i]=value;
	}
}

void get_color(){
	//for(uint8_t i=0;i<36;i++){
	//uint8_t calc_color[3];
	//calc(rd_i[i],calc_color);
	//print_uint8_arr(calc_color);
	//println();
	//}
	
	//for(uint8_t i=0;i<5;i++){
		//uint8_t calc_color[3];
		//calc(readings[i],calc_color);
		//print_uint8_arr(calc_color);
		//println();
	//}
	print_string("\r\nPlace on a color");
	
	blink();
	
	uint16_t reading[3];
	get_reading(reading);
	
	uint8_t calc_color[3];
	calc(reading,calc_color);
	print_uint8_arr(calc_color);
	print_string(" \r\n");
	_delay_ms(500);
	
}