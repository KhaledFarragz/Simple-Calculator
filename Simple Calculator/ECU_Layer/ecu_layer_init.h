/* 
 * File:   ecu_layer_init.h
 * Author: Blu-Ray
 *
 * Created on September 23, 2023, 8:20 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/*section : includes*/
#include "../MCAL_Layer/GPIO/hal_gpio.h"
#include "LED/ecu_led.h"
#include "button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "DC_MOTOR/ec_dc_motor.h"
#include "7_seg/ecu_seven_segment.h"
#include "KeyPad/ecu_keypad.h"
#include "Chr_LCD/ecu_chr_lcd.h"

void ecu_layer_intialize(void);
#endif	/* ECU_LAYER_INIT_H */

