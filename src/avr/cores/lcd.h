/*
 * lcd.h
 *
 * Created: 5/19/2021 12:49:10 AM
 *  Author: Yohan Abeysinghe 1
 */ 


#ifndef LCD_H_
#define LCD_H_

void lcd_char( unsigned char data );
void lcd_init(void);
void lcd_int(uint8_t i);
void lcd_int_array(uint8_t *arr);
void lcd_string(char *str);
void lcd_clear();

#endif /* LCD_H_ */