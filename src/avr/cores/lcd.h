/*
 * lcd.h
 *
 * Created: 5/19/2021 12:49:10 AM
 *  Author: Yohan Abeysinghe 1
 */ 


#ifndef LCD_H_
#define LCD_H_

void LCD_Char( unsigned char data );
void LCD_Init (void);
void LCD_String (char *str);
void LCD_Clear();

#endif /* LCD_H_ */