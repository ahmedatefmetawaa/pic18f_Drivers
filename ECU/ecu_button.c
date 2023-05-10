/* 
 * File:   hal_GPIO.c
 * Author: Ahmed Atef
 *
 * Created on January 1, 2023, 3:26 PM
 */
#include "ecu_button.h"
/**
 * @brief initialize the assigned pin to be input and read from button 
 * @param led :  pointer to the button module configuration 
 * @return status of function
 */
Std_ReturnType ButtonInitialize(const button_t *button)
{
    Std_ReturnType ret = E_OK;
    if (NULL == button){
        ret = E_NOT_OK;}
    else{
       gpio_pin_direction_intialize(&(button->button_pin));
    }
    return ret;
}
/**
 * @brief initialize the assigned pin to be input to read from button 
 * @param led : pointer to the button module configuration 
 * @return status of function
 */
Std_ReturnType ButtonReadState(const button_t *button , button_state_t *btn_state)
{
   Std_ReturnType ret = E_OK;
   logic_t button_pin_status = GPIO_LOW ;
    if ((NULL == button) || (NULL == btn_state )){
        ret = E_NOT_OK;}
    else{
        gpio_pin_read_logic(&(button->button_pin) , &button_pin_status);
        if( button_active_high== button->button_connection){
            if(GPIO_HIGH == button_pin_status ){
                *btn_state = button_pressed;
            }
            else{
                *btn_state = button_released;
            }
        }
        else if (  button_active_low == button->button_connection){
            if(GPIO_HIGH == button_pin_status ){
                *btn_state = button_released;
            }
            else{
                *btn_state = button_pressed;
            }
        }
        else{
            /* Nothing */
        }
        ret = E_OK;
    }
    return ret; 
}
