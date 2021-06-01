/*
 * sensor.h
 *
 * Created: 19/05/2021 03:19:23
 *  Author: Lakdilu
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_

void pin_mode(uint8_t *_port, uint8_t _bit, uint8_t _mode);
void digital_write(uint8_t *port, uint8_t bite, uint8_t state);
uint16_t sensor_read (uint8_t _pin);
void sensor_init();
int calib(uint8_t val, uint8_t clr);
int limit (uint8_t _val, uint8_t _max, uint8_t _min);


#endif /* SENSOR_H_ */