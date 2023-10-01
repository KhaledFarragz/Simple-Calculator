/* 
 * File:   application.h
 * Author: Khaled_Farrag
 *
 * Created on September 19, 2023, 2:11 PM
 */


//#define HWREG8(_x)   (*((volatile unsigned char *)(_x)))
#ifndef APPLICATION_H
#define	APPLICATION_H

/*section : includes*/
#include "ECU_Layer/ecu_layer_init.h"

/*section : Macro declarations*/
Std_ReturnType ret = E_NOT_OK ;
/*section : Macro Functions Declarations*/

/*section : Data Type Declarations*/
extern keypad_t keypad_1;
extern led_t led1;
extern chr_lcd_8bit_t   lcd_2;
extern chr_lcd_4bit_t   lcd_1;
/*section : Functions Declarations*/
void application_intialize(void);
#define _XTAL_FREQ 4000000UL
#endif	/* APPLICATION_H */

