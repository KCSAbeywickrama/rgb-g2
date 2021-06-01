/*
 * avr.c
 *
 * Created: 07-May-21 5:12:49 PM
 * Author : CSA
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include "cores/lcd.h"
#include "cores/led.h"


#define r0 23
#define r1 24
#define r2 25
#define r3 26
#define c0 4
#define c1 5
#define c2 6

char *color_string_array[]={"R = ","G = ","B = "};

void given_RGB(uint8_t *rgbvalue){
	
	
	
	for (int color=0;color<3;color++){
		lcd_setcursor(0,0);
		lcd_string("Enter values");
		lcd_setcursor(1,0);
		lcd_string(color_string_array[color]);
		char ch;
		int val=0;
		
		while(1){
			
			ch=keypad_getKey();
			
			if (ch=='#'){
				break;
			}
			
			lcd_char(ch);
			int digit=ch-'0';
			val = val * 10 + digit;
			
			
		}
		
		lcd_clear();
		rgbvalue[color]=val;
				
		lcd_clear();
	}
}


int main()
{
	int keypadPins[7]={r0,r1,r2,r3,c0,c1,c2};
	set_keypad(keypadPins);	
	lcd_init();
	lcd_string("Welcome");
	lcd_command(0xC0);
	lcd_string("Group 2");
	
	

	led_init();
	while(1){
		
		uint8_t rgbvalue[3];
		given_RGB(rgbvalue);
		led_on(rgbvalue);
		lcd_clear();
		
	}
}
