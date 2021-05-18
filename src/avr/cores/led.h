/*
 * led.h
 *
 * Created: 18-May-21 5:14:50 PM
 *  Author: CSA
 */ 


#ifndef LED_H_
#define LED_H_

void led_init();
void led_on(uint8_t *rgb);
void led_on(uint8_t red,uint8_t green,uint8_t blue);
void led_off();

#endif /* LED_H_ */