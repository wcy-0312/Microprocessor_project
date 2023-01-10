#include <xc.h>

void TMR1_Initialize()
{
    T1CON = 0b10001001;
    TMR1H = 0x0b;
    TMR1L = 0xdb;
    
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    IPR1bits.TMR1IP = 1;
}