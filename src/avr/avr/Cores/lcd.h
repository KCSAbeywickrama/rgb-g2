/*
 * lcd.h
 *
 * Created: 6/13/2021 8:10:02 PM
 *  Author: Yohan Abeysinghe 1
 */ 


#ifndef LCD_H_
#define LCD_H_

void LCD_Char( unsigned char data );
void LCD_Init (void);
void LCD_String (char *str);
void LCD_Clear();
void LCD_SetCursor(int row_index,int col_index);

#endif /* LCD_H_ */