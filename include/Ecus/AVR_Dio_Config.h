/*
 * Dio_Config.h
 *
 *  Created on: 04.12.2017
 *      Author: AP02
 */

#ifndef _AVR_DIO_CONFIG_H_
#define _AVR_DIO_CONFIG_H_
#if ARDUINO_ARCH_AVR


#include "wiring_private.h"



class Dio;

typedef void (*voidDioFuncPtr)(Dio*);

typedef struct {
  voidDioFuncPtr new_interrupt_function;
  Dio * dio_instance;

}Interrupt_Source_t;

#define IS_INTERRUPT_PIN(pin)                       \
  (digitalPinToInterrupt(pin) != NOT_AN_INTERRUPT)


#define INTERRUPT_SOOURCE_INIT_NULL       \
    {                                     \
      (voidDioFuncPtr)NULL,                  \
      (Dio*)NULL                          \
    } 


typedef enum {
    GPIO_NV = -1,
  #if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_PRO) || defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_ETHERNET)
    GPIO_0,
    GPIO_1,
    GPIO_2_INT,
    GPIO_3_INT,
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
    GPIO_2_INT,
    GPIO_3_INT,
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
    GPIO_18_INT,
    GPIO_19_INT,
    GPIO_20_INT,
    GPIO_21_INT,
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
    GPIO_0_INT,
    GPIO_1_INT,
    GPIO_2_INT,
    GPIO_3,
    GPIO_4,
    GPIO_5,
    GPIO_6,
    GPIO_7_INT,
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


void Dio_attachInterrupt(uint8_t pin, int mode, Dio* mThis9,

#endif
#endif /* DIO_AVR_DIO_CONFIG_H_ */
