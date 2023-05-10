/* 
 * File:   application.c
 * Author: Ahmed Atef
 *
 * Created on January 1, 2023, 3:26 PM
 */
/*section : include*/
#include "ecu_led.h"
/*section : functions implementation*/

/**
 * @brief initialize the assigned pin to be output and turn on/off led 
 * @param led : pointer to the led module configuration 
 * @return status of function
 */
Std_ReturnType led_initialize(const led_t *led) {
    Std_ReturnType ret = E_OK;
    if (NULL == led){
        ret = E_NOT_OK;
    }
    else{
       pin_config_t pin_obj = {.pin = led->pin , .port = led->port_name,
                               .direction = GPIO_DIRECTION_OUTPUT,.logic =led->led_status};
        gpio_pin_direction_intialize(&pin_obj);
    }

    return ret;
}

/**
 *@brief turn on led 
 * @param led : pointer to the led module configuration 
 * @return status of function
 */
Std_ReturnType led_on(const led_t *led) {
    Std_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOT_OK;
    }
    else{
       pin_config_t pin_obj = {.pin = led->pin , .port = led->port_name,
                               .direction = GPIO_DIRECTION_OUTPUT,.logic =led->led_status};
        gpio_pin_write_logic(&pin_obj , GPIO_HIGH);
    }

    return ret;
}

/**
 * @brief turn off led 
 * @param led : pointer to the led module configuration 
 * @return status of function 
 */
Std_ReturnType led_off(const led_t *led) {
    Std_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOT_OK;
    }
    else{
       pin_config_t pin_obj = {.pin = led->pin , .port = led->port_name,
                               .direction = GPIO_DIRECTION_OUTPUT,.logic =led->led_status};
        gpio_pin_write_logic(&pin_obj , GPIO_LOW);
    }

    return ret;
}

/**
 * @brief led toggle 
 * @param led : pointer to the led module configuration 
 * @return status of function 
 */
Std_ReturnType led_toggle(const led_t *led) {
    Std_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOT_OK;
    }
    else{
       pin_config_t pin_obj = {.pin = led->pin , .port = led->port_name,
                               .direction = GPIO_DIRECTION_OUTPUT,.logic =led->led_status};
        gpio_pin_toggle_logic(&pin_obj);
    }

    return ret;
}