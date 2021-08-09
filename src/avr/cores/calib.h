/*
 * calib.h
 *
 * Created: 01-Jun-21 6:45:15 PM
 *  Author: K.C.S. Abeywickrama
 */ 


#ifndef CALIB_H_
#define CALIB_H_

void calib_init();
void calib_start();
void calib_run();
void calib_calc(uint16_t *reading,uint8_t *rgb);
void get_color();

#endif /* CALIB_H_ */