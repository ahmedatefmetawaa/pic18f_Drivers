#include "dc_motor.h"


Std_ReturnType motor_initialize (const dc_motor_t *motor )
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == motor ){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_intialize(&(motor->dc_motor[0]));
        gpio_pin_intialize(&(motor->dc_motor[1]));
        
    }
}
Std_ReturnType motor_move_forward (const dc_motor_t *motor )
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == motor ){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(motor->dc_motor[0]) , GPIO_HIGH);
        gpio_pin_write_logic(&(motor->dc_motor[1]) , GPIO_LOW);
    }
    
}
Std_ReturnType motor_move_backward (const dc_motor_t *motor )
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == motor ){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(motor->dc_motor[0]) , GPIO_LOW);
        gpio_pin_write_logic(&(motor->dc_motor[1]) , GPIO_HIGH);
    }
    
}
Std_ReturnType motor_stop (const dc_motor_t *motor )
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == motor ){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(motor->dc_motor[0]) , GPIO_LOW);
        gpio_pin_write_logic(&(motor->dc_motor[1]) , GPIO_LOW);
    }
    
}
