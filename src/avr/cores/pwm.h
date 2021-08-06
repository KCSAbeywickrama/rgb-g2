/*
 * pwm.h
 *
 * Created: 15-Jun-21 6:37:03 PM
 *  Author: K. C. S. Abeywickrama
 */ 


#ifndef PWM_H_
#define PWM_H_

void pwm_init();
void pwm_start();
void pwm_stop();
void pwm_check();
void pwm_set(uint8_t *rgb);
void pwm_set_args(uint8_t red,uint8_t green,uint8_t blue);

#endif /* PWM_H_ */