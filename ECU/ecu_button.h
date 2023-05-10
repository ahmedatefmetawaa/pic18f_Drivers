
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

  
#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/*section : includes*/
#include"ecu_button_cfg.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
/*section : macro declerations*/

/*section : macro functions declerations */

/*section : data types declerations*/
typedef enum {
    button_pressed=0,
    button_released        
}button_state_t;

typedef enum {
    button_active_high,
    button_active_low
}button_active_t;

typedef struct{
 pin_config_t button_pin;
 button_state_t button_state;
 button_active_t button_connection;
}button_t;

/*section : functions declerations*/
Std_ReturnType ButtonInitialize(const button_t *button);
Std_ReturnType ButtonReadState(const button_t *button , button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

