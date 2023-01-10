#include <xc.h>

void CCP1_Initialize() {
    TRISCbits.TRISC2=0;	// RC2 pin is output.
    
    // PWM mode, P1A, P1C active-high; P1B, P1D active-high
    CCP1CONbits.CCP1M = 0b1100;
    
    // Set up CCP to decide Duty Cycle
    CCPR1L = 0x04;  // degree of motor
    CCP1CONbits.DC1B = 0b01;
    
    PIR1bits.CCP1IF=0;
    IPR1bits.CCP1IP = 1;
}
