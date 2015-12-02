#ifndef SYSTEM_H
#define	SYSTEM_H

#include <pic.h>

#include <stdbool.h>
#include <stdint.h>


#define _XTAL_FREQ  31000


void init(void);

#define clrwdt() { asm("CLRWDT"); }
#define nop() { asm("NOP"); }
#define sleep() { asm("SLEEP"); nop(); }

#define wait_10ms() { __delay_ms(10); }
#define wait_50ms() { __delay_ms(50); }
#define wait_250ms() { __delay_ms(250); }

#endif
