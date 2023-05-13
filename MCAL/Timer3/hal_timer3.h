

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H
/*section : includes */
#include "pic18f4620.h"
#include "../MCAL_std_types.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
/*section : macro declerations*/
#define timer3_counter_mode_cfg                 1
#define timer3_timer_mode_cfg                   0
#define timer3_asyncronus_counter_mode          1
#define timer3_syncronus_counter_mode           0
#define timer3_8bit_register_mode_cfg           0
#define timer3_16bit_register_mode_cfg          1

#define TIMER3_PRESCALER_DIV_BY_1               0
#define TIMER3_PRESCALER_DIV_BY_2               1
#define TIMER3_PRESCALER_DIV_BY_4               2
#define TIMER3_PRESCALER_DIV_BY_8               3

/*section : macro functions declerations */
#define timer3_module_enable()                  (T3CONbits.TMR3ON=1)
#define timer3_module_disable()                 (T3CONbits.TMR3ON=0)

#define timer3_timer_mode_enable()              (T3CONbits.TMR3CS=0)
#define timer3_counter_mode_enable()            (T3CONbits.TMR3CS=1)

#define timer3_async_counter_mode()             (T3CONbits.T3SYNC=1)
#define timer3_sync_counter_mode()              (T3CONbits.T3SYNC=0)

#define TIMER3_PRESCALER_select(_prescaler)     (T3CONbits.T3CKPS = _prescaler)

#define timer3_8bit_register_mode               (T3CONbits.RD16=0)
#define timer3_16bit_register_mode              (T3CONbits.RD16=1)

/*section : data types declerations*/
typedef struct{
#if timer3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
  void(*TMR3_InterruptHandler)(void);
  INTERRUPT_PERIORITY_T priority;
#endif 
  uint16 timer3_preload_value;
  uint8 timer3_prescaler_values       :2;
  uint8 timer3_mode                   :1;
  uint8 timer3_counter_mode           :1;
  uint8 timer3_reg_rw_mode            :1;
  uint8 timer3_reserved               :3;   
}timer3_t;

/*section : functions declerations*/
Std_ReturnType Timer3_Init(const timer3_t *timer );
Std_ReturnType Timer3_Deinit(const timer3_t *timer );
Std_ReturnType Timer3_Write_Value (const timer3_t *timer , uint16 value);
Std_ReturnType Timer3_Read_Value (const timer3_t *timer , uint16 *value);
#endif	/* HAL_TIMER3_H */

