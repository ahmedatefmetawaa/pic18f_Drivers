
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */


#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H
/*section : includes*/
#include "pic18f4620.h"
#include "../MCAL_std_types.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
#define _XTAL_FREQ 8000000
#include <xc.h>
/*section : macro declerations*/
#define ACCESS_FLASH_MEMORY                  1
#define ACCESS_EEPROM_MEMORY                 0
#define ACCESS_CONFIG_REGESTERS              1
#define ACCESS_FLASH_EEPROM_MEMORY           0
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM      1 
#define INHIBIT_WRITE_CYCLES_FLASH_EEPROM    0
#define INITIATE_DATA_EEPROM_WRITE_ERASE     1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED    0
#define INITIATE_DATA_EEPROM_READ            1
/*section : macro functions declerations */

/*section : data types declerations*/

/*section : functions declerations*/
Std_ReturnType DATA_EEPROM_WRITE_BYTE (uint16 bAdd , uint16 bData);
Std_ReturnType DATA_EEPROM_READ_BYTE  (uint16 bAdd , uint16 *bData);

#endif	/* HAL_EEPROM_H */

