/*
* lcd.h
*
* Created: 5/19/2021 12:49:10 AM
*  Author: Yohan Abeysinghe 1
*/


#ifndef LCD_H_
#define LCD_H_

//unsigned char ch_correction[8] = { 0x00, 0x00,	0x01, 0x13,	0x16, 0x1C,	0x18, 0x10 };
//unsigned char ch_for[8] = { 0x00, 0x04, 0x02, 0x1F,	0x1F, 0x02,	0x04, 0x00 };
//unsigned char ch_back[8] = { 0x00, 0x04, 0x08, 0x1F, 0x1F, 0x08, 0x04, 0x00 };
//unsigned char ch_bulbon[8] = { 0x0E, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x04, 0x1F };
//unsigned char ch_bulboff[8] = { 0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x1F };

void lcd_command( unsigned char cmnd );
void lcd_char( unsigned char data );
void lcd_init (void);
void lcd_string (char *str);
void lcd_clear();
void lcd_custom_char(unsigned char loc, unsigned char *msg);
void lcd_set_cursor(int row_index,int col_index);
void lcd_clear_line(int row);
void lcd_int(int value);
void lcd_float(float value);
void lcd_delete();
void lcd_string_blink(char *word,int iter,int row,int column);
void lcd_uint8_arr(uint8_t *values);
void lcd_uint16_arr(uint16_t *values);
void lcd_check();

#endif /* LCD_H_ */