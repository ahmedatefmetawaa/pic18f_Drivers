/*section : includes*/
#include "ecu_char_lcd.h"

static Std_ReturnType lcd_send_4bits (const char_lcd_4bit *lcd , uint8 _data_command);
static Std_ReturnType lcd_4bit_send_enable (const char_lcd_4bit *lcd);
static Std_ReturnType lcd_8bit_send_enable (const char_lcd_8bit *lcd);
static Std_ReturnType lcd_8bit_set_cursor (const char_lcd_8bit *lcd , uint8 row ,uint8 column );
static Std_ReturnType lcd_4bit_set_cursor (const char_lcd_4bit *lcd , uint8 row ,uint8 column );


Std_ReturnType lcd_4bit_initialize(const char_lcd_4bit *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_data_counter =0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_intialize (&(lcd->lcd_rs));
        gpio_pin_intialize(&(lcd->lcd_en));
        for(lcd_data_counter =0;lcd_data_counter <4;lcd_data_counter++){
            gpio_pin_intialize(&(lcd->data[lcd_data_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command (lcd , _lcd_8bit_mode_2_line);
        __delay_ms(5);
        ret = lcd_4bit_send_command (lcd , _lcd_8bit_mode_2_line);
        __delay_us(150);
        ret = lcd_4bit_send_command (lcd , _lcd_8bit_mode_2_line);
        ret = lcd_4bit_send_command (lcd , _lcd_clear);
        ret = lcd_4bit_send_command (lcd , _lcd_return_home);
        ret = lcd_4bit_send_command (lcd , _lcd_entry_mode);
        ret = lcd_4bit_send_command (lcd , _cursor_off_display_on);
        ret = lcd_4bit_send_command (lcd , _lcd_4bit_mode_2_line);
        ret = lcd_4bit_send_command (lcd , 0x80);
    }   
    return ret;
}
Std_ReturnType lcd_4bit_send_command(const char_lcd_4bit *lcd , uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW );
        ret = lcd_send_4bits(lcd ,command >>4 );
        ret = lcd_4bit_send_enable(lcd);
        ret = lcd_send_4bits(lcd ,command );
        ret = lcd_4bit_send_enable(lcd);
    }
    return ret;
    
}
Std_ReturnType lcd_4bit_send_char_data(const char_lcd_4bit *lcd , uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH );
        ret = lcd_send_4bits(lcd ,data >>4 );
        ret = lcd_4bit_send_enable(lcd);
        ret = lcd_send_4bits(lcd ,data );
        ret = lcd_4bit_send_enable(lcd);
        
    }
    return ret;
    
}
Std_ReturnType lcd_4bit_send_char_data_pos(const char_lcd_4bit *lcd ,uint8 row,uint8 column ,uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd , row , column);
        ret = lcd_4bit_send_char_data(lcd , data);
    }
    return ret;
    
}
Std_ReturnType lcd_4bit_send_string_data(const char_lcd_4bit *lcd , uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
           while (*str){
            ret = lcd_4bit_send_char_data (lcd , *str++);
        }
    }
    return ret;
    
}
Std_ReturnType lcd_4bit_send_string_data_pos(const char_lcd_4bit *lcd ,uint8 row,uint8 column ,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
         ret = lcd_4bit_set_cursor(lcd , row ,column);
            while (*str){
            ret = lcd_4bit_send_char_data (lcd , *str++);
        }
    }
    return ret;
    
}
Std_ReturnType lcd_4bit_custom_char(const char_lcd_4bit *lcd ,uint8 row,uint8 column ,const uint8 _char[] 
                                                                                          ,uint8 mem_pos )
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_send_command(lcd , (_lcd_cgram_start +(mem_pos * 8)));
        for (lcd_counter = 0;lcd_counter <=7;lcd_counter++){
        ret = lcd_4bit_send_char_data(lcd ,_char[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd , row , column ,mem_pos );
    }
    return ret;   
}


Std_ReturnType lcd_8bit_initialize(const char_lcd_8bit *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_data_counter =0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_intialize (&(lcd->lcd_rs));
        gpio_pin_intialize(&(lcd->lcd_en));
        for(lcd_data_counter =0;lcd_data_counter <8;lcd_data_counter++){
            gpio_pin_intialize(&(lcd->data[lcd_data_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command (lcd , _lcd_8bit_mode_2_line);
        __delay_ms(5);
        ret = lcd_8bit_send_command (lcd , _lcd_8bit_mode_2_line);
        __delay_us(150);
        ret = lcd_8bit_send_command (lcd , _lcd_8bit_mode_2_line);
        ret = lcd_8bit_send_command (lcd , _lcd_clear);
        ret = lcd_8bit_send_command (lcd , _lcd_return_home);
        ret = lcd_8bit_send_command (lcd , _lcd_entry_mode);
        ret = lcd_8bit_send_command (lcd , _cursor_off_display_on);
        ret = lcd_8bit_send_command (lcd , _lcd_8bit_mode_2_line);
        ret = lcd_8bit_send_command (lcd , 0x80);
        

    }
         
    return ret;
}
    

Std_ReturnType lcd_8bit_send_command(const char_lcd_8bit *lcd , uint8 command)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter =0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW );
        for(l_pin_counter=0; l_pin_counter<8; ++l_pin_counter)
        {
          ret = gpio_pin_write_logic (&(lcd->data[l_pin_counter]) , (command >>l_pin_counter) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_data(const char_lcd_8bit *lcd , uint8 data)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter =0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH );
        for(l_pin_counter=0; l_pin_counter<8;++l_pin_counter)
        {
          ret = gpio_pin_write_logic (&(lcd->data[l_pin_counter]) , (data >>l_pin_counter) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_data_pos(const char_lcd_8bit *lcd ,uint8 row,uint8 column ,uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd , row ,column);
        ret = lcd_8bit_send_char_data(lcd , data);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_string_data(const char_lcd_8bit *lcd , uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == str){
        ret = E_NOT_OK;
    }
    else{
        while (*str){
            ret = lcd_8bit_send_char_data (lcd , *str++);
        }
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_string_data_pos(const char_lcd_8bit *lcd ,uint8 row,uint8 column ,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == str){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd , row ,column);
            while (*str){
            ret = lcd_8bit_send_char_data (lcd , *str++);
        }
    }
    return ret;
}
Std_ReturnType lcd_8bit_custom_char(const char_lcd_8bit *lcd ,uint8 row,uint8 column ,const uint8 _char[] 
                                                                                          ,uint8 mem_pos )
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_send_command(lcd , (_lcd_cgram_start +(mem_pos * 8)));
        for (lcd_counter = 0;lcd_counter <=7;lcd_counter++){
        ret = lcd_8bit_send_char_data(lcd ,_char[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd , row , column ,mem_pos );
    }
    return ret;
}



static Std_ReturnType lcd_send_4bits (const char_lcd_4bit *lcd , uint8 _data_command)
{
    Std_ReturnType ret = E_OK;
    gpio_pin_write_logic (&(lcd->data[0]) , (_data_command >>0) & (uint8)0x01);
    gpio_pin_write_logic (&(lcd->data[1]) , (_data_command >>1) & (uint8)0x01);
    gpio_pin_write_logic (&(lcd->data[2]) , (_data_command >>2) & (uint8)0x01);
    gpio_pin_write_logic (&(lcd->data[3]) , (_data_command >>3) & (uint8)0x01);
    return ret;
}

static Std_ReturnType lcd_4bit_send_enable (const char_lcd_4bit *lcd)
{
    Std_ReturnType ret = E_OK;
    gpio_pin_write_logic (&(lcd->lcd_en) , GPIO_HIGH);
    __delay_us(5);
    gpio_pin_write_logic (&(lcd->lcd_en) , GPIO_LOW);
    return ret;
}

static Std_ReturnType lcd_8bit_send_enable (const char_lcd_8bit *lcd)
{
    Std_ReturnType ret = E_OK;
    gpio_pin_write_logic (&(lcd->lcd_en) , GPIO_HIGH);
    __delay_us(5);
    gpio_pin_write_logic (&(lcd->lcd_en) , GPIO_LOW);
    return ret;
}


static Std_ReturnType lcd_8bit_set_cursor (const char_lcd_8bit *lcd , uint8 row ,uint8 column )
{
    Std_ReturnType ret = E_OK;
    column--;
    switch(row){
        case row1 :ret = lcd_8bit_send_command (lcd , (0x80+column));break;
        case row2 :ret = lcd_8bit_send_command (lcd , (0xC0+column));break;
        case row3 :ret = lcd_8bit_send_command (lcd , (0x94+column));break;
        case row4 :ret = lcd_8bit_send_command (lcd , (0xD4+column));break;
        default : ;
    }
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor (const char_lcd_4bit *lcd , uint8 row ,uint8 column )
{
    Std_ReturnType ret = E_OK;
    column--;
    switch(row){
        case row1 :ret = lcd_4bit_send_command (lcd , (0x80+column));break;
        case row2 :ret = lcd_4bit_send_command (lcd , (0xC0+column));break;
        case row3 :ret = lcd_4bit_send_command (lcd , (0x94+column));break;
        case row4 :ret = lcd_4bit_send_command (lcd , (0xD4+column));break;
        default : ;
    }
    return ret;
}

Std_ReturnType convert_byte_to_string (uint8 value , uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str , '\0' , 4);
        sprintf(str , "%i" , value);
        
    }
    return ret;
}
Std_ReturnType convert_short_to_string (uint16 value , uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str , '\0' , 6);
        sprintf(str , "%i" , value);
        
    }
    return ret;
    
}
Std_ReturnType convert_int_to_string (uint32 value , uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str , '\0' , 11);
        sprintf(str , "%i" , value);
        
    }
    return ret;
    
}