#ifndef DIO_FEATURE_H
#define DIO_FEATURE_H

#define DIO_USE_CALLBACKS               0x01u
#define DIO_USE_EVENTS                  0x02u


#ifndef DIO_ENABLE_INTERRUPT_OUTPUT
/**
 * @brief Flag to switch between the pin interrupt output
 * 
 * With this flag the interrupt output can be switched. 
 * It can be choosen between CALLBCKS and EVENT output. For the EVENT output 
 * the Event Library is necessary.
 */
#define DIO_ENABLE_INTERRUPT_OUTPUT          DIO_USE_EVENTS

#endif

#endif