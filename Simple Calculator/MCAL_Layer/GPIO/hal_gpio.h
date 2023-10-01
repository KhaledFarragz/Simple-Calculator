/* 
 * File:   hal_gpio.h
 * Author: Khaled_Farrag
 *
 * Created on September 19, 2023, 2:00 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*section : includes*/
#include "pic18f4620.h"
#include "../mcal_std_libraries.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/*section : Macro declarations*/
#define BIT_MASK (uint8) 1

#define PORT_PIN_MAX     8 
#define PORT_MAX_NUMBER  5

#define PORTC_MASK        0xFF

/*section : Macro Functions Declarations*/
#define HWREG8(_X)     (*((volatile uint8 *)(_X)))

#define SET_BIT(REG, BIT_POSN)    (REG |=  (BIT_MASK << BIT_POSN))
#define CLR_BIT(REG, BIT_POSN)    (REG &= ~(BIT_MASK << BIT_POSN))
#define TOG_BIT(REG, BIT_POSN)    (REG ^=  (BIT_MASK << BIT_POSN))
#define RED_BIT(REG, BIT_POSN)    ((REG >> BIT_POSN) & BIT_MASK)

/*section : Data Type Declarations*/
typedef enum{
    GPIO_LOW,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    GPIO_PIN0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7      
}pin_index_t;

typedef enum{
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX     
}port_index_t;

typedef struct {
    uint8 port       : 3;  /*@ref port_index_t*/
    uint8 pin        : 3;  /*@ref pin_index_t*/
    uint8 direction  : 1;  /*@ref direction_t*/
    uint8 logic      : 1;  /*@ref logic_t*/
}pin_config_t;

/*section : Functions Declarations*/
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config);

Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8  logic);
Std_ReturnType gpio_port_read_logic (port_index_t port, uint8 *logic); 
Std_ReturnType gpio_port_toggle_logic(port_index_t port);


#endif	/* HAL_GPIO_H */

