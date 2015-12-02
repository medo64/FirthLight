#include "io.h"


void io_init(void) {
    LATA   = 0;
    LATB   = 0;
    LATC   = 0;
    TRISA  = 0;
    TRISB  = 0b00010000;
    TRISC  = 0;
    ANSELA = 0b00100000; //A5 is analog input (AN20)
    ANSELB = 0;
    ANSELC = 0;

    ADCOMCONbits.ADFM = 1; //left justified
    ADCOMCONbits.ADCS = 0b111; //Frc
    AD2CON0bits.CHS = 20; //AN20
    AAD2CHbits.CH20 = 1; //AN20 is connected to ADC2
}


uint8_t dataC; bit dataB6, dataB7;

void io_led_off(void) {
    LATC = 0;
    LATB6 = 0;
    LATB7 = 0;
}

void io_led_on(void) {
    LATC = 0b11111111;
    LATB6 = 1;
    LATB7 = 1;
}

void io_led_custom(uint8_t data, bool statusTop, bool statusBottom) {
    LATC = data;
    LATB6 = statusTop;
    LATB7 = statusBottom;
}

void io_led_swipe(void) {
    for(uint8_t i=0; i<3; i++) {
        clrwdt();
        io_led_custom(0b10000001, false, false);
        wait_50ms();
        io_led_custom(0b01000010, false, false);
        wait_50ms();
        io_led_custom(0b00100100, false, false);
        wait_50ms();
        io_led_custom(0b00011000, false, false);
        wait_50ms();
        io_led_custom(0b00000000, true, true);
        wait_50ms();
    }
    io_led_off();
    clrwdt();
}

void io_led_data_show(uint8_t data) {
    LATC = data;
}


void io_led_status_off(void) {
    LATB6 = 0;
    LATB7 = 0;
}

void io_led_status_show(bool statusTop, bool statusBottom) {
    LATB6 = statusTop;
    LATB7 = statusBottom;
}

bit last_led_swap_state = 0;

void io_led_status_swap(void) {
    LATB6 = !last_led_swap_state;
    LATB7 = last_led_swap_state;
    last_led_swap_state = !last_led_swap_state;
}


uint8_t io_sensor_luminosity_value(void) {
    PIR1bits.ADIF = 0; //clear interrupt flag
    AD2CON0bits.ADON = 1; //Turn on ADC

    AD2CON0bits.GO  = 1;
    while (AD2CON0bits.GO_nDONE) { nop(); } //Wait for A/D convert complete

    AD2CON0bits.ADON = 0; //Turn off ADC

    uint16_t value;
    if (AADSTATbits.AD2CONV) {
        value = AD2RES1;
    } else {
        value = AD2RES0;
    }
    if (value > 0xFF) {
        return 0xFF;
    } else {
        return (uint8_t)(value >> 2);
    }
}
