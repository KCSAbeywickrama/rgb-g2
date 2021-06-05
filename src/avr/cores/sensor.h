/*
 * sensor.h
 *
 * Created: 19/05/2021 03:19:23
 *  Author: Lakdilu
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_

void sensor_init();
void sensor_read(uint16_t *reading);
uint16_t _adc_read (uint8_t pin);

#endif /* SENSOR_H_ */