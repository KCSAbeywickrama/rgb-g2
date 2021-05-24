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




#include <util/delay.h>
#include "cores/sensor.h"

int main(void)
{
	
	DDRC |= 1<<PORTC4; //set the red led PC4 pin as a output
	DDRB |= (1<<PORTB4) | (1<<PORTB5); // set PB5 and PB4 as output pins
	DDRC &= ~(1<<PORTC5); // set PC5 as a input pin
	
	adc_init();
	
    while (1) 
    {
		PORTC |= 1<<PORTC; // high red led
		_delay_ms(2000);
		int red_read = analog_read(5); // take the ldr value for red
		PORTC &= ~(1<<PORTC4); // low red led
		
		PORTB |= 1<<PORTB4; // high green led
		_delay_ms(2000);
		int green_read = analog_read(5); // ldr value for green
		PORTB &= ~(1<<PORTB4); // low green led
		
		PORTB |= 1<<PORTB5; // blue
		_delay_ms(2000);
		int blue_read = analog_read(5); 
		PORTB &= ~(1<<PORTB5);
		
		int red_val = calib(red_read,0); // final red value
		int green_val = calib(green_read,1); // final green value
		int blue_val = calib(blue_read,2); // final blue value
		
    }
}

