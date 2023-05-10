
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
  
#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/*section : includes*/
#include "dc_motor_cfg.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"

/*section : macro declerations*/

#define dc_motor_on_status   0X01U
#define dc_motor_off_status  0X00U

/*section : macro functions declerations */

/*section : data types declerations*/



typedef struct {
    pin_config_t dc_motor[2];
}dc_motor_t;

/*section : functions declerations*/
Std_ReturnType motor_initialize (const dc_motor_t *motor );
Std_ReturnType motor_move_forward (const dc_motor_t *motor );
Std_ReturnType motor_move_backward (const dc_motor_t *motor );
Std_ReturnType motor_stop (const dc_motor_t *motor );
#endif	/* DC_MOTOR_H */

