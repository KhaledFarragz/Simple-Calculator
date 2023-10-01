/* 
 * File:   mcal_std_libraries.h
 * Author: Khaled_Farrag
 *
 * Created on September 19, 2023, 2:02 PM
 */

#ifndef MCAL_STD_LIBRARIES_H
#define	MCAL_STD_LIBRARIES_H


/*section : includes*/
#include "std_libraries.h"
#include "compiler.h"

/*section : Data Type Declarations*/
typedef unsigned char    uint8  ;
typedef unsigned short   uint16 ;
typedef unsigned int     uint32 ;
typedef signed   char    sint8  ;
typedef signed   short   sint16 ;
typedef signed   int     sint32 ;

typedef uint8 Std_ReturnType    ;

/*section : Macro declarations*/
#define STD_HIGH       0x01
#define STD_LOW        0x00

#define STD_ON         0x01
#define STD_OFF        0x00

#define STD_ACTIVE     0x01
#define STD_IDLE       0x00

#define E_OK      (Std_ReturnType)0x01
#define E_NOT_OK  (Std_ReturnType)0x00

#define ZERO_INIT      0

/*section : Macro Functions Declarations*/


/*section : Functions Declarations*/

#endif	/* MCAL_STD_LIBRARIES_H */

