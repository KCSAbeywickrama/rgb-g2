/*
* avr.c
*
* Created: 07-May-21 5:12:49 PM
* Author : CSA
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "cores/lcd_my.h"
#include "cores/keypad.h"
#include "cores/led.h"

char *color_array[3]={"R = ","G = ","B = "};		//given rgb output color names
uint8_t color_values_array[3]={0,0,0};			//given rgb color values

void given_rgb();

int delay_time=300;

int main(void)
{
	keypad_init();		//initialize the keypad
	lcd_init();			//initialize the lcd display

	//display a welcome message
	lcd_set_cursor(0,4);
	lcd_string("Welcome");
	lcd_set_cursor(1,4);
	lcd_string("Group 2");
	_delay_ms(3000);
	
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
		_delay_ms(delay_time);
		lcd_clear();

		//color sensor
		if (mainmenu_key=='1'){
			lcd_string("sensor");
			_delay_ms(1000);
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
					_delay_ms(delay_time);
					if (con_key=='#' || con_key=='*'){
						break;
					}
				}
				if (con_key=='#'){			//input key # for continue
					continue;
				}
				else if(con_key=='*'){		//input key * for go back to main menu
					break;
				}
			}
		}

    }
}