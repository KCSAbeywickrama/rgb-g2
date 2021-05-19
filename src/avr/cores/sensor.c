/*
 * sensor.c
 *
 * Created: 19/05/2021 03:18:54
 *  Author: Lakdilu
 */ 

#include <avr/io.h>
#include "sensor.h"


//extra when it use as arduino
void pin_mode(uint8_t *_port, uint8_t _bit, uint8_t _mode){
	if (_mode){
		*_port |= 1<<_bit;
	}
}

//extra when it use as arduino
void digital_write(uint8_t *port, uint8_t bite, uint8_t state){
	if (state){
		*port |= 1<<bite;
	}
	
}

void analog_read (){
	
}

int calib(uint8_t val, uint8_t clr){
	const float R_MAX = 400;
	const float R_MIN = 150;
	const float G_MAX = 365;
	const float G_MIN = 98;
	const float B_MAX = 517;
	const float B_MIN = 175;
	
	if (clr == 0){
		val = limit(val,R_MAX,R_MIN);
		val = (val - R_MIN)*(255/(R_MAX - R_MIN));
	}
	
	else if (clr == 1){
		val = limit(val,G_MAX,G_MIN);
		val = (val - G_MIN)*(255/(G_MAX - G_MIN));
	}
	
	else if (clr == 2){
		val = limit(val,B_MAX,B_MIN);
		val = (val - B_MIN)*(255/(B_MAX - B_MIN));
	}
	
	return val;
	
}

int limit (uint8_t _val, uint8_t _max, uint8_t _min){
	if (_val > _max)
	_val = _max;
	
	else if (_val < _min)
	_val = _min;
	
	return _val;
}
