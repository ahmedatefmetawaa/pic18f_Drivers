/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
#include "hal_eeprom.h"

Std_ReturnType DATA_EEPROM_WRITE_BYTE (uint16 bAdd , uint16 bData)
{
    Std_ReturnType ret = E_NOT_OK;
    /*read the intrrupt status "enabled or disabled" */
    uint8 GlobalInterruptStatus = INTCONbits.GIE;
    /*update the address registers */
    EEADRH = (uint8)((bAdd >> 8)&0x03);
    EEADR = (uint8)(bAdd &0xFF);
    /*update the data registers */
    EEDATA = bData;
    /*select access data eeprom memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    /*allow write cycles to flash memory / eeprom */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /*disable all interrupts"global interrupts" */
    INTERRUPT_GlobalInterruptDisable();
    /*write the required sequence 0x55->0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /*initiates a data eeprom erase / write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /*wait for write to complete*/
    while(EECON1bits.WR);
    /*inhibits write cycles to flash memory / data eeprom */
    EECON1bits.WREN = INHIBIT_WRITE_CYCLES_FLASH_EEPROM ;
    /*restore the interrupts status "enabled or disabled" */ 
    INTCONbits.GIE = GlobalInterruptStatus;
    return ret;
}

Std_ReturnType DATA_EEPROM_READ_BYTE  (uint16 bAdd , uint16 *bData)
{
    Std_ReturnType ret = E_OK;
    if(NULL == bData){
        ret = E_NOT_OK;
    }
    else {
    /*update the address registers*/
    EEADRH = (uint8)((bAdd >> 8)&0x03);
    EEADR = (uint8)(bAdd &0xFF);
    /*select access data eeprom memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;    
    /*initiates a data eeprom read cycle */
    EECON1bits.RD =  INITIATE_DATA_EEPROM_READ ;
    NOP();
    NOP();
    /*return data*/
    *bData = EEDATA;
    }
    
    return ret;
}
