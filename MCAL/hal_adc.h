
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

  
#ifndef HAL_ADC_H
#define	HAL_ADC_H

/*section : includes*/
#include "hal_adc_cfg.h"
#include "pic18f4620.h"
#include "../MCAL_std_types.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
/*section : macro declerations*/

/**
 *@brief :***NOTE*** WHEN SELECT AN9 all AN0->AN9 WILL BE ANALOG_FUNCTIONALITEY
 * AND OTHERS DIGITAL_FUNCTIONALITEY.
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY         0X0E
#define ADC_AN1_ANALOG_FUNCTIONALITY         0X0D
#define ADC_AN2_ANALOG_FUNCTIONALITY         0X0C
#define ADC_AN3_ANALOG_FUNCTIONALITY         0X0B
#define ADC_AN4_ANALOG_FUNCTIONALITY         0X0A
#define ADC_AN5_ANALOG_FUNCTIONALITY         0X09
#define ADC_AN6_ANALOG_FUNCTIONALITY         0X08
#define ADC_AN7_ANALOG_FUNCTIONALITY         0X07
#define ADC_AN8_ANALOG_FUNCTIONALITY         0X06
#define ADC_AN9_ANALOG_FUNCTIONALITY         0X05
#define ADC_AN10_ANALOG_FUNCTIONALITY        0X04
#define ADC_AN11_ANALOG_FUNCTIONALITY        0X03
#define ADC_AN12_ANALOG_FUNCTIONALITY        0X02
#define ADC_ALL_ANALOG_FUNCTIONALITY         0X00
#define ADC_ALL_DIGITAL_FUNCTIONALITY        0X0F

#define ADC_RESULT_RIGHT                     0X01U
#define ADC_RESULT_LEFT                      0X00U
#define ADC_VOLTAGE_REF_ENABLE               0X01U
#define ADC_VOLTAGE_REF_DISABLE              0X00U

#define adc_conversion_completed               1
#define adc_conversion_inprogres               0
/*section : macro functions declerations */

/*A/D conversion status : in progress /idle */
#define ADC_CONVERSION_STATUS()                 (ADCON0bits.GO_nDONE)

/* A/D start conversion*/
#define ADC_CONVERSION_START()                  (ADCON0bits.GODONE = 1)

/*A/D module enable / disable*/
#define ADC_CONVERSION_ENABLE()                 (ADCON0bits.ADON = 1)
#define ADC_CONVERSION_DISABLE()                (ADCON0bits.ADON = 0)

/*A/D voltage reference configration*/
#define ADC_ENABLE_VOLTAGE_REFERENCE()           do{ADCON1bits.VCFG1 = 1;\
                                                    ADCON1bits.VCFG0 = 1;\
                                                    }while(0)
                                                        
#define ADC_DISABLE_VOLTAGE_REFERENCE()          do{ADCON1bits.VCFG1 = 0;\
                                                    ADCON1bits.VCFG0 = 0;\
                                                    }while(0)      
/*SELECT ANX CHANNELS FOR ANALOG / DIGITAL*/
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_config)   (ADCON1bits.PCFG =_config )

/*A/D FORMAT_JUSTIFY*/
#define ADC_RESULT_RIGHT_FORMAT()                   (ADCON2bits.ADFM =1) 
#define ADC_RESULT_LEFT_FORMAT()                    (ADCON2bits.ADFM =0) 

/*section : data types declerations*/
typedef enum {
    ADC_CHANEEL_AN0 =0,
    ADC_CHANEEL_AN1 ,
    ADC_CHANEEL_AN2,
    ADC_CHANEEL_AN3 ,
    ADC_CHANEEL_AN4 ,
    ADC_CHANEEL_AN5,
    ADC_CHANEEL_AN6 ,
    ADC_CHANEEL_AN7 ,
    ADC_CHANEEL_AN8,
    ADC_CHANEEL_AN9 ,
    ADC_CHANEEL_AN10 ,
    ADC_CHANEEL_AN11,
    ADC_CHANEEL_AN12 ,
}adc_channel_select_t;

typedef enum {
    ADC_0_TAD=0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}adc_acqusition_time_t;

typedef enum {
    ADC_CONVERSION_CLOCK_FOSC_DIV_2=0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,       
}adc_conversion_clock_t;

typedef struct {
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
    void(*adc_InterruptHandler)(void);
    INTERRUPT_PERIORITY_T priority;
#endif    
    adc_acqusition_time_t  AcqusitionTime;
    adc_conversion_clock_t ConversionClock;
    adc_channel_select_t   ChannelSelect;
    uint8 format              :1;
    uint8 voltage_ref         :1;
    uint8 adc_reserved        :6;
}adc_confg_t;
/*section : functions declerations*/
Std_ReturnType Adc_Init (const adc_confg_t *_adc );
Std_ReturnType Adc_Deinit (const adc_confg_t *_adc );
Std_ReturnType Adc_Select_Channel (const adc_confg_t *_adc , adc_channel_select_t channel);
Std_ReturnType Adc_Start_Conversion (const adc_confg_t *_adc);
Std_ReturnType Adc_IsConversionDone (const adc_confg_t *_adc , uint8 *Conversion_Status);
Std_ReturnType Adc_GetConversionResult (const adc_confg_t *_adc , uint16 *Conversion_Result);
Std_ReturnType Adc_GetConversion_Blocking (const adc_confg_t *_adc ,adc_channel_select_t channel  
                                          ,uint16 *Conversion_Result);
Std_ReturnType ADC_Start_Conversion_Interrupt (const adc_confg_t *_adc ,adc_channel_select_t channel);
#endif	/* HAL_ADC_H */

