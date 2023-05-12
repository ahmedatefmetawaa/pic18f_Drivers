
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */


#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/*section : includes */
#include "mcal_interrupt_confg.h"
/*section : macro declerations*/

/*section : macro functions declerations */

/*section : data types declerations*/

/*section : functions declerations*/
void INT0_ISR (void);
void INT1_ISR (void);
void INT2_ISR (void);
void RB4_ISR  (void);
void ADC_ISR  (void);
void TMR0_ISR (void);
void TMR1_ISR (void);
void TMR2_ISR (void);
void TMR3_ISR (void);
void ccp1_ISR(void);
void ccp2_ISR(void);
void eusart_tx_ISR(void);
void eusart_rx_ISR(void);
void mssp_i2c_ISR (void);
void mssp_i2c_BC_ISR (void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

