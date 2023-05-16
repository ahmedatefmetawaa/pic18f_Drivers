/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#include "hal_i2c.h"

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
static void (*I2C_DefaultInterruptHandler)(void);
static void (*I2C_report_write_collision_Handler)(void);
static void (*I2C_report_recieve_overflow_handler)(void);
#endif 
static void mssp_i2c_interrupt_configration (const Mssp_I2c_t *I2c_obj);

Std_ReturnType Mssp_I2C_Init(const Mssp_I2c_t *I2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == I2c_obj){
        ret = E_NOT_OK;
    }
    else{
       /*disable mssp module*/ 
        mssp_module_disable_cfg();
        /*mssp i2c select mode*/
        if(mssp_master_mode == I2c_obj->i2c_config.i2c_mode){
        /*mssp i2c master mode configration*/
           /*clock configration*/
            SSPCON1bits.SSPM =I2c_obj->i2c_config.mssp_mode_cfg;
            SSPADD = (uint8)(((_XTAL_FREQ/4.0)/I2c_obj->i2c_clock)-1);
        }
        else if (mssp_slave_mode == I2c_obj->i2c_config.i2c_mode){
        /*mssp i2c slave mode configration*/ 
           /*general call configration*/
            if(I2C_general_call_enable == I2c_obj->i2c_config.general_call){
                I2C_general_call_enable_cfg();
            }
            else if (I2C_general_call_disable == I2c_obj->i2c_config.general_call){
                I2C_general_call_disable_cfg();
            }
            else{/*Nothing*/}
            /*clear the write collision bit*/
            SSPCON1bits.WCOL = 0; /*clear collision*/
            /*clear the receive overflow bit*/
            SSPCON1bits.SSPOV = 0; /*clear overflow*/
            /*release the clock*/
            SSPCON1bits.CKP = 1; /*permit the trans to put clock on scl*/
            /*assign the i2c slave address*/
           SSPADD = I2c_obj->i2c_config.i2c_slave_add;
           /*slave mode configration*/
            SSPCON1bits.SSPM =I2c_obj->i2c_config.mssp_mode_cfg;
        }
        else {/*Nothing*/}

        /*master / slave GPIO configration*/
        TRISCbits.RC3 = 1;
        TRISCbits.RC4 = 1;
        /*slew rate configration*/
            if(i2c_slew_rate_enable == I2c_obj->i2c_config.slew_rate){
                i2c_slew_rate_enable_cfg();
            }
            else if (i2c_slew_rate_disable == I2c_obj->i2c_config.slew_rate){
                i2c_slew_rate_disable_cfg();
            }
            else {/*Nothing*/}
        /*sm bus configration*/
            if(i2c_smbus_enable == I2c_obj->i2c_config.SMbus_control){
                i2c_smbus_enable_cfg();
            }
            else if (i2c_smbus_disable == I2c_obj->i2c_config.SMbus_control){
                i2c_smbus_disable_cfg();
            }
            else {/*Nothing*/}
        /*interrupt configration*/
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    mssp_i2c_interrupt_configration(I2c_obj);
#endif        
        /*enable mssp module*/
        mssp_module_enable_cfg();
    }
    return ret;
}

Std_ReturnType Mssp_I2C_Deinit(const Mssp_I2c_t *I2c_obj )
{
    Std_ReturnType ret = E_OK;
    if(NULL == I2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /*disable mssp module*/
        mssp_module_disable_cfg();
        /*interrupt configration*/
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_INTERRUPT_DISABLE();                
        MSSP_I2C_BUS_COL_INTERRUPT_DISABLE();     
#endif  
    }
    return ret;
}

Std_ReturnType Mssp_I2C_Master_Send_Start(const Mssp_I2c_t *I2c_obj )
{
    Std_ReturnType ret = E_OK;
    if(NULL == I2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /*initiat start condition on sda and scl*/
        SSPCON2bits.SEN = 1 ; /*initiat start condition on sda and scl (cleared by hardware)*/
        /*wait the completion of the start condition*/
        while(SSPCON2bits.SEN);
        /*clear the mssp interrupt flag : sspif*/
        PIR1bits.SSPIF = 0;
        /*report the start condition detection*/
        if(i2c_start_bit_detection == SSPSTATbits.S){
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
    }
    }
    return ret; 
}

Std_ReturnType Mssp_I2C_Master_Send_Repeated_Start(const Mssp_I2c_t *I2c_obj )
{
    Std_ReturnType ret = E_OK;
    if(NULL == I2c_obj){
        ret = E_NOT_OK;
    }
    else{
        /*initiat repeated start condition on sda and scl*/
        SSPCON2bits.RSEN = 1;
        /*wait the completion of the repeated start condition*/
        while(SSPCON2bits.RSEN);
        /*clear the mssp interrupt flag : sspif*/
        PIR1bits.SSPIF = 0;
    }
    return ret;
 
}

Std_ReturnType Mssp_I2C_Master_Send_Stop(const Mssp_I2c_t *I2c_obj )
{
    Std_ReturnType ret = E_OK;
    if(NULL == I2c_obj){
        ret = E_NOT_OK;
    }
    else{
       /*initiat start condition on sda and scl*/
        SSPCON2bits.PEN = 1;
        /*wait the completion of the stop condition*/
        while(SSPCON2bits.PEN);
        /*clear the mssp interrupt flag : sspif*/
        PIR1bits.SSPIF = 0;
        /*report the stop condition detection*/
        if(i2c_stop_bit_detection == SSPSTATbits.P){
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
    }
    }
    return ret;
}

Std_ReturnType Mssp_I2C_Master_Write_Blocking(const Mssp_I2c_t *I2c_obj , uint8 data, uint8 *ack)
{
    Std_ReturnType ret = E_OK;
    if((NULL == I2c_obj)||(NULL == ack)){
        ret = E_NOT_OK;
    }
    else{
    /*write the data to data regester */
       SSPBUF = data;
    /*wait the completion of trasmit*/
       while(!PIR1bits.SSPIF);
    /*clear the mssp interrupt flag : sspif*/
       PIR1bits.SSPIF =0;
    /*report the acknowledge from slave*/
       if(I2C_ACK_REC_FROM_SLAVE == SSPCON2bits.ACKSTAT){
           *ack = I2C_ACK_REC_FROM_SLAVE;
       }
       else{
           *ack = I2C_ACK_NOT_REC_FROM_SLAVE;
       }
    }
    return ret;
}

Std_ReturnType Mssp_I2C_Master_Read_Blocking(const Mssp_I2c_t *I2c_obj, uint8 ack, uint8 *data )
{
    Std_ReturnType ret = E_OK;
    if((NULL == I2c_obj)||(NULL == data )){
        ret = E_NOT_OK;
    }
    else{
        /*master mode receiver enable*/
        I2C_master_rec_enable_cfg();
        /*wait the completion of rec 1byte : buffer full flag*/
        while(!SSPSTATbits.BF);
        /*copy the data regester to buffer variable*/
        *data = SSPBUF;
        /*send ack or notack after read*/
        if(I2C_master_send_ack == ack ){
            SSPCON2bits.ACKDT = 0;/*Acknowledge*/
            SSPCON2bits.ACKDT = 1; /*initiate acknowledge sequence on sda and acl (cleared by HW)*/
        }
        else if(I2C_master_send_not_ack == ack){
            SSPCON2bits.ACKDT = 1;/*Not Acknowledge*/
            SSPCON2bits.ACKDT = 1; /*initiate acknowledge sequence on sda and acl (cleared by HW)*/
        }
        else{/*Nothing*/}
    }
    return ret;

}


static void mssp_i2c_interrupt_configration (const Mssp_I2c_t *I2c_obj)
{
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_INTERRUPT_ENABLE();
        MSSP_I2C_BUS_COL_INTERRUPT_ENABLE();
        MSSP_I2C_INTERRUPT_FLAG_CLEAR();              
        MSSP_I2C_BUS_COL_INTERRUPT_FLAG_CLEAR();
        I2C_DefaultInterruptHandler = I2c_obj->I2C_defaultInterruptHandler;
        I2C_report_write_collision_Handler = I2c_obj->I2C_report_write_collision;
        I2C_report_recieve_overflow_handler = I2c_obj->I2C_report_recieve_overflow;
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE  
INTERRUPT_PRIORITY_ENABLE();
    if(INTERRUPT_HIGH_PRIORITY == I2c_obj->mssp_i2c_priority)
    {
     MSSP_I2C_HIGH_PRIORITY_SET();
     INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY == I2c_obj->mssp_i2c_priority)
    {
     MSSP_I2C_LOW_PRIORITY_SET();
     NTERRUPT_GIlobalInterruptLowEnable();
    }
    else{/*Nothing*/}

    if(INTERRUPT_HIGH_PRIORITY == I2c_obj->mssp_i2c_BC_priority)
    {
     MSSP_I2C_BUS_COL_HIGH_PRIORITY_SET();
     INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY == I2c_obj->mssp_i2c_BC_priority)
    {
     MSSP_I2C_LOW_PRIORITY_SET();
     MSSP_I2C_BUS_COL_LOW_PRIORITY_SET();
    }
    else{/*Nothing*/}
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_InterruptPeripheralsEnable();
#endif        
#endif            
}


void mssp_i2c_ISR (void)
{
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
   MSSP_I2C_INTERRUPT_FLAG_CLEAR(); 
   if(I2C_DefaultInterruptHandler){
       I2C_DefaultInterruptHandler();
       
   }
 #endif    
}
void mssp_i2c_BC_ISR (void)
{
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_BUS_COL_INTERRUPT_FLAG_CLEAR();
    if(I2C_report_write_collision_Handler){
    I2C_report_write_collision_Handler();
    }
    #endif
}