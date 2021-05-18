/*
 * led.h
 *
 * Created: 5/10/2021 11:13:43 PM
 *  Author: Dulanjana
 */ 

#include <avr/io.h>

#ifndef KEYPAD_H_
#define KEYPAD_H_


char *key_pins[7];

//void led_on(uint8_t *port, uint8_t pin);
//void led_off(uint8_t *port, uint8_t pin);
char *pin_set(int pin);
int set_keypad(int *pin_num);
int set_port(char *bits,char **pins);
int set_pin(char *pin);
char getKey();

#endif /* KEYPAD_H_ */