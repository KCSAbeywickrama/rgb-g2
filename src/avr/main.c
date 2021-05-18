/*
 * avr.c
 *
 * Created: 07-May-21 5:12:49 PM
 * Author : CSA
 */ 


#define F_CPU 8000000UL

#include <avr/io.h>
#include "cores/keypad.h"
#include <util/delay.h>

#define r0 2
#define r1 3
#define r2 4
#define r3 5
#define c0 6
#define c1 11
#define c2 12


//char keys[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};	
//int rowPins[rows]={r0,r1,r2,r3};
//int columnPins[columns]={c0,c1,c2};
//Keypad inputKeypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);

int main(void)
{
	DDRB=255;
	DDRC=255;
	int keypadPins[7]={r0,r1,r2,r3,c0,c1,c2};
	set_keypad(keypadPins);
	while (1)
	{	
		//get the keypad inputs
		char val=keypad_getKey();
		led_light(val);		
		
	}
}

