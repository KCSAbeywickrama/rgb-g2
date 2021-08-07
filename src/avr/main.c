/*
 * avr_keypad.c
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

uint16_t sensor_read_values[3];
char *color_array[3]={"R = ","G = ","B = "};		//given rgb output color names
uint8_t color_values_array[3]={0,0,0};			//given rgb color values


void color_sensor();
void calibration();
void given_rgb();


int main(void)
{
	keypad_init();		//initialize the keypad
	lcd_init();			//initialize the lcd display
	sensor_init();		//initialize the sensor

	//display a welcome message
	lcd_clear();
	//lcd_set_cursor(0,4);
	//lcd_string("Welcome");
	//lcd_set_cursor(1,4);
	//lcd_string("Group 2");
	//_delay_ms(3000);
	
    while (1){
		//display the main menu
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_string("1 - color sensor");		//input key 1 for the color sensor
		lcd_set_cursor(1,0);
		lcd_string("2 - given RGB");		//input key 2 for the given value RGB output

		//get the input key to select options from main menu
		char mainmenu_key=' ';
		mainmenu_key=keypad_get_key();
		_delay_ms(300);
		lcd_clear();

		//color sensor
		if (mainmenu_key=='1'){
			color_sensor();
		}

		//given value RGB output
		if (mainmenu_key=='2'){
			//display a startup message
			lcd_clear();
			lcd_set_cursor(0,2);
			lcd_string("given value");
			lcd_set_cursor(1,6);
			lcd_string("RGB");
			_delay_ms(2000);

			while(1){
				//call the function
				given_rgb();

				//ask for continue or stop the feature
				char con_key;
				while (1){
					con_key=keypad_get_key();
					_delay_ms(300);
					if (con_key==OK_KEY || con_key==BACK_KEY){
						break;
					}
				}
				if (con_key==OK_KEY){			//input key # for continue
					continue;
				}
				else if(con_key==BACK_KEY){		//input key * for go back to main menu
					break;
				}
			}
		}

    }
}

void calibration(){
	//display a message
	lcd_clear();
	lcd_set_cursor(0,2);
	lcd_string("Calibration");
	lcd_set_cursor(1,4);
	lcd_string("started");
	_delay_ms(2000);

	//start calibration for colors
	calib_run();
	_delay_ms(2000);
}

void color_sensor(){
	//display a "color sensor" message
	lcd_clear();
	lcd_set_cursor(0,2);
	lcd_string("color sensor");
	_delay_ms(2000);

	while (1){
		//display a menu for calibration or reading color values
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_string("1-calib   2-read");
		lcd_set_cursor(1,0);
		lcd_string("menu=<-");

		char value='a';
		while(value=='a'){
			value=keypad_get_key();

			if (value==BACK_KEY){
				_delay_ms(300);
				break;
			}

			else if (value=='1'){
				//_delay_ms(300);
				//lcd_clear();
				//lcd_string("calibration");
				//_delay_ms(2000);
				calibration();
			}

			else if (value=='2'){
				lcd_clear();
				lcd_string("Place on color");
				lcd_string_blink("...Waiting...",5,1,1);
				sensor_read(sensor_read_values);
				lcd_clear();
				lcd_set_cursor(0,3);
				lcd_string("Reading");
				lcd_set_cursor(1,2);
				lcd_string("finished");
				_delay_ms(2000);
			}
		}
		if (value==BACK_KEY){
			break;
		}
	}
}


void given_rgb(){
	//display a message to enter values
	lcd_clear();
	lcd_set_cursor(0,0);
	lcd_string("Enter values");

	//get RGB values for three colors
	for (int color=0;color<3;color++){
		lcd_clear_line(1);
		lcd_string(color_array[color]);		//display the color name
		
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
				if (len_value!=0){
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
		//if inputs are ok, then add them to the color values array
		else{
			color_values_array[color]=rgb_value;
		}
	}
	//display a "Successfully" end message and options for continue or not
	lcd_clear();
	lcd_set_cursor(0,5);
	lcd_string("@");
	lcd_set_cursor(1,0);
	lcd_string("menu=<-   RGB=->");
}





//int main(){
	//while (1){
		//char value='a';
		//value=keypad_get_key();
		//lcd_char(value);
		//_delay_ms(300);
//
	//}
//}