/* 
 * File:   Mcal_interrupt_manager.c
 * Author: Ahmed Atef
 *
 * Created on January 1, 2023, 3:26 PM
 */
#include "mcal_interrupt_manager.h"

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

void __interrupt()InterruptManagerHigh (void)
{
     if( (INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR ==INTCONbits.INT0IF ) ){
         INT0_ISR();
    }
     else{/*nothing*/}
        if( (INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR ==INTCON3bits.INT2IF ) ){
         INT2_ISR();
    }
    else{/*nothing*/}
}

void __interrupt(low_priority)InterruptManagerLow (void)
{
        if( (INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR ==INTCON3bits.INT1IF ) ){
         INT1_ISR();
    }
    else{/*nothing*/}
}

#else 
void __interrupt()InterruptManager(void)
{
    if( (INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR ==INTCONbits.INT0IF ) ){
         INT0_ISR();
    }
    else{/*nothing*/}

    if( (INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR ==INTCON3bits.INT1IF ) ){
         INT1_ISR();
    }
    else{/*nothing*/}
    if( (INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR ==INTCON3bits.INT2IF ) ){
         INT2_ISR();
    }
    else{/*nothing*/}
    if( (INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF ) ){
         ADC_ISR();
    }
    else{/*nothing*/}
 
    

}

#endif