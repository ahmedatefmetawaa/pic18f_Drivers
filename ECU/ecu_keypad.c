
/* 
 * File:   ecu_keypad
 * Author: ahmed atef 
 * Comments:
 * Revision history:1/19/2023

 */

#include "ecu_keypad.h"

static const uint8 keypad_values [ecu_keypad_rows][ecu_keypad_columns] = {
                                                                            {'7','8','9','/'},
                                                                            {'4','5','6','*'},
                                                                            {'1','2','3','-'},
                                                                            {'#','0','=','+'}
                                                                         };
/**
 * @brief  :
 * @param  : keypad_obj:
 * @return : status of function
 */

Std_ReturnType keypad_initialize (const keypad_t *keypad_obj)
{
    uint8 row_counter , column_counter=0;
    Std_ReturnType ret = E_OK;
    if(NULL == keypad_obj){
        ret = E_NOT_OK;
    }
    else{
        for (row_counter=0; row_counter<ecu_keypad_rows; row_counter++){
            ret = gpio_pin_intialize(&(keypad_obj->keypad_row_pins[row_counter]));
        }
        for (column_counter=0; column_counter<ecu_keypad_columns; column_counter++){
            ret = gpio_pin_direction_intialize(&(keypad_obj->keypad_columns_pins[column_counter]));
        }
    }
    return ret;
}
/**
 * @brief :
 * @param :keypad_obj:
 * @param :
 * @return : status of function
 */
Std_ReturnType keypad_get_value (const keypad_t *keypad_obj , uint8 *value)
{
   uint8 l_row_counter , l_column_counter , l_counter = 0;
   logic_t keypad_logic =GPIO_LOW;
    Std_ReturnType ret = E_OK;
    if(NULL == keypad_obj  || NULL == value ){
        ret = E_NOT_OK;
    }
    else {
        for (l_row_counter=0; l_row_counter<ecu_keypad_rows; l_row_counter++){
            for(l_counter=0; l_counter<ecu_keypad_rows; l_counter++){
                ret =gpio_pin_write_logic(&(keypad_obj->keypad_row_pins[l_counter]) , GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(keypad_obj->keypad_row_pins[l_row_counter]) , GPIO_HIGH);
            for (l_column_counter=0; l_column_counter<ecu_keypad_columns; l_column_counter++){
                ret = gpio_pin_read_logic(&(keypad_obj->keypad_columns_pins[l_column_counter]) ,&keypad_logic );
                if(GPIO_HIGH == keypad_logic){
                    *value = keypad_values[l_row_counter][l_column_counter];
                }else{/*Nothing*/}
            }
            
        }
    }
    return ret;
}
