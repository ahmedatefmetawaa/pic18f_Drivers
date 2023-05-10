/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
#include "seven_seg.h"

Std_ReturnType SegmentInitialize (const segment_t *seg)
{
    Std_ReturnType ret = E_OK;
    if(NULL == seg){
         ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_intialize(&(seg->segment_pins[segment_pin0]));
        ret = gpio_pin_intialize(&(seg->segment_pins[segment_pin1]));
        ret = gpio_pin_intialize(&(seg->segment_pins[segment_pin2]));
        ret = gpio_pin_intialize(&(seg->segment_pins[segment_pin3]));
    }
    return ret;
}
Std_ReturnType SegmentWriteNumber (const segment_t *seg , uint8 number)
{
    Std_ReturnType ret = E_OK;
    if((NULL == seg) || (number > 9) ){
         ret = E_NOT_OK;
    }
    else {
        
       ret= gpio_pin_write_logic(&(seg->segment_pins[segment_pin0]), number & 0x01);
       ret= gpio_pin_write_logic(&(seg->segment_pins[segment_pin1]),(number>>1) & 0x01 );
       ret= gpio_pin_write_logic(&(seg->segment_pins[segment_pin2]),(number>>2) & 0x01 );
       ret= gpio_pin_write_logic(&(seg->segment_pins[segment_pin3]),(number>>3) & 0x01 );
    }
    return ret;
    
}
