/*
 * Dio_Config.h
 *
 *  Created on: 04.05.2019
 *      Author: AP02
 */

#ifndef _ESP32_DIO_CONFIG_H_
#define _ESP32_DIO_CONFIG_H_
#if ARDUINO_ARCH_ESP32

#include <Arduino.h>

#define DIO_NUMBER_OF_IO               19

typedef enum
{
  /*GPIO                Input    Output    Notes                              */
    GPIO_NV = -1,
    GPIO_0  =   0, /*    OK         OK                                        */
    GPIO_1  =   1, /*    OK         OK                                        */
    GPIO_2  =   2, /*    OK         OK         connected to on-board LED      */
    GPIO_3  =   3, /*    OK         RX pin     HIGH at boot                   */
    GPIO_4  =   4, /*    OK         OK                                        */
    GPIO_5  =   5, /*    OK         OK         outputs PWM signal at boot     */
    GPIO_12 =  12, /*    OK         OK         boot fail if pulled high       */
    GPIO_13 =  13, /*    OK         OK                                        */
    GPIO_14 =  14, /*    OK         OK         outputs PWM signal at boot     */
    GPIO_15 =  15, /*    OK         OK         outputs PWM signal at boot     */
    GPIO_16 =  16, /*    OK         OK                                        */
    GPIO_17 =  17, /*    OK         OK                                        */
    GPIO_18 =  18, /*    OK         OK                                        */
    GPIO_19 =  19, /*    OK         OK                                        */
    GPIO_21 =  21, /*    OK         OK                                        */
    GPIO_22 =  22, /*    OK         OK                                        */
    GPIO_23 =  23, /*    OK         OK                                        */
    GPIO_25 =  25, /*    OK         OK                                        */
    GPIO_26 =  26, /*    OK         OK                                        */
    GPIO_27 =  27, /*    OK         OK                                        */
    GPIO_32 =  32, /*    OK         OK                                        */
    GPIO_33 =  33, /*    OK         OK                                        */
    GPIO_34 =  34, /*    OK         input only                                */
    GPIO_35 =  35, /*    OK         input only                                */
    GPIO_36 =  36, /*    OK         input only                                */
    GPIO_39 =  39, /*    OK         input only                                */
   

}Dio_t;


typedef void (*voidDioFuncPtrArg)(void*);



extern "C"
{
	extern void __attachInterruptFunctionalArg(uint8_t pin, voidDioFuncPtrArg userFunc, void * arg, int intr_type, bool functional);
}


void Dio_attachInterrupt(uint8_t pin, int mode, void * arg);



#endif
#endif /* SENSORS_SOURCE_05_PERIPERIAL_DIO_ESP32_DIO_CONFIG_H_ */
