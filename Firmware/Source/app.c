//#define DEBUG
//#define DEBUG_TEST

#include "io.h"
#include "system.h"

const uint16_t LUMINOSITY_LOW_LIMIT = 0;
const uint16_t LUMINOSITY_HIGH_LIMIT = 2;
uint8_t light_duration_factor = 3;


bit wasLight = 0;
bit wasDark = 0;
bit isLight = 0;
bit isDark = 0;

void main(void) {
    init();
    io_init();

#ifdef DEBUG_TEST
    io_led_on();
    wait_250ms(); clrwdt();
    io_led_off();

    while(true) {
        sleep();
        io_led_off(); //not to affect sensor

        io_sensor_luminosity_on();
        io_led_data_show(io_sensor_luminosity_value());
        io_sensor_luminosity_off();

        io_sensor_magnetic_on();
        if (io_sensor_magnetic_status()) { io_led_status_show(true, true); } else { io_led_status_swap(); }
        io_sensor_magnetic_off();
    }
#endif

    io_led_swipe();
    
    while(true) {
        sleep();
        io_led_off();

        io_sensor_luminosity_on();
        uint8_t luminosity = io_sensor_luminosity_value();
        io_sensor_luminosity_off();

        isLight = (luminosity >= LUMINOSITY_HIGH_LIMIT);
        isDark = (luminosity <= LUMINOSITY_LOW_LIMIT);

#ifdef DEBUG
        io_led_status_show(isLight, wasLight);
#endif
        
        if (wasLight && isDark) {
            io_led_custom(0b00000001, false, false); wait_50ms();
            io_led_custom(0b00000011, false, false); wait_50ms();
            io_led_custom(0b00000111, false, false); wait_50ms();
            io_led_custom(0b00001111, false, false); wait_50ms();
            io_led_custom(0b00001111, false, true); wait_50ms();
            io_led_custom(0b10001111, false, true); wait_50ms();
            io_led_custom(0b11001111, false, true); wait_50ms();
            io_led_custom(0b11101111, false, true); wait_50ms();
            io_led_custom(0b11111111, false, true); wait_50ms();
            io_led_on();
            for (uint8_t i=0; i<light_duration_factor; i++) {
                for (uint8_t j=0; j<40; j++) { //10 seconds
                    clrwdt();
                    wait_250ms();
                }
            }
            io_led_custom(0b11111110, true, true); wait_50ms();
            io_led_custom(0b11111100, true, true); wait_50ms();
            io_led_custom(0b11111000, true, true); wait_50ms();
            io_led_custom(0b11110000, true, true); wait_50ms();
            io_led_custom(0b11110000, true, false); wait_50ms();
            io_led_custom(0b01110000, true, false); wait_50ms();
            io_led_custom(0b00110000, true, false); wait_50ms();
            io_led_custom(0b00010000, true, false); wait_50ms();
            io_led_custom(0b00000000, true, false); wait_50ms();
            io_led_off();
            clrwdt();
        }
        wasLight = isLight;
        wasDark = isDark;

        io_sensor_magnetic_on();
        if (io_sensor_magnetic_status()) {
            while (io_sensor_magnetic_status()) { //configuration
                io_led_status_show(1, 1);
                uint8_t currentDurationFactorDisplay = 0xFF;
                if (light_duration_factor < 8) { currentDurationFactorDisplay >>= (8-light_duration_factor);}
                io_led_data_show(currentDurationFactorDisplay);

                for (uint8_t i=0; i<8; i++) { clrwdt(); wait_250ms(); } //2 seconds
                if (io_sensor_magnetic_status()) { //if still pressed, increase duration
                    if (light_duration_factor < 8) { light_duration_factor++; } else { light_duration_factor = 1; }
                }

                io_led_off();
            }
            io_led_status_off();
        }
        io_sensor_magnetic_off();
    }
}
