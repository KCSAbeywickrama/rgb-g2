/*
 * led.h
 *
 * Created: 5/10/2021 11:13:43 PM
 *  Author: Dulanjana
 */ 

#include <avr/io.h>

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define BACK_KEY '*'
#define OK_KEY '#'

void keypad_init();
char keypad_get_key();
void keypad_check();

#endif /* KEYPAD_H_ */