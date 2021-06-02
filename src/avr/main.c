/*
 * avr.c
 *
 * Created: 07-May-21 5:12:49 PM
 * Author : CSA
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

#include "cores/sensor.h"
#include "cores/calib.h"


int main(){
	sensor_init();
	calib_init();
	calib_start();
	get_color();
	while(1);
	
}