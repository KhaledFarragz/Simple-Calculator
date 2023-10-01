/* 
 * File:   ecu_keypad.c
 * Author: Blu-Ray
 *
 * Created on September 23, 2023, 1:48 PM
 */
#include "ecu_keypad.h"

static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLOMNS] = {
                                                                        {'7','8','9','/'},
                                                                        {'4','5','6','*'},
                                                                        {'1','2','3','-'},
                                                                        {'#','0','=','+'}
                                                                    };   

 
/**
 * @brief Initialize the keypad assigned pins
 * @param _keypad_obj pointer to the keypad configurations
 * @return status of the function 
 *          (E_OK) : the function  done successfully 
 *          (E_NOT_OK) : The function has issue performing this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj){
     Std_ReturnType ret = E_OK;
     uint8 rows_counter = ZERO_INIT, coloumns_counter = ZERO_INIT;
     if(NULL == _keypad_obj)
     {
        ret = E_NOT_OK ;
     }
     else
     {
         for(rows_counter = ZERO_INIT;rows_counter < ECU_KEYPAD_ROWS;rows_counter++)
         {
              gpio_pin_intialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
         }
         
         for(coloumns_counter = ZERO_INIT;coloumns_counter < ECU_KEYPAD_COLOMNS;coloumns_counter++)
         {
              gpio_pin_intialize(&(_keypad_obj->keypad_colomns_pins[coloumns_counter]));
         }
        
     }
    return ret;
}
/**
 * 
 * @param _keypad_obj
 * @param value
 * @return status of the function 
 *          (E_OK) : the function  done successfully 
 *          (E_NOT_OK) : The function has issue performing this action
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *keypad_value){
    Std_ReturnType ret = E_OK;
    uint8 l_rows_counter = ZERO_INIT, l_coloumns_counter = ZERO_INIT, l_counter = ZERO_INIT;
    uint8 column_logic = ZERO_INIT;
     if((NULL == _keypad_obj) || (NULL == keypad_value))
     {
        ret = E_NOT_OK ;
     }
     else
     {
          for(l_rows_counter = ZERO_INIT;l_rows_counter < ECU_KEYPAD_ROWS;l_rows_counter++)
         {
              for(l_counter = ZERO_INIT;l_counter < ECU_KEYPAD_ROWS;l_counter++)
              {
                ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]), GPIO_LOW);
              }
                ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counter]), GPIO_HIGH);
              __delay_ms(10);
              for(l_coloumns_counter = ZERO_INIT;l_coloumns_counter < ECU_KEYPAD_COLOMNS;l_coloumns_counter++)
              {
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_colomns_pins[l_coloumns_counter]), &column_logic);
                 if(GPIO_HIGH == column_logic)
                 {
                    *keypad_value = btn_values[l_rows_counter][l_coloumns_counter]  ;
                 }
              } 
         }
          __delay_ms(150);
     }
    return ret;
}