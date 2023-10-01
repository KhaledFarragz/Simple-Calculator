/* 
 * File:   application.c
 * Author: Khaled_farrag
 *
 * Created on July 4, 2023, 12:50 AM
 */

#include "application.h"


  

int main() {
     
uint8 KeypadValue = '\0';
uint8 FirstNumber[6];
uint8 SecondNumber[6];
uint32 number1 = 0, number2 = 0;
uint8 operation = 0;
uint32 result[8];
uint8 counter = 0;


    application_intialize();
    
    /*  Start message   */
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 3, "Simple Calculator");
     ret = lcd_4bit_send_string_pos(&lcd_1, 2, 7, "Made By");
        ret = lcd_4bit_send_string_pos(&lcd_1, 3, 3, "Eng. Khaled Farrag");
    __delay_ms(2000);
    ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    
         while(1)
        {   
        KeypadValue = '\0';
            
        clearDataArrays(FirstNumber, 6);
        clearDataArrays(SecondNumber, 6);
            
        operation = 0;
        counter = 0;
          
         while(1){
 
            do{
                ret = keypad_get_value(&keypad_1, &KeypadValue);
            }while(KeypadValue == '\0');
            
            if(KeypadValue == '/' || KeypadValue == '*' || KeypadValue == '-' || KeypadValue == '+'){
                operation = KeypadValue;
                ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, counter+1, KeypadValue);
                KeypadValue = '\0';
                break;
            }
            FirstNumber[counter] = KeypadValue;
            counter++;
            ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, counter, KeypadValue);
            KeypadValue = '\0';
        }
       
        uint8 counter2 = counter + 1;
        uint8 counter3 = 0;
        while(1){
            do{
                ret = keypad_get_value(&keypad_1, &KeypadValue);
               // __delay_ms(100);
            }while(KeypadValue == '\0');
            
            if(KeypadValue == '='){
                ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, counter2+1, KeypadValue);
                KeypadValue = '\0';
                break;
            }
            
            SecondNumber[counter3] = KeypadValue;
            counter2++;
            counter3++;
            ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, counter2, KeypadValue);
            KeypadValue = '\0';
        }
        
         /*  Convert number one and number two from string to numbers    */
        number1 = Number_return(FirstNumber, counter);
        number2 = Number_return(SecondNumber, counter3);
        
        /*  Operation   */
        switch(operation){
            case '+' : 
                ret = convert_uint32_to_string((number1 + number2), result);
                 break;
            case '-' : 
                ret = convert_uint32_to_string((number1 - number2), result);
                break;
            case '*' : 
                ret = convert_uint32_to_string((number1 * number2), result);
                break;    
            case '/' : 
                ret = convert_uint32_to_string((number1 / number2), result);
                break;
  
        }
        
        ret = lcd_4bit_send_string_pos(&lcd_1, 1, counter2+2, result);
        
        __delay_ms(3000);
		ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
           
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
     ecu_layer_intialize();
}

