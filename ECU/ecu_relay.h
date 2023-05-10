
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H
/*section : includes*/
#include "ecu_relay_cfg.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"

/*section : macro declerations*/
#define relay_on_status    0X01U
#define relay_off_status   0X00U
/*section : macro functions declerations */

/*section : data types declerations*/
typedef struct {
    uint8 relay_port     : 4;
    uint8 relay_pin      : 3;
    uint8 relay_status   : 1;
}relay_t;
/*section : functions declerations*/
Std_ReturnType RelayInitialize (const relay_t *relay);
Std_ReturnType Relay_turn_on (const relay_t *relay);
Std_ReturnType Relay_turn_off (const relay_t *relay);
#endif	/* ECU_RELAY_H */

