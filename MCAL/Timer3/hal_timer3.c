
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#include "hal_timer3.h"

#if timer3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
static void (*TMR3_INTERRUPT_HANDLER)(void) = NULL;
#endif

static inline void timer3_mode_select(const timer3_t *timer);

static uint16 timer3_preload =0;

Std_ReturnType Timer3_Init(const timer3_t *timer )
{
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
    /*disable the timer1*/
    timer3_module_disable();
    /*congigure the prescaler value*/
    TIMER3_PRESCALER_select(timer->timer3_prescaler_values);
    /*configure the timer1 mode of operation*/
    timer3_mode_select(timer);
    /*configure the initialize preload value*/
    TMR3H = (timer->timer3_preload_value)>>8;
    TMR3L = (uint8)(timer->timer3_preload_value);
    timer3_preload = timer->timer3_preload_value;
    /*configure the interrupt*/
#if timer3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    
    timer3_INTERRUPT_ENABLE();
    timer3_INTERRUPT_FLAG_CLEAR();
    TMR3_INTERRUPT_HANDLER = timer->TMR3_InterruptHandler;
    
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_ENABLE();
    if(INTERRUPT_HIGH_PRIORITY == timer->priority)
    {
     timer3_HIGH_PRIORITY_SET();
     INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY == timer->priority)
    {
     timer3_LOW_PRIORITY_SET();
     NTERRUPT_GIlobalInterruptLowEnable();
    }
    else{/*Nothing*/}
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_InterruptPeripheralsEnable();
#endif
        
#endif

        /*enable the timer1*/
        timer3_module_enable();
    }
    return ret;
}

Std_ReturnType Timer3_Deinit(const timer3_t *timer )
{
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
    timer3_module_disable();
#if timer3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    timer3_INTERRUPT_DISABLE();
#endif 
    }
    return ret;
}  

Std_ReturnType Timer3_Write_Value (const timer3_t *timer , uint16 value)
{
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
    TMR3H = (value)>>8;
    TMR3L = (uint8)(value);    
    }
    return ret;
}

Std_ReturnType Timer3_Read_Value (const timer3_t *timer , uint16 *value)
{
    uint8 l_tmr3H  , l_tmr3L =0;   
    Std_ReturnType ret = E_OK;
    if((NULL == timer) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
    l_tmr3L = TMR3L;
    l_tmr3H = TMR3H ;
    *value = (uint16)((l_tmr3H<<8)+l_tmr3L);
    }

return ret;
}

 void TMR3_ISR(void){
    timer3_INTERRUPT_FLAG_CLEAR();
    TMR3H = (timer3_preload)>>8;
    TMR3L = (uint8)(timer3_preload);
    if(TMR3_INTERRUPT_HANDLER){TMR3_INTERRUPT_HANDLER();}
 }

static inline void timer3_mode_select(const timer3_t *timer)
 {
    if (timer3_timer_mode_cfg == timer->timer3_mode)
    {
        timer3_timer_mode_enable();
    }
    else if(timer3_counter_mode_cfg == timer->timer3_mode)
    {
       timer3_counter_mode_enable();
       
    if(timer3_asyncronus_counter_mode == timer->timer3_counter_mode)
       {
           timer3_async_counter_mode();
       }
    else if (timer3_syncronus_counter_mode == timer->timer3_counter_mode)
       {
           timer3_sync_counter_mode();
       }
    else {/*Nothing*/}
    }
    else {/*Nothing*/}
 }