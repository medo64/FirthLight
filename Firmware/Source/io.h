#ifndef IO_H
#define	IO_H

#include "system.h"


void io_init();

void io_led_off(void);
void io_led_on(void);
void io_led_custom(uint8_t data, bool statusTop, bool statusBottom);
void io_led_swipe(void);
void io_led_data_show(uint8_t data);
void io_led_status_off(void);
void io_led_status_show(bool statusTop, bool statusBottom);
void io_led_status_swap(void);

#define io_sensor_luminosity_on() { LATA4 = 1; }
#define io_sensor_luminosity_off() { LATA4 = 0; }

#define io_sensor_magnetic_on() { LATB5 = 1; }
#define io_sensor_magnetic_off() { LATB5 = 0; }
#define io_sensor_magnetic_status() !PORTBbits.RB4

uint8_t io_sensor_luminosity_value(void);

#endif
