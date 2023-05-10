#include "ecu_relay.h"

Std_ReturnType RelayInitialize (const relay_t *relay)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == relay ){
        ret = E_NOT_OK;
    }
    else {
        pin_config_t pin_obj = {.pin = relay->relay_pin , .port = relay->relay_port ,
                                .direction =GPIO_DIRECTION_OUTPUT , .logic = relay->relay_status };
        gpio_pin_intialize(&pin_obj);
     }
    return ret;
}
Std_ReturnType Relay_turn_on (const relay_t *relay)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == relay ){
        ret = E_NOT_OK;
    }
    else {
        pin_config_t pin_obj = {.pin = relay->relay_pin , .port = relay->relay_port ,
                                .direction =GPIO_DIRECTION_OUTPUT , .logic = relay->relay_status };
        gpio_pin_write_logic(&pin_obj , GPIO_HIGH);
     }
    return ret;
    
}
Std_ReturnType Relay_turn_off (const relay_t *relay)
{
     Std_ReturnType ret = E_NOT_OK;
    if (NULL == relay ){
        ret = E_NOT_OK;
    }
    else {
        pin_config_t pin_obj = {.pin = relay->relay_pin , .port = relay->relay_port ,
                                .direction =GPIO_DIRECTION_OUTPUT , .logic = relay->relay_status };
        gpio_pin_write_logic(&pin_obj , GPIO_LOW);
     }
    return ret;
    
}
