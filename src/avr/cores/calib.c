/*
* calib.c
*
* Created: 01-Jun-21 6:45:02 PM
*  Author: K.C.S. Abeywickrama
*/
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "calib.h"
#include "lcd.h"
#include "sensor.h"

uint16_t readings[3][3];
float coffs[3][2];
char *colors[5]={"RED","GREEN","BLUE"};

uint16_t max(uint16_t v1,uint16_t v2){
	if(v1>v2) return v1;
	return v2;
}

uint8_t trim(float v){
	if(v<15) return 0;
	if(v>240) return 255;
	return (uint8_t)v;
}

void calib_start(){
	
	for(uint8_t i=0;i<3;i++){		
		lcd_clear();
		lcd_string("Place on ");
		lcd_string(colors[i]);
		lcd_string_blink("...Waiting...",5,1,1);
		sensor_read(readings[i]);
		lcd_set_cursor(1,0);
		lcd_uint16_arr(readings[i]);
		_delay_ms(2000);
	}	
	
	
	for(uint8_t i=0;i<3;i++){
		uint16_t h=readings[i][i];
		uint16_t l=max(readings[(i+1)%3][i],readings[(i+2)%3][i]);
		
		float m=255.0/(h-l);
		float c=-m*l;
		
		coffs[i][0]=m;
		coffs[i][1]=c;	
	}	
	
}

void calib_calc(uint16_t *reading,uint8_t *rgb){
	
	for(uint8_t i=0;i<3;i++){
		uint8_t value=trim(coffs[i][0]*reading[i]+coffs[i][1]);
		rgb[i]=value;
	}
}