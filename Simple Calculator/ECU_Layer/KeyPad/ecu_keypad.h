/* 
 * File:   ecu_keypad.h
 * Author: Blu-Ray
 *
 * Created on September 23, 2023, 1:48 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*section : includes*/
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/*section : Macro declarations*/
#define ECU_KEYPAD_ROWS     4
#define ECU_KEYPAD_COLOMNS  4


/*section : Macro Functions Declarations*/

/*section : Data Type Declarations*/
typedef struct {
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_colomns_pins[ECU_KEYPAD_COLOMNS];     
}keypad_t;
/*section : Functions Declarations*/
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *keypad_value);

#endif	/* ECU_KEYPAD_H */

