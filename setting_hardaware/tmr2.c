#include <xc.h>

void TMR2_Initialize() {
    // Timer2 -> On, prescaler -> 4
    T2CONbits.TMR2ON = 0b1;
    T2CONbits.T2CKPS = 0b01;
    
    // Set up PR2 to decide PWM period
    PR2 = 0x9b;
}