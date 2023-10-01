/* 
 * File:   ecu_chr_lcd.c
 * Author: Blu-Ray
 *
 * Created on September 29, 2023, 1:36 PM
 */
#include "ecu_chr_lcd.h"

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command);
static Std_ReturnType lcd_4bits_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bits_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 colomn);

static Std_ReturnType lcd_8bits_send_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bits_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 colomn);


Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 l_data_pins_counter = ZERO_INIT ;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));  
        for(l_data_pins_counter = ZERO_INIT;l_data_pins_counter < 4;l_data_pins_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80); 
     }
    return ret;
}
 
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
         lcd_send_4bits(lcd, command >> 4);
         lcd_4bits_send_enable_signal(lcd);
         lcd_send_4bits(lcd, command);
         lcd_4bits_send_enable_signal(lcd);
     }
    return ret;
}
 
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
         lcd_send_4bits(lcd, data >> 4);
         lcd_4bits_send_enable_signal(lcd);
         lcd_send_4bits(lcd, data);
         lcd_4bits_send_enable_signal(lcd);
     }
    return ret;
}
 
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 colomn, uint8 data){
    Std_ReturnType ret = E_OK;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
        ret = lcd_4bits_set_cursor(lcd, row, colomn);
        ret = lcd_4bit_send_char_data(lcd, data);
     }
    return ret;
}
 
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
     if(NULL == lcd || NULL == str)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         while(*str)
          {
             ret = lcd_4bit_send_char_data(lcd,*str++);  
          }
     }
    return ret;
}
 
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 colomn, uint8 *str){
    Std_ReturnType ret = E_OK;
     if(NULL == lcd || NULL == str)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         lcd_4bits_set_cursor(lcd, row, colomn);
         while(*str){
         lcd_4bit_send_char_data(lcd, *str++);
         }
     }
    return ret;
}
 
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 colomn,
                                         const uint8 _chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
     uint8 lcd_counter = ZERO_INIT ;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
         for(lcd_counter = ZERO_INIT;lcd_counter <= 7 ;lcd_counter++)
         {
             ret = lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
         }
         ret = lcd_4bit_send_char_data_pos(lcd, row, colomn, mem_pos);
     }
    return ret;
}
 

Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd){
     Std_ReturnType ret = E_OK;
    uint8 l_data_pins_counter = ZERO_INIT ;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
        ret = gpio_pin_intialize(&(lcd->lcd_en)); 
        ret = gpio_pin_intialize(&(lcd->lcd_rs)); 
        for(l_data_pins_counter = 0;l_data_pins_counter < 8;l_data_pins_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, 0x80);
     }
    return ret;
}
 
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter =ZERO_INIT ;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
         for(l_pin_counter = 0;l_pin_counter < 8;l_pin_counter++)
         {
             ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), (command >> l_pin_counter) & 0x01);
         }
          ret = lcd_8bits_send_enable_signal(lcd);  
     }
    return ret;
}
 
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
     uint8 l_pin_counter = ZERO_INIT ;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
         for(l_pin_counter = 0;l_pin_counter < 8;l_pin_counter++)
         {
             ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), (data >> l_pin_counter) & 0x01);
         }
          ret = lcd_8bits_send_enable_signal(lcd);  
     }
    return ret;
}
 
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 colomn, uint8 data){
    Std_ReturnType ret = E_OK;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         ret = lcd_8bits_set_cursor(lcd, row, colomn);
         ret = lcd_8bit_send_char_data(lcd, data);
     }
    return ret;
}
 
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
     uint8 l_pin_counter = ZERO_INIT, l_char_counter = ZERO_INIT;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
          while(*str)
          {
             ret = lcd_8bit_send_char_data(lcd,*str++);  
          }
     }
    return ret;
}
 
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 colomn, uint8 *str){
    Std_ReturnType ret = E_OK;
     if(NULL == lcd || NULL == str)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         lcd_8bit_send_char_data_pos(lcd, row, colomn,*str);
         lcd_8bit_send_string(lcd, ++str);
     }
    return ret;
}
 
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 colomn,
                                         const uint8 _chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT ;
     if(NULL == lcd)
     {
        ret = E_NOT_OK ;
     }
     else
     {
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
         for(lcd_counter = ZERO_INIT;lcd_counter <= 7 ;lcd_counter++)
         {
             ret = lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
         }
         ret = lcd_8bit_send_char_data_pos(lcd, row, colomn, mem_pos);
     }
    return ret;
}

Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str){
   Std_ReturnType ret = E_OK;
     if(NULL == str)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         memset(str, '\0', 4);
         sprintf(str, "%i", value);
     }
    return ret;
}
 
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret = E_OK;
     if(NULL == str)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         memset(str, '\0', 6);
         sprintf(str, "%i", value);
     }
    return ret;
}
 
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret = E_OK;
     if(NULL == str)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         memset(str, '\0', 11);
         sprintf(str, "%i", value);
     }
    return ret;
}

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (_data_command >> 0) & (uint8)0x01 );
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (_data_command >> 1) & (uint8)0x01 );
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (_data_command >> 2) & (uint8)0x01 );
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (_data_command >> 3) & (uint8)0x01 );
    }
    return ret;
}

static Std_ReturnType lcd_4bits_send_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_ms(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
      //   ret = lcd_4bit_initialize(&lcd);
    }
    return ret;
}

static Std_ReturnType lcd_8bits_send_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
     //   ret = lcd_8bit_initialize(&lcd);
    }
    return ret;
}

static Std_ReturnType lcd_8bits_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 colomn){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        colomn--;
        switch(row)
        {  
            case ROW1 :  ret = lcd_8bit_send_command(lcd, (0x80) + colomn);break;
            case ROW2 :  ret = lcd_8bit_send_command(lcd, (0xC0) + colomn);break;
            case ROW3 :  ret = lcd_8bit_send_command(lcd, (0x94) + colomn);break;
            case ROW4 :  ret = lcd_8bit_send_command(lcd, (0xD4) + colomn);break;
            default   : ;
        }
    }
    return ret;
}

static Std_ReturnType lcd_4bits_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 colomn){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        colomn--;
        switch(row)
        {  
            case ROW1 :  ret = lcd_4bit_send_command(lcd, (0x80) + colomn);break;
            case ROW2 :  ret = lcd_4bit_send_command(lcd, (0xC0) + colomn);break;
            case ROW3 :  ret = lcd_4bit_send_command(lcd, (0x94) + colomn);break;
            case ROW4 :  ret = lcd_4bit_send_command(lcd, (0xD4) + colomn);break;
            default   : ;
        }
    }
    return ret;
}
/*Std_ReturnType LCD_Write_Num (const chr_lcd_4bit_t *lcd, uint32 Num)
{
	uint8 Rem , index = 0 ;
	uint8 arr[20];

	if (Num==0)
	{
		arr[index]='0';
		index++;
	}


	while (Num!=0)
	{
		Rem = Num % 10 ;
		arr[index]= Rem + '0' ;
		index++;
		Num /= 10 ;
	}
	arr[index]='\0';
	//reverse (arr , index );
	lcd_4bit_send_string(&lcd, &arr); //(&lcd , x_pos ,  y_pos,  arr ) ;
    return 0 ;
}

static Std_ReturnType reverse (uint8 * ptr , uint8 element )
{
	uint8 start =0 ;
	uint8 end = element - 1 ;

	while (start < end)
	{

		//Swap
		 uint32 temp = ptr[start];
		 ptr[start] = ptr[end];
		 ptr[end] = temp;

	start++;
	end--;
	}
    return 0 ;
}
*/


/*  Implement the clearDataArrays function   */
void clearDataArrays(uint8 arr[], uint8 size) {
    for (uint8 i = 0; i < size; i++) {
        arr[i] = '\0';
    }
}

/*  Implement the Number_return function  */
uint16 Number_return(uint8 arr[], uint8 count){
    uint16 num = 0;
    for(int i = 0; i < count; i++){
        num = num * 10 + (arr[i] - '0'); // Convert character to integer
    }
    return num;
}

