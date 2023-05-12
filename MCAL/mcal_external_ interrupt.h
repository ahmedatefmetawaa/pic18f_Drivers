
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */


#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H
/*section : includes */
#include "mcal_interrupt_confg.h"
/*section : macro declerations*/

/*section : macro functions declerations */
#if EXTERNAL_INTERRUPT_INTX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXT_INT0_INTERRUPT_ENABLE()             (INTCONbits.INT0IE = 1)
#define EXT_INT0_INTERRUPT_DISABLE()            (INTCONbits.INT0IE = 0)
#define EXT_INT0_INTERRUPT_FLAG_CLEAR()         (INTCONbits.INT0IF =0)
#define EXT_INT0_INTERRUPT_RISINGEDGE()         (INTCON2bits.INTEDG0 = 1)
#define EXT_INT0_INTERRUPT_FALLINGEDGE()        (INTCON2bits.INTEDG0 = 0)

#define EXT_INT1_INTERRUPT_ENABLE()             (INTCON3bits.INT1E = 1)
#define EXT_INT1_INTERRUPT_DISABLE()            (INTCON3bits.INT1E = 0)
#define EXT_INT1_INTERRUPT_FLAG_CLEAR()         (INTCON3bits.INT1IF =0)
#define EXT_INT1_INTERRUPT_RISINGEDGE()         (INTCON2bits.INTEDG1 = 1)
#define EXT_INT1_INTERRUPT_FALLINGEDGE()        (INTCON2bits.INTEDG1 = 0)

#define EXT_INT2_INTERRUPT_ENABLE()             (INTCON3bits.INT2IE = 1)
#define EXT_INT2_INTERRUPT_DISABLE()            (INTCON3bits.INT2IE = 0)
#define EXT_INT2_INTERRUPT_FLAG_CLEAR()         (INTCON3bits.INT2IF =0)
#define EXT_INT2_INTERRUPT_RISINGEDGE()         (INTCON2bits.INTEDG2 = 1)
#define EXT_INT2_INTERRUPT_FALLINGEDGE()        (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
// EXT_INT1 alwayse high priority
#define EXT_INT1_HIGH_PRIORITY_SET()            (INTCON3bits.INT1IP = 1 )
#define EXT_INT1_LOW_PRIORITY_SET()             (INTCON3bits.INT1IP = 0)
#define EXT_INT2_HIGH_PRIORITY_SET()            (INTCON3bits.INT2IP = 1)      
#define EXT_INT2_LOW_PRIORITY_SET()             (INTCON3bits.INT2IP = 0)
#endif 

#endif

#if  EXTERNAL_INTERRUPT_ONCHANGE_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXT_RBX_INTERRUPT_ENABLE()              (INTCONbits.RBIE = 1)
#define EXT_RBX_INTERRUPT_DISABLE()             (INTCONbits.RBIE = 0)
#define EXT_RBX_INTERRUPT_FLAG_CLEAR()          (INTCONbits.RBIF = 0)

#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#define  EXT_RBX_HIGH_PRIORITY()                (INTCON2bits.RBIP = 1)
#define  EXT_RBX_LOW_PRIORITY()                 (INTCON2bits.RBIP = 0)

#endif

#endif
/*section : data types declerations*/
typedef enum {
    FALLING_EDGE=0,
    RISING_EDGE        
}INTERRUPT_INTX_EDGE_T; 
typedef enum {
    INTERRUPT_INT0=0,
    INTERRUPT_INT1,
    INTERRUPT_INT2,
}INTERRUPT_INTX_src_T;

typedef struct {
    void (*EXT_Interrupt_Handler)(void);
    INTERRUPT_INTX_EDGE_T edge;
    INTERRUPT_PERIORITY_T priority;
    INTERRUPT_INTX_src_T sorce;
    pin_config_t mcu_pin;
}interrupt_INTX_t;

typedef struct {
    void (*EXT_Interrupt_Handler)(void);
    pin_config_t mcu_pin;
    INTERRUPT_PERIORITY_T priority;
}interrupt_RBX_t;

/*section : functions declerations*/
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTX_Init   (const interrupt_INTX_t *int_obj );
Std_ReturnType Interrupt_INTX_Deinit (const interrupt_INTX_t *int_obj );
Std_ReturnType Interrupt_RBX_Init    (const interrupt_RBX_t *RB_obj );
Std_ReturnType Interrupt_RBX_Deinit  (const interrupt_RBX_t *RB_obj );
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

