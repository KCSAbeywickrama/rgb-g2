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
	COL_DDR &= ~(0x1c);
	COL_PORT |= 0x1c;
	ROW_DDR |= 0x0f;
 }

 void set_port(char *str){
	for (int bit=0;bit<4;bit++){
		if (str[bit]=='1'){
			ROW_PORT |= 1<<ROW_PINS[bit];
		}
		else{
			ROW_PORT &= ~(1<<ROW_PINS[bit]);
		}
	}
 }

 char keypad_get_key(){
	char value='\0';
	while (value=='\0'){
		for (int col=0;col<3;col++){
			set_port("0111");
			if(~COL_PIN & 1<<COL_PINS[col]){
				value=KEYS[0][col];
			}
			set_port("1011");
			if(~COL_PIN & 1<<COL_PINS[col]){
				value=KEYS[1][col];
			}
			set_port("1101");
			if(~COL_PIN & 1<<COL_PINS[col]){
				value=KEYS[2][col];
			}
			set_port("1110");
			if(~COL_PIN & 1<<COL_PINS[col]){
				value=KEYS[3][col];
			}
		}
	}
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