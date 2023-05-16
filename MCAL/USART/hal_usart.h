
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

  
#ifndef HAL_USART_H
#define	HAL_USART_H
/*section : includes*/
#include"hal_usart_cfg.h"
#include "pic18f4620.h"
#include "../MCAL_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
/*section : macro declerations*/
/*EUSART MODULE ENABLE / DISABLE*/
#define EUSART_MODULE_ENABLE  1
#define EUSART_MODULE_DISABLE 0
/*EUSART OPERATION MODE*/
#define EUSART_SYNCHRONOUS_MODE  1
#define EUSART_ASYNCHRONOUS_MODE 0
/*EUSART BAUD RATE SPEED*/
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED   0
/*EUSART BAUD RATE GENERATOR REGISTER SIZE*/
#define EUSART_BAUDRATE_16BIT_GEN  1
#define EUSART_BAUDRATE_8BIT_GEN   0

/*EUSART TRANSMIT ENABLE*/
#define EUSART_ASYNCHRONOUS_TX_ENABLE  1
#define EUSART_ASYNCHRONOUS_TX_DISABLE 0
/*EUSART TRANSMIT INTERRUPT ENABLE*/
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE  1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE 0
/*EUSART TRANSMIT 9-BIT ENABLE*/
#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE  1
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE 0

/*EUSART RECIEVER ENABLE*/
#define EUSART_ASYNCHRONOUS_RX_ENABLE  1
#define EUSART_ASYNCHRONOUS_RX_DISABLE 0
/*EUSART RECIEVER INTERRUPT ENABLE*/
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE  1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE 0
/*EUSART RECIEVER 9-BIT ENABLE*/
#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE  1
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE 0

/*EUSART FRAMMING ERROR*/
#define EUSART_FRAMMING_ERROR_DETECTED 1 
#define EUSART_FRAMMING_ERROR_CLEARED  0
/*EUSART OVERRUN ERROR*/
#define EUSART_OVERRUN_ERROR_DETECTED 1 
#define EUSART_OVERRUN_ERROR_CLEARED  0

/*section : macro functions declerations */

/*section : data types declerations*/
typedef enum {
  baudrate_async_8bit_low_speed, 
  baudrate_async_8bit_high_speed,
  baudrate_async_16bit_low_speed,
  baudrate_async_16bit_high_speed,
  baudrate_sync_8bit,
  baudrate_sync_16bit       
}baudrate_gen_t;
typedef struct{
INTERRUPT_PERIORITY_T eusart_tx_priority;   
 uint8 eusart_reserved  :5;
 uint8 eusart_tx_enable :1;
 uint8 eusart_tx_interrupt :1;
 uint8 eusart_tx_9bit     :1;
}eusart_tx_t;
typedef struct{
 INTERRUPT_PERIORITY_T eusart_rx_priority;   
 uint8 eusart_reserved  :5;
 uint8 eusart_rx_enable :1;
 uint8 eusart_rx_interrupt :1;
 uint8 eusart_rx_9bit     :1;
}eusart_rx_t;
typedef union {
   struct{
    uint8 error_reserved :6;
    uint8 framming_error :1;
    uint8 overrun_error  :1;
   }; 
   uint8 status;
}eusart_error_status_t;

typedef struct{
   uint32 baudrate;
   baudrate_gen_t baudrate_gen;
   eusart_tx_t eusart_tx_cfg;
   eusart_rx_t eusart_rx_cfg;
   eusart_error_status_t error_status;
   void (*EUSART_TXdefaultInterruptHandler)(void);
   void (*EUSART_RXdefaultInterruptHandler)(void);
   void (*EUSART_FrammingErrorHandler)(void);
   void (*EUSART_OverrunErrorHandler)(void);
}eusart_t;
/*section : functions declerations*/
Std_ReturnType USART_INIT (const eusart_t *eusart);
Std_ReturnType USART_DEINIT (const eusart_t *eusart);
Std_ReturnType USART_READ_BYTE_BLOCKING (uint8 *data);
Std_ReturnType USART_READ_BYTE_NON_BLOCKING (uint8 *data);
Std_ReturnType USART_WRITE_BYTE_BLOCKING (uint8 data);
Std_ReturnType USART_WRITE_STRING_BLOCKING (uint8 *data , uint8 str_len);
#endif	/* HAL_USART_H */

