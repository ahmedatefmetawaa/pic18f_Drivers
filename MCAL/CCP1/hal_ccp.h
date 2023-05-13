

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

  
#ifndef HAL_CCP1_H
#define	HAL_CCP1_H
/*section : includes*/
#include "pic18f4620.h"
#include "../MCAL_std_types.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
#include "hal_ccp1_cfg.h"
/*section : macro declerations*/
#define ccp1_module_disable                  ((uint8)0x00)
#define ccp1_captureMode_1_fallingEdge       ((uint8)0x04)
#define ccp1_captureMode_1_risingEdge        ((uint8)0x05)
#define ccp1_captureMode_4_risingEdge        ((uint8)0x06)
#define ccp1_captureMode_16_risingEdge       ((uint8)0x07)
#define ccp1_compareMode_set_pin_low         ((uint8)0x08)
#define ccp1_compareMode_set_pin_high        ((uint8)0x09)
#define ccp1_compareMode_toggle_on_match     ((uint8)0x02)
#define ccp1_compareMode_gen_sw_interrupt    ((uint8)0x0A)
#define ccp1_compareMode_gen_event           ((uint8)0x0B)
#define ccp1_PWM_Mode                        ((uint8)0x0C)

#define ccp1_capture_not_ready               0x00
#define ccp1_capture_ready                   0x01

#define ccp1_compare_not_ready               0x00
#define ccp1_compare_ready                   0x01
/*section : macro functions declerations */
#define ccp1_set_mode(config)             (CCP1CONbits.CCP1M = config)
#define ccp2_set_mode(config)             (CCP2CONbits.CCP2M = config)
/*section : data types declerations*/
typedef enum{
    ccp1_capture_mode=0,
    ccp1_compare_mode,
    ccp1_pwm_mode        
}ccp_Mode_t;

typedef enum {
    ccp1_inst=0,
    ccp2_inst        
}ccp_type;

typedef enum {
    ccp1_ccp2_timer1=0,
    ccp1_timer1_ccp2_timer3,
    ccp1_ccp2_timer3       
}ccp_capture_t;

typedef union {
    struct {
       uint8 ccpr1_low;
       uint8 ccpr1_high;
   }; 
    struct {
       uint16 ccpr1_16bit;
   };
}ccp1_reg_t;


typedef struct {
    ccp_Mode_t  ccp1_mode;
    uint8 ccp1_variantModes_select;
    pin_config_t ccp_pin;
    ccp_type ccp_inst;
    ccp_capture_t capture_type;
    INTERRUPT_PERIORITY_T priority;
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    void(*CCP1_InterruptHandler)(void);
    INTERRUPT_PERIORITY_T ccp1_priority;
#endif  
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    void(*CCP2_InterruptHandler)(void);
    INTERRUPT_PERIORITY_T ccp2_priority;
#endif
#if CCP1_CFG_MODE_SELECTED == CCP1_CFG_PWM_MODE_SELECTED
    uint32 PWM_Frequency;
    uint8  timer2_postscaler_values      :4;
    uint8  timer2_prescaler_values       :2;
#endif    
}ccp1_t;

/*section : functions declerations*/
   Std_ReturnType CCP_INIT (const ccp1_t *ccp1 );
   Std_ReturnType CCP_DEINIT (const ccp1_t *ccp1 );
#if CCP1_CFG_MODE_SELECTED == CCP1_CFG_CAPTURE_MODE_SELECTED
   Std_ReturnType ccp1_IsCaptureReady (uint8 *capture_status);
   Std_ReturnType ccp1_Capture_Mode_Read_Value (uint16 *capture_value);
#endif  
    
#if CCP1_CFG_MODE_SELECTED == CCP1_CFG_COMPARE_MODE_SELECTED
   STD_ReturnType ccp1_IsCompareReady (uint8 *compare_status);
   STD_ReturnType ccp1_Compare_Mode_Set_Value (uint16 *compare_value);
#endif     

#if CCP1_CFG_MODE_SELECTED == CCP1_CFG_PWM_MODE_SELECTED
   STD_ReturnType ccp_PWM_set_duty(const ccp1_t *ccp1,const uint8 duty);
   STD_ReturnType ccp_PWM_start(const ccp1_t *ccp1);
   STD_ReturnType ccp_PWM_stop(const ccp1_t *ccp1);
#endif  
#endif	/* HAL_CCP1_H */

