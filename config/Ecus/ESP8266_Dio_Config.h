/*
 * Dio_Config.h
 *
 *  Created on: 04.12.2017
 *      Author: AP02
 */

#ifndef _ESP8266_DIO_CONFIG_H_
#define _ESP8266_DIO_CONFIG_H_

#if ESP8266
#include "Arduino.h"

#define DIO_NUMBER_OF_IO               9

typedef enum
{
   GPIO_DO         = 16,
   GPIO_D1         =  5,
   GPIO_D2         =  4,
   GPIO_D3         =  0,
   GPIO_D4         =  2,
   GPIO_D5         =  14,
   GPIO_D6         =  12,
   GPIO_D7         =  13,
   GPIO_D8         =  15,
   GPIO_NV         = 255,

}Dio_t;

#endif
#endif /* ESP8266_DIO_CONFIG_H_ */
