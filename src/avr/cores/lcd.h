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
void lcd_setcursor(int row_index,int col_index);
void lcd_clear_line(int row);
void lcd_int(uint8_t value);
void lcd_delete();
void lcd_string_blink(char *word,int iter,int row,int column);

#endif /* LCD_H_ */