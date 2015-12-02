#include "system.h"


// CONFIG1
#pragma config FOSC     = INTOSC
#pragma config WDTE     = ON
#pragma config PWRTE    = OFF
#pragma config MCLRE    = ON
#pragma config CP       = OFF
#pragma config BOREN    = ON
#pragma config CLKOUTEN = OFF

// CONFIG2
#pragma config WRT      = ALL
#pragma config STVREN   = ON
#pragma config BORV     = LO
#pragma config LPBOR    = OFF
#pragma config LVP      = OFF


void init(void) {
    GIE = 0; //disable interrupts

    //Oscillator
    OSCCON  = 0b00000010; //PLL disabled, 31 KHz, Internal oscillator
    OSCSTAT = 0x00;
    while (!OSCSTATbits.LFIOFR) { nop(); }

    //Watchdog
    WDTCONbits.WDTPS = 0b01010; //1s
    clrwdt();

    //ADC
    ADCON1bits.ADFM = 1;      //Right-justified
    ADCON1bits.ADCS = 0b011;  //Frc (clock derived from A/D RC oscillator)
    ADCON1bits.ADPREF = 0b00; //Vdd
}
