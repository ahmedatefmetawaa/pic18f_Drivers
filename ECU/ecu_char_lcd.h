
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

 
#ifndef ECU_CHAR_LCD_H
#define	ECU_CHAR_LCD_H
/*section : includes*/
#include "ecu_char_lcd_cfg.h"
#include "../../MCAL_layer/GPIO/hal_GPIO.h"
#define _XTAL_FREQ  8000000
/*section : macro declerations*/
#define _lcd_clear                          0x01
#define _lcd_return_home                    0x02
#define _lcd_entry_mode                     0x06
#define _cursor_off_display_on              0x0C
#define _cursor_off_display_off             0x08
#define _cursor_on_blink_on                 0x0F
#define _cursor_on_blink_off                0x0E
#define _lcd_display_shift_right            0x1C
#define _lcd_display_shift_left             0x18
#define _lcd_8bit_mode_2_line               0x38
#define _lcd_4bit_mode_2_line               0x28
#define _lcd_cgram_start                    0x40
#define _lcd_ddram_start                    0x80 

#define row1 1
#define row2 2
#define row3 3
#define row4 4
/*section : macro functions declerations */

/*section : data types declerations*/
typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t data[4];
}char_lcd_4bit;

typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t data[8];
}char_lcd_8bit;
/*section : functions declerations*/
Std_ReturnType lcd_4bit_initialize(const char_lcd_4bit *lcd);
Std_ReturnType lcd_4bit_send_command(const char_lcd_4bit *lcd , uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const char_lcd_4bit *lcd , uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const char_lcd_4bit *lcd ,uint8 row,uint8 column ,uint8 data);
Std_ReturnType lcd_4bit_send_string_data(const char_lcd_4bit *lcd , uint8 *str);
Std_ReturnType lcd_4bit_send_string_data_pos(const char_lcd_4bit *lcd ,uint8 row,uint8 column ,uint8 *str);
Std_ReturnType lcd_4bit_custom_char(const char_lcd_4bit *lcd ,uint8 row,uint8 column ,const uint8 _char[] 
                                                                                          ,uint8 mem_pos );
Std_ReturnType lcd_8bit_initialize(const char_lcd_8bit *lcd);
Std_ReturnType lcd_8bit_send_command(const char_lcd_8bit *lcd , uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const char_lcd_8bit *lcd , uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const char_lcd_8bit *lcd ,uint8 row,uint8 column ,uint8 data);
Std_ReturnType lcd_8bit_send_string_data(const char_lcd_8bit *lcd , uint8 *str);
Std_ReturnType lcd_8bit_send_string_data_pos(const char_lcd_8bit *lcd ,uint8 row,uint8 column ,uint8 *str);
Std_ReturnType lcd_8bit_custom_char(const char_lcd_8bit *lcd ,uint8 row,uint8 column ,const uint8 _char[] 
                                                                                          ,uint8 mem_pos );

Std_ReturnType convert_byte_to_string (uint8 value , uint8 *str);
Std_ReturnType convert_short_to_string (uint16 value , uint8 *str);
Std_ReturnType convert_int_to_string (uint32 value , uint8 *str);
#endif	/* ECU_CHAR_LCD_H */

