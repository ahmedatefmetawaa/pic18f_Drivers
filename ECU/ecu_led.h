 /* 
 * File:   application.c
 * Author: Ahmed Atef
 *
 * Created on January 1, 2023, 3:26 PM
 */
#ifndef ECU_LED_H
#define	ECU_LED_H

/*section : includes*/
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
#include "ecu_led_cfg.h"
/*section : macro declerations*/

/*section : macro functions declerations */

/*section : data types declerations*/
typedef enum {
    LEDOFF,
    LEDON
}led_status;

typedef struct{
    uint8 port_name :4;
    uint8 pin :3;
    uint8 led_status :1;
}led_t; 

/*section : functions declerations*/

Std_ReturnType led_initialize (const led_t *led);
Std_ReturnType led_on (const led_t *led);
Std_ReturnType led_off (const led_t *led);
Std_ReturnType led_toggle (const led_t *led);

#endif	/* XC_HEADER_TEMPLATE_H */

