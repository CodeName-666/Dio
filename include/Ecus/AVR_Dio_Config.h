/*
 * Dio_Config.h
 *
 *  Created on: 04.12.2017
 *      Author: AP02
 */

#ifndef _AVR_DIO_CONFIG_H_
#define _AVR_DIO_CONFIG_H_
#if ARDUINO_ARCH_AVR

#define CONCAT(a, b) a##b
#define EXPAND_AND_CONCAT(a, b) CONCAT(a, b)  

// Angepasstes GET_ISR_FUNCTION Macro
#define GET_ISR_FUNCTION(vect) EXPAND_AND_CONCAT(Dio_IsrFunction_, vect)

#define PRE_DEFINE_ISR(vect) void EXPAND_AND_CONCAT(Dio_IsrFunction_, vect)(void)

#define IS_INTERRUPT_PIN(pin)                       \
  (digitalPinToInterrupt(pin) != NOT_AN_INTERRUPT)


typedef void (*DioCallback)(void*);
typedef void (*voidIsrPtr)(void);

typedef struct {

  voidIsrPtr isrPtr;
  void* dio_instance;

}Interrupt_Source_t;


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


void Dio_attachInterrupt(uint8_t pin, int mode, void* mThis);

#if defined(__AVR_ATmega32U4__)

  PRE_DEFINE_ISR(INT0_vect_num);
  PRE_DEFINE_ISR(INT1_vect_num);
  PRE_DEFINE_ISR(INT2_vect_num);
  PRE_DEFINE_ISR(INT3_vect_num);
  PRE_DEFINE_ISR(INT6_vect_num);

#elif defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__) || defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega8U2__)

  PRE_DEFINE_ISR(INT0_vect_num);
  PRE_DEFINE_ISR(INT1_vect_num);
  PRE_DEFINE_ISR(INT2_vect_num);
  PRE_DEFINE_ISR(INT3_vect_num);
  PRE_DEFINE_ISR(INT4_vect_num);
  PRE_DEFINE_ISR(INT5_vect_num);
  PRE_DEFINE_ISR(INT6_vect_num);
  PRE_DEFINE_ISR(INT7_vect_num);

#elif defined(EICRA) && defined(EICRB)


  PRE_DEFINE_ISR(INT0_vect_num);
  PRE_DEFINE_ISR(INT1_vect_num);
  PRE_DEFINE_ISR(INT2_vect_num);
  PRE_DEFINE_ISR(INT3_vect_num);
  PRE_DEFINE_ISR(INT4_vect_num);
  PRE_DEFINE_ISR(INT5_vect_num);
  PRE_DEFINE_ISR(INT6_vect_num);
  PRE_DEFINE_ISR(INT7_vect_num);

#else

  PRE_DEFINE_ISR(INT0_vect_num);
  PRE_DEFINE_ISR(INT1_vect_num);

#if defined(EICRA) && defined(ISC20)
  PRE_DEFINE_ISR(INT2_vect_num);
#endif
#endif

#endif
#endif /* DIO_AVR_DIO_CONFIG_H_ */
