#ifndef DIO_CONFIG_H
#define DIO_CONFIG_H

/**
 * @file DIO_Config.h
 * @brief Configuration file for the Digital I/O module.
 */

#include "Dio_Feature.h"

#ifdef IMPLEMENT_ISR
    #undef IMPLEMENT_ISR
    #define IMPLEMENT_ISR do {} while(0)
#endif 
//#include "Arduino.h"


#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_EVENTS
#include "Event.h"
#endif

#if ARDUINO_ARCH_ESP8266
#include "Ecus/ESP8266_Dio_Config.h"
#elif ARDUINO_ARCH_AVR
#include "Ecus/Avr_Dio_Config.h"
#elif ARDUINO_ARCH_ESP32
#include "Ecus/ESP32_Dio_Config.h"
#else
#error "ECU not Supported"
#endif


#define IMPLEMENT_ISR(vect, interrupt) do {} while(0)
#include "Arduino.h"

/**
 * @brief Enumeration of interrupt modes for GPIO pins.
 */
typedef enum
{
    INTERRUPT_ON_RISING = RISING,                          /**< Interrupt triggered on rising edge */
    INTERRUPT_ON_FALLING = FALLING,                        /**< Interrupt triggered on falling edge */
    INTERRUPT_ON_CHANGE = CHANGE,                          /**< Interrupt triggered on any edge */

#if defined(ESP32) || defined(ESP8266)
    INTERRUPT_ON_LOW = ONLOW,                              /**< Interrupt triggered on low level */
    INTERRUPT_ON_HIGH = ONHIGH,                            /**< Interrupt triggered on high level */
    INTERRUPT_ON_LOW_WAKEUP_ENABLE = ONLOW_WE,             /**< Interrupt triggered on low level with wakeup enable */
    INTERRUPT_ON_HIGH_WAKEUP_ENABLE = ONHIGH_WE,           /**< Interrupt triggered on high level with wakeup enable */
#endif
} InterruptMode_t;

/**
 * @brief Enumeration of digital I/O pin modes.
 */
typedef enum
{
    DIO_AS_INPUT = INPUT,                                  /**< Pin configured as input */
    DIO_AS_INPUT_WITH_PULLUP = INPUT_PULLUP,               /**< Pin configured as input with internal pull-up resistor */
#if defined(ESP32)
    DIO_AS_INPUT_WITH_PULLDOWN = INPUT_PULLDOWN,           /**< Pin configured as input with internal pull-down resistor */
#elif defined(ESP8266)
    DIO_AS_INPUT_WITH_PULLDOWN_16 = INPUT_PULLDOWN_16,     /**< Pin configured as input with internal pull-down resistor (ESP8266 specific) */
#endif
    DIO_AS_OUTPUT = OUTPUT,                                /**< Pin configured as output */
#if defined(ESP8266)
    DIO_AS_OUTPUT_OPEN_DRAIN = OUTPUT_OPEN_DRAIN           /**< Pin configured as output in open-drain mode (ESP8266 specific) */
#endif
} Mode_t;

#define DIO_NOT_VALID DIO_NV                               /**< Not valid GPIO pin */
#define DIO_INTERRUPT_NOT_USED (InterruptMode_t)0xFF       /**< Interrupt mode not used for GPIO pin */

#if (DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_EVENTS)
    #define DIO_INTERFACE EventSignal<Dio*>*
#else
    #define DIO_INTERFACE DioCallback
#endif


#endif
