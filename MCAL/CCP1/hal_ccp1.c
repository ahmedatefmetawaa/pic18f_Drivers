
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
#include"hal_ccp.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
static void (*CCP1_INTERRUPT_HANDLER)(void) = NULL;
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
static void (*CCP2_INTERRUPT_HANDLER)(void) = NULL;
#endif
 static void ccp_capture_mode_select(const ccp1_t *ccp1);

Std_ReturnType CCP_INIT (const ccp1_t *ccp1 )
{
  Std_ReturnType ret = E_OK;
    if(NULL == ccp1){
        ret = E_NOT_OK;
    }
    else{
    /*Disable ccp Module*/ 
    if(ccp1_inst == ccp1->ccp_inst){
          ccp1_set_mode(ccp1_module_disable);
       }
       else if(ccp2_inst == ccp1->ccp_inst){
          ccp2_set_mode(ccp1_module_disable);
       }
       else{/*Nothing*/}    
    /*configure capture mode */    
     if(ccp1_capture_mode == ccp1->ccp1_mode) 
     {
      switch(ccp1->ccp1_variantModes_select){
          case ccp1_captureMode_1_fallingEdge : ccp1_set_mode(ccp1_captureMode_1_fallingEdge);break;
          case ccp1_captureMode_1_risingEdge :  ccp1_set_mode(ccp1_captureMode_1_risingEdge);break;
          case ccp1_captureMode_4_risingEdge :  ccp1_set_mode(ccp1_captureMode_4_risingEdge);break;
          case ccp1_captureMode_16_risingEdge : ccp1_set_mode(ccp1_captureMode_16_risingEdge);break;
          default: ret = E_NOT_OK;
      } 
      ccp_capture_mode_select(ccp1);
     }
#if CCP1_CFG_MODE_SELECTED == CCP1_CFG_COMPARE_MODE_SELECTED    
     /*configure compare mode */
     else if(ccp1_compare_mode == ccp1->ccp1_mode )
     {
        switch(ccp1->ccp1_variantModes_select){
          case ccp1_compareMode_set_pin_low :        ccp1_set_mode(ccp1_compareMode_set_pin_low);break;
          case ccp1_compareMode_set_pin_high :       ccp1_set_mode(ccp1_compareMode_set_pin_high);break;
          case ccp1_compareMode_toggle_on_match :    ccp1_set_mode(ccp1_compareMode_toggle_on_match);break;
          case ccp1_compareMode_gen_sw_interrupt :   ccp1_set_mode(ccp1_compareMode_gen_sw_interrupt);break;
          case ccp1_compareMode_gen_event :          ccp1_set_mode(ccp1_compareMode_gen_event);break;
          default: ret = E_NOK;
      }  
     }
#endif    
     /*configure PWM mode */
     
#if (CCP1_CFG_MODE_SELECTED == CCP1_CFG_PWM_MODE_SELECTED)
    else if (ccp1_pwm_mode == ccp1->ccp1_mode ){
         if(ccp1_inst == ccp1->ccp_inst){
            if(ccp1_PWM_Mode == ccp1->ccp1_variantModes_select){ 
                ccp1_set_mode(ccp1_PWM_Mode);
            }
            else{/*Nothing*/}   
         }
            
        else if(ccp2_inst == ccp1->ccp_inst){
                if(ccp1_PWM_Mode == ccp1->ccp1_variantModes_select){ 
                ccp2_set_mode(ccp1_PWM_Mode);
            }
                else{/*Nothing*/}         
       }
       else{/*Nothing*/}
        PR2 = (uint8)((_XTAL_FREQ /(ccp1->PWM_Frequency * 4.0 * ccp1->timer2_prescaler_values 
                      * ccp1->timer2_postscaler_values))-1);
           
       }
    else {/*Nothing*/}
#endif       
     }
     
     /* configure I/O pin  */
     ret = gpio_pin_intialize(&(ccp1->ccp_pin));
     /* configure interrupt feature */
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    
    ccp1_INTERRUPT_ENABLE();
    ccp1_INTERRUPT_FLAG_CLEAR();
    CCP1_INTERRUPT_HANDLER = ccp1->CCP1_InterruptHandler;
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
    
    INTERRUPT_PRIORITY_ENABLE();
    if(INTERRUPT_HIGH_PRIORITY == ccp1->priority)
    {
     ccp1_HIGH_PRIORITY_SET();
     INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY == ccp1->priority)
    {
     ccp1_LOW_PRIORITY_SET();
     NTERRUPT_GIlobalInterruptLowEnable();
    }
    else{/*Nothing*/}
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_InterruptPeripheralsEnable();
#endif
    
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    
    ccp2_INTERRUPT_ENABLE();
    ccp2_INTERRUPT_FLAG_CLEAR();
    CCP2_INTERRUPT_HANDLER = ccp1->CCP2_InterruptHandler;
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
    
    INTERRUPT_PRIORITY_ENABLE();
    if(INTERRUPT_HIGH_PRIORITY == ccp1->ccp2_priority)
    {
     ccp2_HIGH_PRIORITY_SET();
     INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY == ccp1->ccp2_priority)
    {
     ccp2_LOW_PRIORITY_SET();
     NTERRUPT_GIlobalInterruptLowEnable();
    }
    else{/*Nothing*/}
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_InterruptPeripheralsEnable();
#endif
    
#endif
     
    
  return ret;
}

Std_ReturnType CCP_DEINIT (const ccp1_t *ccp1 )
{
    Std_ReturnType ret = E_OK;
    if(NULL == ccp1){
        ret = E_NOT_OK;
    }
    else{
        
        if(ccp1_inst == ccp1->ccp_inst){
          ccp1_set_mode(ccp1_module_disable);
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    ccp1_INTERRUPT_DISABLE();
#endif 
       }
       else if(ccp2_inst == ccp1->ccp_inst){
          ccp2_set_mode(ccp1_module_disable);
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    ccp2_INTERRUPT_ENABLE();
#endif           
       }
       else{/*Nothing*/}
    }  
  return ret;  
}        
#if CCP1_CFG_MODE_SELECTED == CCP1_CFG_CAPTURE_MODE_SELECTED

   Std_ReturnType ccp1_IsCaptureReady (uint8 *capture_status)
{
    Std_ReturnType ret = E_OK;
    if(NULL == capture_status){
        ret = E_NOT_OK;
    }
    else{
     if(ccp1_capture_ready == PIR1bits.CCP1IF){
       *capture_status = ccp1_capture_ready ;
       ccp1_INTERRUPT_FLAG_CLEAR();
    }
       else{
       *capture_status = ccp1_capture_not_ready;  
     } 
    }  
  return ret;
}
 
   Std_ReturnType ccp1_Capture_Mode_Read_Value (uint16 *capture_value)
{
    ccp1_reg_t ccp1_temp_reg = {.ccpr1_low =0 , .ccpr1_high =0};   
    Std_ReturnType ret = E_OK;
    if(NULL == capture_value){
        ret = E_NOT_OK;
    }
    else{
     ccp1_temp_reg.ccpr1_low = CCPR1L;
     ccp1_temp_reg.ccpr1_high =CCPR1H;
     *capture_value = ccp1_temp_reg.ccpr1_16bit;
    }  
  return ret;  
}        
#endif  
    
#if CCP1_CFG_MODE_SELECTED == CCP1_CFG_COMPARE_MODE_SELECTED
   STD_ReturnType ccp1_IsCompareReady (uint8 *compare_status)
{
    STD_ReturnType ret = E_OK;
    if(NULL == compare_status){
        ret = E_NOK;
    }
    else{
       if(ccp1_capture_ready == PIR1bits.CCP1IF){
       *compare_status = ccp1_compare_ready ;
       ccp1_INTERRUPT_FLAG_CLEAR();
     }
       else{
       *compare_status = ccp1_compare_not_ready;  
     }    
    }  
  return ret;   
} 
   
   STD_ReturnType ccp1_Compare_Mode_Set_Value (uint16 *compare_value)
{
    ccp1_reg_t ccp1_temp_reg = {.ccpr1_low =0 , .ccpr1_high =0};
    STD_ReturnType ret = E_OK;
    if(NULL == compare_value){
        ret = E_NOK;
    }
    else{
     ccp1_temp_reg.ccpr1_16bit =  *compare_value;
     CCPR1L = ccp1_temp_reg.ccpr1_low;
     CCPR1H = ccp1_temp_reg.ccpr1_high;
    }  
  return ret;     
}         
#endif     

#if CCP1_CFG_MODE_SELECTED == CCP1_CFG_PWM_MODE_SELECTED
   
   STD_ReturnType ccp_PWM_set_duty(const ccp1_t *ccp1 , const uint8 duty)
{
    STD_ReturnType ret = E_OK;
    uint16 l_duty_temp=0;
    if(NULL == ccp1){
        ret = E_NOK;
    }
    else{
        l_duty_temp = (uint16)(4 * (PR2 + 1) * (duty / 100.0));
       if(ccp1_inst == ccp1->ccp_inst){
           CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
           CCPR1L = (uint8)(l_duty_temp >>2);  
       }
       else if(ccp2_inst == ccp1->ccp_inst){
           CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
           CCPR2L = (uint8)(l_duty_temp >>2);
       }
       else{/*Nothing*/}
    }
       
   return ret;
} 
   
   STD_ReturnType ccp_PWM_start(const ccp1_t *ccp1)
{
    STD_ReturnType ret = E_OK;
    if(NULL == ccp1){
        ret = E_NOK;
    }
    else{
       if(ccp1_inst == ccp1->ccp_inst){
           CCP1CONbits.CCP1M = ccp1_PWM_Mode;
       }
       else if(ccp2_inst == ccp1->ccp_inst){
           CCP2CONbits.CCP2M = ccp1_PWM_Mode;
       }
       else{/*Nothing*/}
    }
  
    return ret;     
}  
   
   STD_ReturnType ccp_PWM_stop(const ccp1_t *ccp1)
{
    STD_ReturnType ret = E_OK;
    if(NULL == ccp1){
        ret = E_NOK;
    }
    else{
       if(ccp1_inst == ccp1->ccp_inst){
          CCP1CONbits.CCP1M = ccp1_module_disable;
       }
       else if(ccp2_inst == ccp1->ccp_inst){
          CCP2CONbits.CCP2M = ccp1_module_disable;
       }
       else{/*Nothing*/}
    }
  
    return ret;      
    
       
}        
#endif
   
 void ccp1_ISR(void){
    ccp1_INTERRUPT_FLAG_CLEAR();
    if(CCP1_INTERRUPT_HANDLER){CCP1_INTERRUPT_HANDLER();}
 }
 
  void ccp2_ISR(void){
    ccp2_INTERRUPT_FLAG_CLEAR();
    if(CCP2_INTERRUPT_HANDLER){CCP2_INTERRUPT_HANDLER();}
 }

  static void ccp_capture_mode_select(const ccp1_t *ccp1)
  {
      if(ccp1_ccp2_timer3 == ccp1->capture_type){
       T3CONbits.T3CCP1 = 0;
       T3CONbits.T3CCP2 = 1;        
      }
      else if(ccp1_timer1_ccp2_timer3 == ccp1->capture_type){
       T3CONbits.T3CCP1 =1;
       T3CONbits.T3CCP2 =0;        
      }
      else if (ccp1_ccp2_timer1 == ccp1->capture_type){
       T3CONbits.T3CCP1 = 0;
       T3CONbits.T3CCP2 = 0;
      }
  }