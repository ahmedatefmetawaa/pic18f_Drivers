/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
#include "hal_usart.h"
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(*Eusart_TxInterruptHandler)(void) = NULL;
#endif 
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*Eusart_RxInterruptHandler)(void)= NULL;
static void (*Eusart_FrammingInterruptHandler)(void)= NULL;
static void (*Eusart_OverrunInterruptHandler)(void)= NULL;
#endif
static void Baud_Rate_Calculations (const eusart_t *eusart);
static void EUSART_ASYN_TX_INIT (const eusart_t *eusart);
static void EUSART_ASYN_RX_INIT (const eusart_t *eusart);

Std_ReturnType USART_INIT (const eusart_t *eusart)
{
    Std_ReturnType ret = E_OK;
    if(NULL == eusart){
        ret = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        Baud_Rate_Calculations(eusart);
        EUSART_ASYN_TX_INIT(eusart);
        EUSART_ASYN_RX_INIT(eusart);
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
    }
    return ret;
}
Std_ReturnType USART_DEINIT (const eusart_t *eusart)
{
    Std_ReturnType ret = E_OK;
    if(NULL == eusart){
        ret = E_NOT_OK;
    }
    else{
      RCSTAbits.SPEN = EUSART_MODULE_DISABLE;   
    }
    return ret;
    
}
Std_ReturnType USART_READ_BYTE_BLOCKING ( uint8 *data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == data){
        ret = E_NOT_OK;
    }
    else{
        while(!PIR1bits.RCIF);
         *data = RCREG;
    }
    return ret;
    
}

Std_ReturnType USART_READ_BYTE_NON_BLOCKING (uint8 *data)
{
     Std_ReturnType ret = E_OK;
    if(1 == PIR1bits.RCIF){
        *data = RCREG;
    }
    else{
        ret = E_NOT_OK;  
     }
     return ret;
}
Std_ReturnType USART_WRITE_BYTE_BLOCKING (uint8 data)
{
    Std_ReturnType ret = E_OK;
    while(!TXSTAbits.TRMT);
    EUSART_TX_INTERRUPT_ENABLE();
    TXREG = data;
    return ret;
    
}

Std_ReturnType USART_WRITE_STRING_BLOCKING (uint8 *data , uint8 str_len)
{
    uint8 char_counter=0;
    Std_ReturnType ret = E_OK;
    if(NULL == data){
        ret = E_NOT_OK;
    }
    else{
     for(char_counter=0;char_counter < str_len;char_counter++ ){
         USART_WRITE_BYTE_BLOCKING( data[char_counter]);
     }   
    }
    return ret;   
}

static void Baud_Rate_Calculations (const eusart_t *eusart)
{
    float baud_rate_temp;
    Std_ReturnType ret = E_OK;
    switch(eusart->baudrate_gen){
        case baudrate_async_8bit_low_speed :
            TXSTAbits.SYNC =EUSART_ASYNCHRONOUS_MODE ;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_BAUDRATE_8BIT_GEN;
            baud_rate_temp = ((_XTAL_FREQ / (float)eusart->baudrate)/64)-1;
        break;
        
        case baudrate_async_8bit_high_speed :
            TXSTAbits.SYNC =EUSART_ASYNCHRONOUS_MODE ;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_BAUDRATE_8BIT_GEN; 
            baud_rate_temp = ((_XTAL_FREQ / (float)eusart->baudrate)/16)-1;
        break; 
        
        case baudrate_async_16bit_low_speed :
            TXSTAbits.SYNC =EUSART_ASYNCHRONOUS_MODE ;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_BAUDRATE_16BIT_GEN;
            baud_rate_temp = ((_XTAL_FREQ / (float)eusart->baudrate)/16)-1;
        break;
        
        case baudrate_async_16bit_high_speed :
            TXSTAbits.SYNC =EUSART_ASYNCHRONOUS_MODE ;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_BAUDRATE_16BIT_GEN; 
            baud_rate_temp = ((_XTAL_FREQ / (float)eusart->baudrate)/4)-1;
        break; 
        
        case baudrate_sync_8bit :
            TXSTAbits.SYNC =EUSART_SYNCHRONOUS_MODE ;
            BAUDCONbits.BRG16 = EUSART_BAUDRATE_8BIT_GEN; 
            baud_rate_temp = ((_XTAL_FREQ / (float)eusart->baudrate)/4)-1;
        break; 
        
        case baudrate_sync_16bit :
            TXSTAbits.SYNC =EUSART_SYNCHRONOUS_MODE ;
            BAUDCONbits.BRG16 = EUSART_BAUDRATE_16BIT_GEN;  
            baud_rate_temp = ((_XTAL_FREQ / (float)eusart->baudrate)/4)-1;
        break;
        default :;
    }
  SPBRG= (uint8)((uint32)baud_rate_temp);
  SPBRGH = (uint8)(((uint32)baud_rate_temp) >> 8 );
}

static void EUSART_ASYN_TX_INIT (const eusart_t *eusart)
{
    /*transmit feature enable*/
    if(EUSART_ASYNCHRONOUS_TX_ENABLE ==eusart->eusart_tx_cfg.eusart_tx_enable){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
      /*interrupt configure*/
    if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE ==eusart->eusart_tx_cfg.eusart_tx_interrupt){
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
     EUSART_TX_INTERRUPT_ENABLE();
     Eusart_TxInterruptHandler = eusart->EUSART_TXdefaultInterruptHandler;
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_ENABLE();
    if(INTERRUPT_HIGH_PRIORITY == eusart->eusart_tx_cfg.eusart_tx_priority)
    {
     EUSART_TX_HIGH_PRIORITY_SET();
     INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY == eusart->eusart_tx_cfg.eusart_tx_priority)
    {
     EUSART_TX_LOW_PRIORITY_SET();
     NTERRUPT_GIlobalInterruptLowEnable();
    }
    else{/*Nothing*/}
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_InterruptPeripheralsEnable();
#endif
        
#endif
       } 
       else if (EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE==eusart->eusart_tx_cfg.eusart_tx_interrupt){
           PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
       }
       else{/*Nothing*/}
       
       /*9-bit configure*/
       if( EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE==eusart->eusart_tx_cfg.eusart_tx_9bit){
           TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE;
       } 
       else if (EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE==eusart->eusart_tx_cfg.eusart_tx_9bit){
           TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
       }
       else{/*Nothing*/}
    }
    else{/*Nothing*/}
}


static void EUSART_ASYN_RX_INIT (const eusart_t *eusart)
{
    /*recieve feature enable*/
    if(EUSART_ASYNCHRONOUS_RX_ENABLE ==eusart->eusart_rx_cfg.eusart_rx_enable){  
       RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE; 
       Eusart_RxInterruptHandler = eusart->EUSART_RXdefaultInterruptHandler;
       Eusart_FrammingInterruptHandler = eusart->EUSART_FrammingErrorHandler;
       Eusart_OverrunInterruptHandler = eusart->EUSART_OverrunErrorHandler;
    /*interrupt configure*/
    if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE ==eusart->eusart_rx_cfg.eusart_rx_interrupt){
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
     EUSART_RX_INTERRUPT_ENABLE();
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_ENABLE();
    if(INTERRUPT_HIGH_PRIORITY == eusart->eusart_rx_cfg.eusart_rx_priority)
    {
     EUSART_RX_HIGH_PRIORITY_SET();
     INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY == eusart->eusart_rx_cfg.eusart_rx_priority)
    {
     EUSART_RX_LOW_PRIORITY_SET();
     NTERRUPT_GIlobalInterruptLowEnable();
    }
    else{/*Nothing*/}
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_InterruptPeripheralsEnable();
#endif
        
#endif           
       } 
       else if (EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE==eusart->eusart_rx_cfg.eusart_rx_interrupt){
           PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
       }
       else{/*Nothing*/}
       
       /*9-bit configure*/
       if(EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE ==eusart->eusart_rx_cfg.eusart_rx_9bit){
           RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE;
       } 
       else if (EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE==eusart->eusart_rx_cfg.eusart_rx_9bit){
           RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
       }
       else{/*Nothing*/}
    }
    else{/*Nothing*/}   
}

void eusart_tx_ISR(void)
{
 EUSART_TX_INTERRUPT_DISABLE();
 if(Eusart_TxInterruptHandler){
     Eusart_TxInterruptHandler;}
 else{/*Nothing*/}

}
void eusart_rx_ISR(void)
{
 if(Eusart_RxInterruptHandler){
     Eusart_RxInterruptHandler;}
 else{/*Nothing*/}  
 if(Eusart_FrammingInterruptHandler){
     Eusart_FrammingInterruptHandler;}
 else{/*Nothing*/}  
  if(Eusart_OverrunInterruptHandler){
     Eusart_OverrunInterruptHandler;}
 else{/*Nothing*/}
}


 