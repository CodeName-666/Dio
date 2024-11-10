/*
 * Dio_Config.h
 *
 *  Created on: 04.12.2017
 *      Author: AP02
 */

#ifndef _AVR_DIO_CONFIG_H_
#define _AVR_DIO_CONFIG_H_

#if ARDUINO_ARCH_AVR
#include "Arduino.h"

typedef enum {
    GPIO_NV = -1,
  #if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_PRO) || defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_ETHERNET)
    GPIO_0,
    GPIO_1,
    GPIO_2,
    GPIO_3,
    GPIO_4,
    GPIO_5,
    GPIO_6,
    GPIO_7,
    GPIO_8,
    GPIO_9,
    GPIO_10,
    GPIO_11,
    GPIO_12,
    GPIO_13
  #endif

  #if defined(ARDUINO_AVR_MEGA2560)
    GPIO_0,
    GPIO_1,
    GPIO_2,
    GPIO_3,
    GPIO_4,
    GPIO_5,
    GPIO_6,
    GPIO_7,
    GPIO_8,
    GPIO_9,
    GPIO_10,
    GPIO_11,
    GPIO_12,
    GPIO_13,
    GPIO_14,
    GPIO_15,
    GPIO_16,
    GPIO_17,
    GPIO_18,
    GPIO_19,
    GPIO_20,
    GPIO_21,
    GPIO_22,
    GPIO_23,
    GPIO_24,
    GPIO_25,
    GPIO_26,
    GPIO_27,
    GPIO_28,
    GPIO_29,
    GPIO_30,
    GPIO_31,
    GPIO_32,
    GPIO_33,
    GPIO_34,
    GPIO_35,
    GPIO_36,
    GPIO_37,
    GPIO_38,
    GPIO_39,
    GPIO_40,
    GPIO_41,
    GPIO_42,
    GPIO_43,
    GPIO_44,
    GPIO_45,
    GPIO_46,
    GPIO_47,
    GPIO_48,
    GPIO_49,
    GPIO_50,
    GPIO_51,
    GPIO_52,
    GPIO_53
  #endif

  #if defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_LEONARDO) || defined(ARDUINO_AVR_YUN)
    GPIO_0,
    GPIO_1,
    GPIO_2,
    GPIO_3,
    GPIO_4,
    GPIO_5,
    GPIO_6,
    GPIO_7,
    GPIO_8,
    GPIO_9,
    GPIO_10,
    GPIO_11,
    GPIO_12,
    GPIO_13,
    GPIO_14,
    GPIO_15,
    GPIO_16,
    GPIO_17,
    GPIO_18,
    GPIO_19,
  #endif
} Dio_t;


typedef void (*voidDioFuncPtrArg)(void*);

/**
 * 
 */
extern void attachInterruptArg(uint8_t interruptNum, voidDioFuncPtrArg userFunc, void * arg, int mode);



inline static void Dio_attachInterrupt(uint8_t pin, voidDioFuncPtrArg intRoutine,void * arg, int mode)
{
	// use the local interrupt routine which takes the ArgStructure as argument
	attachInterruptArg(pin, (voidDioFuncPtrArg) intRoutine, arg, mode);
}



#endif
#endif /* DIO_AVR_DIO_CONFIG_H_ */
