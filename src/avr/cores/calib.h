/*
 * calib.h
 *
 * Created: 01-Jun-21 6:45:15 PM
 *  Author: K.C.S. Abeywickrama
 */ 


#ifndef CALIB_H_
#define CALIB_H_

void calib_start();
void calib_calc(uint16_t *reading,uint8_t *rgb);

#endif /* CALIB_H_ */