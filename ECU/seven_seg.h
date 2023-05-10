
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
  
#ifndef SEVEN_SEG_H
#define	SEVEN_SEG_H
/*section : includes*/
#include "seven_seg_cfg.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
/*section : macro declerations*/
#define segment_pin0  0
#define segment_pin1  1
#define segment_pin2  2
#define segment_pin3  3
/*section : macro functions declerations */

/*section : data types declerations*/
typedef enum {
    segment_common_anode,
    segment_common_cathode
}segment_type_t;

typedef struct {
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;
/*section : functions declerations*/
Std_ReturnType SegmentInitialize (const segment_t *seg);
Std_ReturnType SegmentWriteNumber (const segment_t *seg , uint8 number);

#endif	/* SEVEN_SEG_H */

