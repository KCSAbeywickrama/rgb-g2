/*
 * lcd.h
 *
 * Created: 5/19/2021 12:49:10 AM
 *  Author: Yohan Abeysinghe 1
 */ 


#ifndef LCD_H_
#define LCD_H_

void lcd_command( unsigned char cmnd );
void lcd_char( unsigned char data );
void lcd_init (void);
void lcd_string (char *str);
void lcd_clear();
void LCD_SetCursor(int row_index,int col_index);

#endif /* LCD_H_ */