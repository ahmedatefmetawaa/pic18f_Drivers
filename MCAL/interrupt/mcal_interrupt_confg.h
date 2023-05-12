
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

  
#ifndef MCAL_INTERRUPT_CONFG_H
#define	MCAL_INTERRUPT_CONFG_H

/*section : includes */
#include "pic18f4620.h"
#include "../MCAL_std_types.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
#include"mcal_interrupt_gen_cfg.h"
#define _XTAL_FREQ 8000000
#include <xc.h>

/*section : macro declerations*/
#define INTERRUPT_ENABLE            1 
#define INTERRUPT_DISABLE           0
#define INTERRUPT_OCCUR             1
#define INTERRUPT_NOT_OCCUR         0
#define INTERRUPT_PRIORITY_ENABLE   1
#define INTERRUPT_PRIORITY_DISABLE  0
/*section : macro functions declerations */
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define INTERRUPT_PRIORITY_ENABLE()                    (RCONbits.IPEN = 1)
#define INTERRUPT_PRIORITY_DISABLE()                   (RCONbits.IPEN = 0)
#define INTERRUPT_GlobalInterruptHighEnable()          (INTCONbits.GIEH = 1)
#define INTERRUPT_GlobalInterruptHighDisable()         (INTCONbits.GIEH = 0)
#define NTERRUPT_GIlobalInterruptLowEnable()           (INTCONbits.GIEL = 1)
#define INTERRUPT_GlobalInterruptLowDisable()          (INTCONbits.GIEL = 0)


#else
#define INTERRUPT_GlobalInterruptEnable()              (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalInterruptDisable()             (INTCONbits.GIE = 0)
#define INTERRUPT_InterruptPeripheralsEnable()         (INTCONbits.PEIE = 1)
#define INTERRUPT_InterruptPeripheralsDisable()        (INTCONbits.PEIE = 0)

#endif
/*section : data types declerations*/
typedef enum {
    INTERRUPT_LOW_PRIORITY=0,
    INTERRUPT_HIGH_PRIORITY      
}INTERRUPT_PERIORITY_T;

/*section : functions declerations*/

#endif	/* MCAL_INTERRUPT_CONFG_H */

