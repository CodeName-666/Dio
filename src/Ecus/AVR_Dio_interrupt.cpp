/* -*- mode: jde; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
  Part of the Wiring project - http://wiring.uniandes.edu.co

  Copyright (c) 2004-05 Hernando Barragan

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
  
  Modified 24 November 2006 by David A. Mellis
  Modified 1 August 2010 by Mark Sproul
*/


#if ARDUINO_ARCH_AVR

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "wiring_private.h"


#include "Ecus/AVR_Dio_Config.h"
#include "Dio.h"


/**
 * Crate a new array named interruptArguments, in the same way as the interruptFunction array was defined.
 * This is needed to store the arguments paramter, which will be set, when a interrupt will be triggered
 */
static Interrupt_Source_t interruptArgument[EXTERNAL_NUM_INTERRUPTS] = {
#if EXTERNAL_NUM_INTERRUPTS > 8
    #warning There are more than 8 external interrupts. Some callbacks may not be initialized.
#endif
#if EXTERNAL_NUM_INTERRUPTS > 7
    GET_ISR_FUNCTION(INT0_vect_num), NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 6
    GET_ISR_FUNCTION(INT1_vect_num), NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 5
    GET_ISR_FUNCTION(INT2_vect_num), NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 4
    GET_ISR_FUNCTION(INT3_vect_num), NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 3
    GET_ISR_FUNCTION(INT4_vect_num), NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 2
    GET_ISR_FUNCTION(INT5_vect_num), NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 1
    GET_ISR_FUNCTION(INT6_vect_num), NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 0
    GET_ISR_FUNCTION(INT7_vect_num), NULL,
#endif
};


#define IMPLEMENT_ISR_FUNCTION(vect)                                                    \
    void EXPAND_AND_CONCAT(interrupt_function_, vect)(void)                             \
    {                                                                                   \
      uint8_t vector = vect;                                                            \
      Dio* dio = static_cast<Dio*>(interruptArgument[vector].dio_instance);             \
      if(dio != NULL)                                                                   \
      {                                                                                 \
        dio->interruptHandler();                                                        \
      }                                                                                 \
    }

#if defined(__AVR_ATmega32U4__)

  IMPLEMENT_ISR_FUNCTION(INT0_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT1_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT2_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT3_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT6_vect_num);

#elif defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__) || defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega8U2__)

  IMPLEMENT_ISR_FUNCTION(INT0_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT1_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT2_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT3_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT4_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT5_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT6_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT7_vect_num);

#elif defined(EICRA) && defined(EICRB)


  IMPLEMENT_ISR_FUNCTION(INT0_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT1_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT2_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT3_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT4_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT5_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT6_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT7_vect_num);

#else

  IMPLEMENT_ISR_FUNCTION(INT0_vect_num);
  IMPLEMENT_ISR_FUNCTION(INT1_vect_num);

#if defined(EICRA) && defined(ISC20)
  IMPLEMENT_ISR_FUNCTION(INT2_vect_num);
#endif

#endif


void Dio_attachInterrupt(uint8_t pin, int mode, void* mThis)
{
  if (IS_INTERRUPT_PIN(pin))
  {
    uint8_t vector_idx = digitalPinToInterrupt(pin);
    interruptArgument[vector_idx].dio_instance = mThis;
    voidIsrPtr isr = interruptArgument[vector_idx].isrPtr;
    attachInterrupt(vector_idx, isr, mode); 
  }
}



#endif
