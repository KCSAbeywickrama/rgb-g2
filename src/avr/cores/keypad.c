/*
 * keypad.c
 *
 * Created: 5/19/2021 12:22:11 AM
 *  Author: Dulanjana
 */ 

 #define F_CPU 16000000UL
 #include <avr/io.h>
 #include <util/delay.h>
 #include "keypad.h"
 #include "lcd.h"

 #define ROW_DDR DDRC
 #define ROW_PORT PORTC
 #define ROW_PIN PINC
 #define COL_DDR DDRD
 #define COL_PORT PORTD
 #define COL_PIN PIND



 const uint8_t ROW_PINS[4]={PORTC0,PORTC1,PORTC2,PORTC3};
 const uint8_t COL_PINS[4]={PORTD2,PORTD3,PORTD4};

 const char KEYS[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{BACK_KEY,'0',OK_KEY}};

 void keypad_init(){
	ROW_DDR &= ~(0x0f);
	COL_DDR |= 0x1c;
	ROW_PORT |= 0x0f;
 }

 void set_port(char *str){
	for (int bit=0;bit<3;bit++){
		if (str[bit]=='1'){
			COL_PORT |= 1<<COL_PINS[bit];
		}
		else{
			COL_PORT &= ~(1<<COL_PINS[bit]);
		}
	}
 }

 char keypad_get_key(){
	char value='a';
	while (value=='a'){
		for (int row=0;row<4;row++){
			set_port("011");
			if(~ROW_PIN & 1<<ROW_PINS[row]){
				value=KEYS[row][0];
			}
			set_port("101");
			if(~ROW_PIN & 1<<ROW_PINS[row]){
				value=KEYS[row][1];
			}
			set_port("110");
			if(~ROW_PIN & 1<<ROW_PINS[row]){
				value=KEYS[row][2];
			}
		}
	}
	//_delay_ms(275);
	return value;
 }

 void keypad_check(){
	lcd_clear();
	lcd_set_cursor(0,0);
	lcd_string("Keypad checking");
	lcd_set_cursor(1,0);
	char value;
	while (1){
		value=keypad_get_key();

		lcd_char(value);
		_delay_ms(300);

		if (value==OK_KEY){
			_delay_ms(1000);
			break;
		}
	}
 }