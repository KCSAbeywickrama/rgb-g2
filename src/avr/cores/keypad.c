/*
 * keypad.c
 *
 * Created: 5/19/2021 12:22:11 AM
 *  Author: Dulanjana
 */ 

 #define F_CPU 8000000UL
 #include <avr/io.h>
 #include <util/delay.h>
 #include "keypad.h"

 #define ROW_DDR DDRC
 #define ROW_PORT PORTC
 #define ROW_PIN PINC
 #define COL_DDR DDRD
 #define COL_PORT PORTD
 #define COL_PIN PIND

 const uint8_t ROW_PINS[4]={PORTC0,PORTC1,PORTC2,PORTC3};
 const uint8_t COL_PINS[4]={PORTD2,PORTD3,PORTD4};

const char KEYS[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};

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
