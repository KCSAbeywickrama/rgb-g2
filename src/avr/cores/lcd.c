/*
 * lcd.c
 *
 * Created: 5/19/2021 12:49:00 AM
 *  Author: Yohan Abeysinghe 1
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define LCD_EN PORTD
#define RS PB0				/* Define Register Select pin */
#define EN PD7				/* Define Enable signal pin */



