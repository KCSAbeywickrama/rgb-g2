/*
 * led.c
 *
 * Created: 5/10/2021 11:13:26 PM
 *  Author: Dulanjana
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include "keypad.h"
#include <util/delay.h>


//LED on
void led_on(uint8_t *port, uint8_t pin){
	*port |=1<<pin;
}
//LED off
void led_off(uint8_t *port, uint8_t pin){
	*port &= ~(1<<pin);
}

//pin configuration in IC
char *pin_set(int pin){
	char *pin_array[]={
		"PC6","PD0","PD1","PD2","PD3","PD4","VCC",
		"GND","PB6","PB7","PD5","PD6","PD7","PB0",
		"PB1","PB2","PB3","PB4","PB5","AVCC","AREF",
		"GND","PC0","PC1","PC2","PC3","PC4","PC5"};
	return pin_array[pin-1];
}

//set the DDR registers for inputs and outputs in keypad
int set_keypad(int *pin_num){
	for (int index=0;index<7;index++){
		char *pin=pin_set(pin_num[index]);
		key_pins[index]=pin;
		if(index<4){
			if(pin[1]=='B'){
				DDRB |= 0<<(pin[2]-48);
			}
			if(pin[1]=='C'){
				DDRC |= 0<<(pin[2]-48);
				led_on(&PORTB,PORTB0);
			}
			if(pin[1]=='D'){
				DDRD |= 0<<(pin[2]-48);
			}
		}
		else{
			
			if(pin[1]=='B'){
				DDRB |= 1<<(pin[2]-48);
			}
			if(pin[1]=='C'){
				DDRC |= 1<<(pin[2]-48);
			}
			if(pin[1]=='D'){
				DDRD |= 1<<(pin[2]-48);
			}
		}		
	}
	return 0;
}

//set the PORT registers in keypad
int set_port(char *bits,char **pins){
	for (int index=0;index<7;index++){
		char *pin=pins[index];
		if (index<4){
			//led_on(&PORTB,PORTB0);
			if(pin[1]=='B'){
				PORTB |= 1<<(pin[2]-48);
			}
			if(pin[1]=='C'){
				PORTC |= 1<<(pin[2]-48);
			}
			if(pin[1]=='D'){
				PORTD |= 1<<(pin[2]-48);
			}
		}
		else{
			if(pin[1]=='B'){
				if (bits[index-4]=='1'){
					PORTB |= 1<<(pin[2]-48);
				}
				if (bits[index-4]=='0'){
					PORTB &= ~(1<<(pin[2]-48));
				}
			}
			if(pin[1]=='C'){
				if (bits[index-4]=='1'){
					PORTC |= 1<<(pin[2]-48);
				}
				if (bits[index-4]=='0'){
					PORTC &= ~(1<<(pin[2]-48));
				}
			}
			if(pin[1]=='D'){				
				if (bits[index-4]=='1'){
					PORTD |= 1<<(pin[2]-48);
				}
				if (bits[index-4]=='0'){
					PORTD &= ~(1<<(pin[2]-48));
				}
			}
		}
		
	}
	return 0;
}

//set the PIN registers in keypad
int set_pin(char *pin){
	if (pin[1]=='B'){
		return (~PINB & 1<<(pin[2]-48));
	}
	if (pin[1]=='C'){
		return (~PINC & 1<<(pin[2]-48));
	}
	if (pin[1]=='D'){
		return (~PIND & 1<<(pin[2]-48));
	}
}

//get the input keys
char keypad_getKey(){
	char value;	
	while(1){
		//input char 1
		set_port("011",key_pins);
		if (set_pin(key_pins[0])){
			value='1';
			break;
		}
		//input char 2
		set_port("101",key_pins);
		if (set_pin(key_pins[0])){
			value='2';
			break;
		}
		////input char 3
		set_port("110",key_pins);
		if (set_pin(key_pins[0])){
			value='3';
			break;
		}
		////input char 4
		set_port("011",key_pins);
		if (set_pin(key_pins[1])){
			value='4';
			break;
		}
		////input char 5
		set_port("101",key_pins);
		if (set_pin(key_pins[1])){
			value='5';
			break;
		}
		////input char 6
		set_port("110",key_pins);
		if (set_pin(key_pins[1])){
			value='6';
			break;
		}
		////input char 7
		set_port("011",key_pins);
		if (set_pin(key_pins[2])){
			value='7';
			break;
		}
		////input char 8
		set_port("101",key_pins);
		if (set_pin(key_pins[2])){
			value='8';
			break;
		}
		////input char 9
		set_port("110",key_pins);
		if (set_pin(key_pins[2])){
			value='9';
			break;
		}
		////input char *
		set_port("011",key_pins);
		if (set_pin(key_pins[3])){
			value='*';
			break;
		}
		////input char 0
		set_port("101",key_pins);
		if (set_pin(key_pins[3])){
			value='0';
			break;
		}
		////input char #
		set_port("110",key_pins);
		if (set_pin(key_pins[3])){
			value='#';
			break;
		}
	}
	return value;
}