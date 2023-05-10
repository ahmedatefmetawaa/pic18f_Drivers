
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H
/*section : includes*/
#include "ecu_keypad_cfg.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
/*section : macro declerations*/
#define ecu_keypad_rows      4
#define ecu_keypad_columns   4
/*section : macro functions declerations */

/*section : data types declerations*/
typedef struct {
    pin_config_t keypad_row_pins[ecu_keypad_rows];
    pin_config_t keypad_columns_pins[ecu_keypad_columns];
}keypad_t;
/*section : functions declerations*/
Std_ReturnType keypad_initialize (const keypad_t *keypad_obj);
Std_ReturnType keypad_get_value (const keypad_t *keypad_obj , uint8 *value);

#endif	/* ECU_KEYPAD_H */

