/*
* avr.c
*
* Created: 07-May-21 5:12:49 PM
* Author : CSA
*/


#define F_CPU 8000000UL

#include <avr/io.h>
#include "cores/keypad.h"
#include "cores/lcd.h"
#include <util/delay.h>

#define r0 23
#define r1 24
#define r2 25
#define r3 26
#define c0 4
#define c1 5
#define c2 6

char *color_string_array[]={"R = ","G = ","B = "};

//char keys[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
//int rowPins[rows]={r0,r1,r2,r3};
//int columnPins[columns]={c0,c1,c2};
//Keypad inputKeypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);

void given_RGB(int *rgbvalue){
	//LCD_SetCursor(0,2);
	//LCD_String("given value");
	//LCD_SetCursor(1,6);
	//LCD_String("RGB");
	//_delay_ms(3000);
	//LCD_Clear();
	int arr[3];
	
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
		arr[color]=val;
		//char rgb_char[3];
		//itoa(val,rgb_char,3);
		//LCD_String(rgb_char);
		do{
			char c=(arr[color])%10+'0';
			LCD_Char(c);
			arr[color]/=10;
		}while(arr[color]!=0);
		_delay_ms(1000);
		LCD_Clear();
	}
}


int main(void)
{
	int keypadPins[7]={r0,r1,r2,r3,c0,c1,c2};
	set_keypad(keypadPins);
	//int lcdPins[]={rs,en,d4,d5,d6,d7};
	LCD_Init();

	LCD_SetCursor(0,0);
	LCD_String("Welcome");
	_delay_ms(1000);
	LCD_Clear();
	_delay_ms(500);

	while(1){
		
		int rgbvalue[3];
		given_RGB(rgbvalue);
		break;
	}
}




