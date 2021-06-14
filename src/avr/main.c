/*
* avr.c
*
* Created: 07-May-21 5:12:49 PM
* Author : CSA
*/


#define F_CPU 16000000UL

#include <avr/io.h>
#include "cores/lcd.h"
#include <util/delay.h>
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
		LCD_SetCursor(0,0);
		LCD_String("Enter values");
		LCD_SetCursor(1,0);
		LCD_String(color_string_array[color]);
		char ch;
		int val=0;
		
		while(1){
			
			ch=keypad_getKey();
			
			if (ch=='#'){
				break;
			}
			
			LCD_Char(ch);
			int digit=ch-'0';
			val = val * 10 + digit;
			
			
		}
		
		LCD_Clear();
		rgbvalue[color]=val;
				
		LCD_Clear();
	}
}

int main()
{

	int keypadPins[7]={r0,r1,r2,r3,c0,c1,c2};
	set_keypad(keypadPins);	
	LCD_Init();
	LCD_String("Welcome");
	LCD_Command(0xC0);
	LCD_String("Group 2");
	
	while(1);
}                                                        
	_delay_ms(1000);
	LCD_Clear();
	_delay_ms(500);


	led_init();
	while(1){
		
		uint8_t rgbvalue[3];
		given_RGB(rgbvalue);
		led_on(rgbvalue);
		LCD_Clear();
		
	}
}
