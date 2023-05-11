/* 
 * File:   application.c
 * Author:ENG \ Ahmed Atef
 * 
 * Created on January 1, 2023, 3:26 PM
 */

#include"application.h"
//#include "ECU_Layer/7_segment/seven_seg.h"

void application (void);

keypad_t keypad = 
{
    .keypad_row_pins[0].port =PORTA_INDEX ,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic =GPIO_LOW ,
    .keypad_row_pins[1].port =PORTA_INDEX ,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic =GPIO_LOW ,
    .keypad_row_pins[2].port =PORTA_INDEX ,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic =GPIO_LOW ,
    .keypad_row_pins[3].port =PORTA_INDEX ,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic =GPIO_LOW ,
    
    .keypad_columns_pins[0].port = PORTA_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN4,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    .keypad_columns_pins[1].port = PORTA_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN5,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    .keypad_columns_pins[2].port = PORTA_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN6,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    .keypad_columns_pins[3].port = PORTA_INDEX,
    .keypad_columns_pins[3].pin = GPIO_PIN7,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].logic = GPIO_LOW,

};

char_lcd_8bit lcd_2 = 
{
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN6,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN7,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .data[0].port = PORTD_INDEX,
    .data[0].pin = GPIO_PIN0,
    .data[0].direction = GPIO_DIRECTION_OUTPUT,
    .data[0].logic = GPIO_LOW,
    .data[1].port = PORTD_INDEX,
    .data[1].pin = GPIO_PIN1,
    .data[1].direction = GPIO_DIRECTION_OUTPUT,
    .data[1].logic = GPIO_LOW,
    .data[2].port = PORTD_INDEX,
    .data[2].pin = GPIO_PIN2,
    .data[2].direction = GPIO_DIRECTION_OUTPUT,
    .data[2].logic = GPIO_LOW,
    .data[3].port = PORTD_INDEX,
    .data[3].pin = GPIO_PIN3,
    .data[3].direction = GPIO_DIRECTION_OUTPUT,
    .data[3].logic = GPIO_LOW,
    .data[4].port = PORTD_INDEX,
    .data[4].pin = GPIO_PIN4,
    .data[4].direction = GPIO_DIRECTION_OUTPUT,
    .data[4].logic = GPIO_LOW,
    .data[5].port = PORTD_INDEX,
    .data[5].pin = GPIO_PIN5,
    .data[5].direction = GPIO_DIRECTION_OUTPUT,
    .data[5].logic = GPIO_LOW,
    .data[6].port = PORTD_INDEX,
    .data[6].pin = GPIO_PIN6,
    .data[6].direction = GPIO_DIRECTION_OUTPUT,
    .data[6].logic = GPIO_LOW,
    .data[7].port = PORTD_INDEX,
    .data[7].pin = GPIO_PIN7,
    .data[7].direction = GPIO_DIRECTION_OUTPUT,
    .data[7].logic = GPIO_LOW,
};
#define max_tries  3
uint8 password[4]= {0};
uint8 input[4] = {0}; // Initialize input array to 0
uint8 counter = 0; 
uint8 keypad_number = 0;
uint8 tries = max_tries;
uint8 flag=0;


int main()
{ 
    Std_ReturnType ret = E_NOT_OK;
    application();
    ret = lcd_8bit_send_string_data_pos(&lcd_2 ,2,5,"Hello User" );
    __delay_ms(2000);
    ret = lcd_8bit_send_command(&lcd_2 ,_lcd_clear );
    for(counter=0;counter<4;counter++)
    {
        ret = lcd_8bit_send_string_data_pos(&lcd_2 ,1,1,"Set Password:" );
        do{
            ret = keypad_get_value(&keypad ,&keypad_number);
        }while(keypad_number == 0);
        
        input[counter] = keypad_number;
        ret = lcd_8bit_send_char_data_pos(&lcd_2 ,1,14+counter,keypad_number );
       __delay_ms(500);
        ret = lcd_8bit_send_char_data_pos(&lcd_2 ,1,14+counter,'*' );
        keypad_number = 0;
    }

    while(flag == 0)
    { 
        ret = lcd_8bit_send_command(&lcd_2 ,_lcd_clear );
        ret = lcd_8bit_send_string_data_pos(&lcd_2 ,1,1,"Check Password:" );
        for(counter=0;counter<4;counter++)
        {
            do{
            ret = keypad_get_value(&keypad ,&keypad_number);
            }while(keypad_number == 0);
        
            password[counter] = keypad_number;
            ret = lcd_8bit_send_char_data_pos(&lcd_2 ,1,16+counter,keypad_number );
            __delay_ms(500);
            ret = lcd_8bit_send_char_data_pos(&lcd_2 ,1,16+counter,'*' );
            keypad_number = 0;
        }
        if (memcmp(password, input, sizeof(password)) == 0)
        {
            ret = lcd_8bit_send_command(&lcd_2 ,_lcd_clear );    
            ret = lcd_8bit_send_string_data_pos(&lcd_2 ,1,1,"Correct Password");
            __delay_ms(3000);
            ret = lcd_8bit_send_string_data_pos(&lcd_2 ,1,1,"Safe Lock");
            __delay_ms(3000);
            flag = 1;
        }
        else
        {
            tries--;
            ret = lcd_8bit_send_command(&lcd_2 ,_lcd_clear );
            ret = lcd_8bit_send_string_data_pos(&lcd_2 ,1,1,"Wrong Password");
            __delay_ms(3000);
            ret = lcd_8bit_send_string_data_pos(&lcd_2 ,2,1,"Tries Left");
            __delay_ms(3000);
            ret = lcd_8bit_send_char_data_pos(&lcd_2 ,2,12,tries );
            __delay_ms(3000);
            if(tries == 0)
            {
                ret = lcd_8bit_send_command(&lcd_2 ,_lcd_clear );
                ret = lcd_8bit_send_string_data_pos(&lcd_2 ,1,1,"attempts over");
                __delay_ms(3000);
                flag = 1;
            }
        }
  
}
    
    return (0);
}


void application (void)
{
   Std_ReturnType ret = E_NOT_OK;
   ret = keypad_initialize(&keypad);
   ret = lcd_8bit_initialize(&lcd_2);
}