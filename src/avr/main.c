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

uint16_t reading[3]; //sensor readings
uint8_t rgb[3];		 //rgb values
char *rgb_str[3]={"RED = ","GREEN = ","BLUE = "};

//declaring fucnitons for modes
void sensor_mode();
void calib_mode();
void read_mode();
void rgb_mode();


int main(void)
{
	//init cores
	lcd_init();	
	keypad_init();
	sensor_init();
	pwm_init();
	
	//display a startup message
	lcd_clear();
	lcd_string("RGB Color Sensor");
	lcd_set_cursor(1,4);
	lcd_string("Group 2");
	_delay_ms(3000);	
	
	while (1){

		//display the main menu
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_string("1 - Color Sensor");	
		lcd_set_cursor(1,0);
		lcd_string("2 - Given RGB");

		//get the input key to select options from main menu
		char mainmenu_key=keypad_get_key();
		
		//key1: goto color sensor mode
		if (mainmenu_key=='1')sensor_mode();

		//key2: goto given value RGB mode
		else if (mainmenu_key=='2')rgb_mode();
		
		//debounce delay
		_delay_ms(300);
	}
}

void calib_mode(){		
	lcd_clear();
	lcd_set_cursor(0,2);
	lcd_string("Calibration");
	lcd_set_cursor(1,4);
	lcd_string("Started");
	_delay_ms(2000);

	//start calibration for colors
	calib_start();	
	
	lcd_clear();
	lcd_set_cursor(0,2);
	lcd_string("Calibration");
	lcd_set_cursor(1,5);
	lcd_string("Done");
	_delay_ms(2000);
}

void read_mode(){
	
	while (1)
	{
		lcd_clear();				
		lcd_string("Place on color");
		lcd_string_blink("...Waiting...",2,1,1);		
		
		//get readings and calculate the color
		sensor_read(reading);
		calib_calc(reading,rgb);

		//display color code
		lcd_clear();
		lcd_set_cursor(0,2);
		lcd_string("@ ");
		lcd_uint8_arr(rgb);
		lcd_set_cursor(1,0);
		lcd_string("Menu=<-  Read=->");

		//ligt up RGB led with respective color
		pwm_set(rgb);
		pwm_start();

		//ask for continue or stop 		
		while (1){
			char con_key=keypad_get_key();
			if (con_key==OK_KEY){
				pwm_stop();
				break;
			}
			if(con_key==BACK_KEY){
				pwm_stop();
				_delay_ms(300);
				return;
			}
		}
	}
	
}

void sensor_mode(){
	
	lcd_clear();
	lcd_set_cursor(0,2);
	lcd_string("Color Sensor");
	_delay_ms(2000);

	while (1){

		//display a menu for calibrating or reading color values
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_string("1-Calib   2-Read");
		lcd_set_cursor(1,5);
		lcd_string("Menu=<-");

		char value='\0';
		while(value=='\0'){
			value=keypad_get_key();
			
			if (value==BACK_KEY){
				_delay_ms(300);
				break;
			}

			//key1: goto calibraiton mode
			else if (value=='1') calib_mode();
			
			//key2: goto color reading mode
			else if (value=='2') read_mode();
		}

		//back key: exit from sensor mode
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

	//get RGB values
	for (int color=0;color<3;color++){
		lcd_clear_line(1);
		lcd_string(rgb_str[color]);		//display the color name
		
		
		int rgb_value=0;	//given value
		int len_value=0;	//length of the input value
		
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
				//display pressed key on lcd display
				lcd_char(key);			
				_delay_ms(300);

				//calculate the integer value from pressed keys
				rgb_value=rgb_value*10+(key-'0');
				len_value+=1;
			}
		}

		//check whether the entered value is valid
		if (rgb_value>255){
			lcd_clear();
			lcd_set_cursor(0,2);
			lcd_string("Invalid input");
			_delay_ms(2000);

			//if the value is invalid allow to enter that value again
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
	
	lcd_clear();
	lcd_set_cursor(0,2);
	lcd_string("Given Value");
	lcd_set_cursor(1,6);
	lcd_string("RGB");
	_delay_ms(2000);

	while(1){
		
		//get rgb color code input
		rgb_input();

		//display the entered color values
		lcd_clear();
		lcd_set_cursor(0,2);
		lcd_string("@ ");
		lcd_uint8_arr(rgb);
		lcd_set_cursor(1,0);
		lcd_string("Menu=<-   RGB=->");
		
		//ligt up RGB led with the enterd color
		pwm_set(rgb);
		pwm_start();

		//ask for continue with this mode or go back to menu
		char con_key;
		while (1){
			con_key=keypad_get_key();
			if (con_key==OK_KEY || con_key==BACK_KEY){
				break;
			}
		}

		//exit from given value rgb mode
		if(con_key==BACK_KEY){		
			pwm_stop();
			break;
		}
		
		//debounce delay
		_delay_ms(300);
	}
}
