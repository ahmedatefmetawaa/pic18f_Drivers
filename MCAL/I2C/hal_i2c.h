

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
  
#ifndef HAL_I2C_H
#define	HAL_I2C_H

/*section : includes*/
#include "pic18f4620.h"
#include "../MCAL_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
/*section : macro declerations*/
#define i2c_slew_rate_disable          1
#define i2c_slew_rate_enable           0

#define i2c_smbus_enable               1
#define i2c_smbus_disable              0

#define i2c_last_byte_data             1
#define i2c_last_byte_address          0

#define i2c_stop_bit_detection         1
#define i2c_stop_bit_not_detection     0
#define i2c_start_bit_detection        1
#define i2c_start_bit_not_detection    0

#define mssp_master_mode               1
#define mssp_slave_mode                0

#define I2C_slave_mode_7bit_address                     0x06U
#define I2C_slave_mode_10bit_address                    0x07U
#define I2C_slave_mode_7bit_address_ss_int_enable       0x0EU
#define I2C_slave_mode_10bit_address_ss_int_enable      0x0FU
#define I2C_master_mode_defined_clock                   0x08U
#define I2C_master_mode_firmware_controled              0x0BU

#define I2C_general_call_enable        1
#define I2C_general_call_disable       0
#define I2C_master_rec_enable          1
#define I2C_master_rec_disable         0

#define I2C_ACK_REC_FROM_SLAVE         0
#define I2C_ACK_NOT_REC_FROM_SLAVE     1
#define I2C_master_send_ack            0
#define I2C_master_send_not_ack        1
/*section : macro functions declerations */
#define mssp_module_enable_cfg()             (SSPCON1bits.SSPEN = 1)
#define mssp_module_disable_cfg()            (SSPCON1bits.SSPEN = 0)
#define i2c_slew_rate_disable_cfg()          (SSPSTATbits.SMP = 1)
#define i2c_slew_rate_enable_cfg()           (SSPSTATbits.SMP = 0)

#define i2c_smbus_enable_cfg()               (SSPSTATbits.CKE = 1)
#define i2c_smbus_disable_cfg()              (SSPSTATbits.CKE = 0)

#define I2C_general_call_enable_cfg()        (SSPCON2bits.GCEN = 1)
#define I2C_general_call_disable_cfg()       (SSPCON2bits.GCEN = 0)
#define I2C_master_rec_enable_cfg()          (SSPCON2bits.RCEN = 1)
#define I2C_master_rec_disable_cfg()         (SSPCON2bits.RCEN = 0)

/*section : data types declerations*/
typedef struct{
  uint8 mssp_mode_cfg;
  uint8 i2c_slave_add :1;
  uint8 i2c_mode :1;
  uint8 slew_rate :1;
  uint8 SMbus_control :1;
  uint8 general_call :1;
  uint8 master_receiver_mode :1;
  uint8 reserved_mode :2;
}i2c_config_t;
typedef struct{
   uint32 i2c_clock; /*master clock frequency*/
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE  ==  INTERRUPT_FEATURE_ENABLE 
   void (*I2C_defaultInterruptHandler)(void);
   void (*I2C_report_write_collision)(void);
   void (*I2C_report_recieve_overflow)(void);
   INTERRUPT_PERIORITY_T mssp_i2c_priority;
   INTERRUPT_PERIORITY_T mssp_i2c_BC_priority;
#endif       
   i2c_config_t i2c_config;
}Mssp_I2c_t;
/*section : functions declerations*/
Std_ReturnType Mssp_I2C_Init(const Mssp_I2c_t *I2c_obj );
Std_ReturnType Mssp_I2C_Deinit(const Mssp_I2c_t *I2c_obj );
Std_ReturnType Mssp_I2C_Master_Send_Start(const Mssp_I2c_t *I2c_obj );
Std_ReturnType Mssp_I2C_Master_Send_Repeated_Start(const Mssp_I2c_t *I2c_obj );
Std_ReturnType Mssp_I2C_Master_Send_Stop(const Mssp_I2c_t *I2c_obj );
Std_ReturnType Mssp_I2C_Master_Write_Blocking(const Mssp_I2c_t *I2c_obj , uint8 data, uint8 *ack);
Std_ReturnType Mssp_I2C_Master_Read_Blocking(const Mssp_I2c_t *I2c_obj, uint8 ack, uint8 *data );
#endif	/* HAL_I2C_H */

