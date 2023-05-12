

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

 
#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/*section : includes */
#include "mcal_interrupt_confg.h"
/*section : macro declerations*/


/*section : macro functions declerations */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_ENABLE()                  (PIE1bits.ADIE = 1)
#define ADC_INTERRUPT_DISABLE()                 (PIE1bits.ADIE = 0)
#define ADC_INTERRUPT_FLAG_CLEAR()              (PIR1bits.ADIF = 0)

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define ADC_HIGH_PRIORITY_SET()            (IPR1bits.ADIP = 1)
#define ADC_LOW_PRIORITY_SET()             (IPR1bits.ADIP = 1)

#endif

#endif 

#if timer0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define timer0_INTERRUPT_ENABLE()                  (INTCONbits.TMR0IE = 1)
#define timer0_INTERRUPT_DISABLE()                 (INTCONbits.TMR0IE= 0)
#define timer0_INTERRUPT_FLAG_CLEAR()              (INTCONbits.TMR0IF=0)

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define timer0_HIGH_PRIORITY_SET()            (INTCON2bits.TMR0IP = 1)
#define timer0_LOW_PRIORITY_SET()             (INTCON2bits.TMR0IP = 0)

#endif

#endif 

#if timer1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define timer1_INTERRUPT_ENABLE()                  (PIE1bits.TMR1IE = 1)
#define timer1_INTERRUPT_DISABLE()                 (PIE1bits.TMR1IE= 0)
#define timer1_INTERRUPT_FLAG_CLEAR()              (PIR1bits.TMR1IF=0)

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define timer1_HIGH_PRIORITY_SET()            (IPR1bits.TMR1IP = 1)
#define timer1_LOW_PRIORITY_SET()             (IPR1bits.TMR1IP = 0)

#endif

#endif 

#if timer2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define timer2_INTERRUPT_ENABLE()                  (PIE1bits.TMR2IE = 1)
#define timer2_INTERRUPT_DISABLE()                 (PIE1bits.TMR2IE= 0)
#define timer2_INTERRUPT_FLAG_CLEAR()              (PIR1bits.TMR2IF=0)

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define timer2_HIGH_PRIORITY_SET()            (IPR1bits.TMR2IP = 1)
#define timer2_LOW_PRIORITY_SET()             (IPR1bits.TMR2IP = 0)

#endif

#endif 

#if timer3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define timer3_INTERRUPT_ENABLE()                  (PIE2bits.TMR3IE = 1)
#define timer3_INTERRUPT_DISABLE()                 (PIE2bits.TMR3IE= 0)
#define timer3_INTERRUPT_FLAG_CLEAR()              (PIR2bits.TMR3IF=0)

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define timer3_HIGH_PRIORITY_SET()            (IPR2bits.TMR3IP = 1)
#define timer3_LOW_PRIORITY_SET()             (IPR2bits.TMR3IP = 0)

#endif

#endif 

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define ccp1_INTERRUPT_ENABLE()                  (PIE1bits.CCP1IE = 1)
#define ccp1_INTERRUPT_DISABLE()                 (PIE1bits.CCP1IE = 0)
#define ccp1_INTERRUPT_FLAG_CLEAR()              (PIR1bits.CCP1IF=0)

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define ccp1_HIGH_PRIORITY_SET()                (IPR1bits.CCP1IP = 1)
#define ccp1_LOW_PRIORITY_SET()                 (IPR1bits.CCP1IP = 0)

#endif

#endif 

#if CCP2_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE

#define ccp2_INTERRUPT_ENABLE()                  (PIE2bits.CCP2IE = 1)
#define ccp2_INTERRUPT_DISABLE()                 (PIE2bits.CCP2IE = 0)
#define ccp2_INTERRUPT_FLAG_CLEAR()              (PIR2bits.CCP2IF=0)

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define ccp2_HIGH_PRIORITY_SET()                (IPR2bits.CCP2IP = 1)
#define ccp2_LOW_PRIORITY_SET()                 (IPR2bits.CCP2IP = 0)

#endif

#endif 

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE

#define EUSART_TX_INTERRUPT_ENABLE()                  (PIE1bits.TXIE = 1)
#define EUSART_TX_INTERRUPT_DISABLE()                 (PIE1bits.TXIE = 0)


#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define EUSART_TX_HIGH_PRIORITY_SET()                (IPR1bits.TXIP = 1)
#define EUSART_TX_LOW_PRIORITY_SET()                 (IPR1bits.TXIP = 0)

#endif

#endif 

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE

#define EUSART_RX_INTERRUPT_ENABLE()                  (PIE1bits.RCIE= 1)
#define EUSART_RX_INTERRUPT_DISABLE()                 (PIE1bits.RCIE = 0)


#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define EUSART_RX_HIGH_PRIORITY_SET()                (IPR1bits.RCIP = 1)
#define EUSART_RX_LOW_PRIORITY_SET()                 (IPR1bits.RCIP = 0)

#endif

#endif 
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_ENABLE()                 (PIE1bits.SSPIE = 1)
#define MSSP_I2C_BUS_COL_INTERRUPT_ENABLE()         (PIE2bits.BCLIE = 1)

#define MSSP_I2C_INTERRUPT_DISABLE()                 (PIE1bits.SSPIE = 0)
#define MSSP_I2C_BUS_COL_INTERRUPT_DISABLE()         (PIE2bits.BCLIE = 0)

#define MSSP_I2C_INTERRUPT_FLAG_CLEAR()              (PIR1bits.SSPIF=0)
#define MSSP_I2C_BUS_COL_INTERRUPT_FLAG_CLEAR()      (PIR2bits.BCLIF = 0)

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_HIGH_PRIORITY_SET()                (IPR1bits.SSPIP = 1)
#define MSSP_I2C_BUS_COL_HIGH_PRIORITY_SET()        (IPR2bits.BCLIP = 1)

#define MSSP_I2C_LOW_PRIORITY_SET()                 (IPR1bits.SSPIP = 0)
#define MSSP_I2C_BUS_COL_LOW_PRIORITY_SET()         (IPR2bits.BCLIP = 0)
#endif

#endif
/*section : data types declerations*/

/*section : functions declerations*/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */
