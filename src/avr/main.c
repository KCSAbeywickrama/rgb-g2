/*
* main.c
*
* Created: 6/12/2021 11:27:28 PM
* Author : Dulanjana
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "cores/lcd.h"
#include "cores/keypad.h"
#include "cores/pwm.h"
#include "cores/calib.h"
#include "cores/sensor.h"

uint16_t sensor_reading[3];

uint8_t rgb[3]={255,0,0};						//rgb values
char *rgb_str[3]={"R = ","G = ","B = "};	//rgb strings


void sensor_mode();
void calib_mode();
void read_mode();
void rgb_mode();


int main(void)
{
	lcd_init();			//initialize the lcd display
	keypad_init();		//initialize the keypad	
	sensor_init();		//initialize the sensor
	pwm_init();
	

	//display a welcome message
	//lcd_clear();
	//lcd_set_cursor(0,4);
	//lcd_string("RGB Color Sensor");
	//lcd_set_cursor(1,4);
	//lcd_string("Group 2");
	//_delay_ms(3000);
	
	while (1){
		//display the main menu
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_string("1 - Color Sensor");		//input key 1 for the color sensor
		lcd_set_cursor(1,0);
		lcd_string("2 - Given RGB");		//input key 2 for the given value RGB output

		//get the input key to select options from main menu
		char mainmenu_key=keypad_get_key();		
		if (mainmenu_key=='1')sensor_mode();
		else if (mainmenu_key=='2')rgb_mode();
		
		_delay_ms(300);
	}
}

void calib_mode(){
	//display a message
	lcd_clear();
	lcd_set_cursor(0,2);
	lcd_string("Calibration");
	lcd_set_cursor(1,4);
	lcd_string("Started");
	_delay_ms(2000);

	//start calibration for colors
	calib_run();
	_delay_ms(2000);
}

void read_mode(){
	lcd_clear();
	lcd_string("Place on color");
	lcd_string_blink("...Waiting...",5,1,1);
	sensor_read(sensor_reading);	
	lcd_set_cursor(1,2);
	lcd_string("Done");
	_delay_ms(2000);
}

void sensor_mode(){
	//display a "Color Sensor" message
	lcd_clear();
	lcd_set_cursor(0,2);
	lcd_string("Color Sensor");
	_delay_ms(2000);

	while (1){
		//display a menu for calibration or reading color values
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_string("1-Calib   2-Read");
		lcd_set_cursor(1,5);
		lcd_string("Menu=<-");

		char value='a';
		while(value=='a'){
			value=keypad_get_key();

			if (value==BACK_KEY){
				_delay_ms(300);
				break;
			}

			else if (value=='1') calib_mode();
			else if (value=='2') read_mode();
		}
		if (value==BACK_KEY){
			break;
		}
	}
}

void rgb_input(){
	//display a message to enter values
	lcd_clear();
	lcd_set_cursor(0,0);
	lcd_string("Enter values");

	//get RGB values for three colors
	for (int color=0;color<3;color++){
		lcd_clear_line(1);
		lcd_string(rgb_str[color]);		//display the color name
		
		//get values
		int rgb_value=0;		//given rgb value
		int len_value=0;		//length of the input rgb value
				
		while(1){
			char key=keypad_get_key();

			//break and go to next color
			if (key==OK_KEY){
				_delay_ms(300);
				break;
			}
			//delete a wrong input character
			else if (key==BACK_KEY){
				if (len_value){
					lcd_delete();
					_delay_ms(300);
					rgb_value/=10;
					len_value-=1;
				}
			}

			else{
				lcd_char(key);			//display input keys on lcd display
				_delay_ms(300);
				rgb_value=rgb_value*10+(key-'0');		//calculate the integer value from given character keys
				len_value+=1;
			}
		}



		//check whether the input value is wrong
		if (rgb_value>255){
			lcd_clear();
			lcd_set_cursor(0,2);
			lcd_string("Invalid input");		//display an invalid message
			_delay_ms(2000);
			lcd_clear();
			lcd_set_cursor(0,0);
			lcd_string("Enter values");
			color-=1;
		}
		//if inputs are OK, then add them to the rgb array
		else{
			rgb[color]=rgb_value;
		}
	}
}


void rgb_mode(){
	//display a startup message
	lcd_clear();
	lcd_set_cursor(0,2);
	lcd_string("Given Value");
	lcd_set_cursor(1,6);
	lcd_string("RGB");
	_delay_ms(2000);

	while(1){
		//call the function
		rgb_input();
		
		pwm_set(rgb);
		pwm_start();

		//display a "Successfully" end message and options for continue or not
		lcd_clear();
		lcd_set_cursor(0,2);
		lcd_string("@");
		lcd_uint8_arr(rgb);		
		lcd_set_cursor(1,0);
		lcd_string("Menu=<-   RGB=->");

		//ask for continue or stop the feature
		char con_key;
		while (1){
			con_key=keypad_get_key();			
			if (con_key==OK_KEY || con_key==BACK_KEY){
				break;
			}
		}
		
		if(con_key==BACK_KEY){		//input key * for go back to main menu
			pwm_stop();
			break;
		}
		
		_delay_ms(300);
	}
}
