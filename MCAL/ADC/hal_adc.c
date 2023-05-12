
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
#include "hal_adc.h"
static void (*ADC_INTERRUPT_HANDLER)(void) = NULL;
static inline void input_channel_port_config(adc_channel_select_t channel);
static inline void result_format_select(const adc_confg_t *_adc);
static inline void configure_voltage_reference (const adc_confg_t *_adc);
/**
 * @summary     : initialize ADC module
 * @description : this routine initialize the ADC 
 *                this routine must called before any other ADC routine
 *                this routine must called once during system initialization
 * @preconditions : None
 * @param  :  _adc pointer to adc configration
 * @return : status of function : 
 *           E_NOK : the function has issues 
 *           E_OK  : the function done successfully    
 */
Std_ReturnType Adc_Init (const adc_confg_t *_adc )
{
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
    /*disable the adc*/
    ADC_CONVERSION_DISABLE();    
    /*configure the acqusition time*/
    ADCON2bits.ACQT = _adc->AcqusitionTime;
    /*configure the conversion clock*/
    ADCON2bits.ADCS = _adc->ConversionClock;
    /*configure the default channel*/
    ADCON0bits.CHS =  _adc->ChannelSelect;
    input_channel_port_config(_adc->ChannelSelect);
    /*configure the interrupt*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_InterruptPeripheralsEnable();
    ADC_INTERRUPT_ENABLE();
    ADC_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
    if(INTERRUPT_HIGH_PRIORITY == _adc->priority){ADC_HIGH_PRIORITY_SET();}
    else if(INTERRUPT_LOW_PRIORITY == _adc->priority){ADC_LOW_PRIORITY_SET();}
    else{/*Nothing*/}
#endif
   ADC_INTERRUPT_HANDLER = _adc->adc_InterruptHandler;
#endif
    /*configure the result format*/ 
    result_format_select(_adc);
    /*configure the voltage reference*/  
    configure_voltage_reference(_adc);
    /*enable the adc*/ 
    ADC_CONVERSION_ENABLE();
    }
    return ret;
}
Std_ReturnType Adc_Deinit (const adc_confg_t *_adc )
{
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
   /*disable the adc*/
    ADC_CONVERSION_DISABLE(); 
   /*Disable the interrupt*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    ADC_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}
Std_ReturnType Adc_Select_Channel (const adc_confg_t *_adc , adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
    /*configure the selected channel*/
    ADCON0bits.CHS = channel;
    input_channel_port_config(channel);   
    }
    return ret;
}
Std_ReturnType Adc_Start_Conversion (const adc_confg_t *_adc)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
      ADC_CONVERSION_START();   
    }
    return ret;
}
Std_ReturnType Adc_IsConversionDone (const adc_confg_t *_adc , uint8 *Conversion_Status)
{
    Std_ReturnType ret = E_OK;
    if((NULL == _adc)  ||  (NULL ==Conversion_Status )){
        ret = E_NOT_OK;
    }
    else{
      *Conversion_Status = (uint8)(!(ADCON0bits.GODONE));  
    }
    return ret; 
}
Std_ReturnType Adc_GetConversionResult (const adc_confg_t *_adc , uint16 *Conversion_Result)
{
    Std_ReturnType ret = E_OK;
    if((NULL == _adc)  ||  (NULL ==Conversion_Result )){
        ret = E_NOT_OK;
    }
    else{
    if(ADC_RESULT_RIGHT == _adc->format){
        *Conversion_Result = (uint16)((ADRESH <<8) + ADRESL); 
    }
    else if (ADC_RESULT_LEFT == _adc->format){
        *Conversion_Result = (uint16)(((ADRESH <<8) + ADRESL)>>6);
    }
    else{
       *Conversion_Result = (uint16)((ADRESH <<8) + ADRESL);
    }
    return ret;
}
}
Std_ReturnType Adc_GetConversion_Blocking (const adc_confg_t *_adc ,adc_channel_select_t channel  
                                  ,uint16 *Conversion_Result)
{
    Std_ReturnType ret = E_OK;
    if((NULL == _adc)  ||  (NULL ==Conversion_Result )){
        ret = E_NOT_OK;
    }
    else{
    /*configure the selected channel*/
    ret = Adc_Select_Channel(_adc ,channel );  
    /*start conversion*/
    ret = Adc_Start_Conversion(_adc);
    /*conversion status*/
    while(ADCON0bits.GO_nDONE);
    Adc_GetConversionResult(_adc ,Conversion_Result );       
    }
   return ret;  
}

Std_ReturnType ADC_Start_Conversion_Interrupt (const adc_confg_t *_adc ,adc_channel_select_t channel)
{
    
    Std_ReturnType ret = E_OK;
    if(NULL == _adc ){
        ret = E_NOT_OK;
    }
    else{
    /*configure the selected channel*/
    ret = Adc_Select_Channel(_adc ,channel );  
    /*start conversion*/
    ret = Adc_Start_Conversion(_adc);    
    }
   return ret;  
}

static inline void input_channel_port_config(adc_channel_select_t channel)
{
    switch(channel){
        case ADC_CHANEEL_AN0: SET_BIT(TRISA , _TRISA_RA0_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN1: SET_BIT(TRISA , _TRISA_RA1_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN2: SET_BIT(TRISA , _TRISA_RA2_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN3: SET_BIT(TRISA , _TRISA_RA3_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN4: SET_BIT(TRISA , _TRISA_RA5_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN5: SET_BIT(TRISE , _TRISE_RE0_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN6: SET_BIT(TRISE , _TRISE_RE1_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN7: SET_BIT(TRISE , _TRISE_RE2_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN8: SET_BIT(TRISB , _TRISB_RB2_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN9: SET_BIT(TRISB , _TRISB_RB3_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN10: SET_BIT(TRISB , _TRISB_RB1_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN11: SET_BIT(TRISB , _TRISB_RB4_POSN );break;/*disable the output config*/
        case ADC_CHANEEL_AN12: SET_BIT(TRISB , _TRISB_RB0_POSN );break;/*disable the output config*/
        default : /*Nothing*/;
    }
}

static inline void result_format_select(const adc_confg_t *_adc)
{
    if(ADC_RESULT_RIGHT == _adc->format){
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if (ADC_RESULT_LEFT == _adc->format){
        ADC_RESULT_LEFT_FORMAT();
    }
    else{
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static inline void configure_voltage_reference (const adc_confg_t *_adc)
{
    if(ADC_VOLTAGE_REF_ENABLE == _adc->voltage_ref){
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if (ADC_VOLTAGE_REF_DISABLE == _adc->voltage_ref){
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else{
         ADC_DISABLE_VOLTAGE_REFERENCE();
    }  
}

 void ADC_ISR(void){
     ADC_INTERRUPT_FLAG_CLEAR();
     if(ADC_INTERRUPT_HANDLER){ADC_INTERRUPT_HANDLER();}
 }