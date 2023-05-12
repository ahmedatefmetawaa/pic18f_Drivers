
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

 
#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

#define INTERRUPT_FEATURE_ENABLE                                1 
//#define INTERRUPT_priority_level_enable                  INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_INTX_FEATURE_ENABLE           INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_ONCHANGE_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_FEATURE_ENABLE                     INTERRUPT_FEATURE_ENABLE   
#define timer0_INTERRUPT_FEATURE_ENABLE                  INTERRUPT_FEATURE_ENABLE
#define timer1_INTERRUPT_FEATURE_ENABLE                  INTERRUPT_FEATURE_ENABLE
#define timer2_INTERRUPT_FEATURE_ENABLE                  INTERRUPT_FEATURE_ENABLE
#define timer3_INTERRUPT_FEATURE_ENABLE                  INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_FEATURE_ENABLE                    INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENABLE                    INTERRUPT_FEATURE_ENABLE
#define EUSART_TX_INTERRUPT_FEATURE_ENABLE               INTERRUPT_FEATURE_ENABLE
#define EUSART_RX_INTERRUPT_FEATURE_ENABLE               INTERRUPT_FEATURE_ENABLE
//#define MSSP_I2C_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#endif	/* MCAL_INTERRUPT_GEN_CFG_H */
