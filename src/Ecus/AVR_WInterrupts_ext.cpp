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

#ifndef AVR_WINTERRUPTS_EXT_H
#define AVR_WINTERRUPTS_EXT_H


#if ARDUINO_ARCH_AVR

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "wiring_private.h"




/*Define the new Funciton Pointer Data Type with argurment pointer*/ 
typedef void (*voidDioFuncPtrArg)(void*);

static void nothing(void*) {
}


void interrupt_vector_1(void) 
{
  
}


void interrupt_vector_2(void)
{
  
}


void interrupt_vector_3(void)
{
  
}


void interrupt_vector_4(void)
{
  
}


void interrupt_vector_5(void)
{
  
}


void interrupt_vector_6(void)
{
  
}


void interrupt_vector_7(void)
{
  
}


void interrupt_vector_8(void)
{
  
}





/**
 * define the new Interrupt Function array in the same way as it was in the original file
 * Only the naming was updated
 */
static volatile voidDioFuncPtrArg interruptFunction[EXTERNAL_NUM_INTERRUPTS] = {
#if EXTERNAL_NUM_INTERRUPTS > 8
    #warning There are more than 8 external interrupts. Some callbacks may not be initialized.
    (voidDioFuncPtrArg)nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 7
    (voidDioFuncPtrArg)nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 6
    (voidDioFuncPtrArg)nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 5
    (voidDioFuncPtrArg)nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 4
    (voidDioFuncPtrArg)nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 3
    (voidDioFuncPtrArg)nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 2
    (voidDioFuncPtrArg)nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 1
    (voidDioFuncPtrArg)nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 0
    (voidDioFuncPtrArg)nothing,
#endif
};

/**
 * Crate a new array named interruptArguments, in the same way as the interruptFunction array was defined.
 * This is needed to store the arguments paramter, which will be set, when a interrupt will be triggered
 */
static void* interruptArgument[EXTERNAL_NUM_INTERRUPTS] = {
#if EXTERNAL_NUM_INTERRUPTS > 8
    #warning There are more than 8 external interrupts. Some callbacks may not be initialized.
    NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 7
    NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 6
    NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 5
    NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 4
    NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 3
    NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 2
    NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 1
    NULL,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 0
    NULL,
#endif
};

/**
 * This is the updated attachInterrupt function, which allows now also to handover parameter. 
 */
void attachInterruptArg(uint8_t interruptNum, voidDioFuncPtrArg userFunc, void * arg, int mode) {
  if(interruptNum < EXTERNAL_NUM_INTERRUPTS) {
    interruptFunction[interruptNum] = userFunc;
   
    /*Here is the main change*/ 
    interruptArgument[interruptNum] = arg;
    // Configure the interrupt mode (trigger on low input, any change, rising
    // edge, or falling edge).  The mode constants were chosen to correspond
    // to the configuration bits in the hardware register, so we simply shift
    // the mode into place.
      
    // Enable the interrupt.
      
    switch (interruptNum) {
#if defined(__AVR_ATmega32U4__)
	// I hate doing this, but the register assignment differs between the 1280/2560
	// and the 32U4.  Since avrlib defines registers PCMSK1 and PCMSK2 that aren't 
	// even present on the 32U4 this is the only way to distinguish between them.
    case 0:
	EICRA = (EICRA & ~((1<<ISC00) | (1<<ISC01))) | (mode << ISC00);
	EIMSK |= (1<<INT0);
	break;
    case 1:
	EICRA = (EICRA & ~((1<<ISC10) | (1<<ISC11))) | (mode << ISC10);
	EIMSK |= (1<<INT1);
	break;	
    case 2:
        EICRA = (EICRA & ~((1<<ISC20) | (1<<ISC21))) | (mode << ISC20);
        EIMSK |= (1<<INT2);
        break;
    case 3:
        EICRA = (EICRA & ~((1<<ISC30) | (1<<ISC31))) | (mode << ISC30);
        EIMSK |= (1<<INT3);
        break;
    case 4:
        EICRB = (EICRB & ~((1<<ISC60) | (1<<ISC61))) | (mode << ISC60);
        EIMSK |= (1<<INT6);
        break;
#elif defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__) || defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega8U2__)
    case 0:
      EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
      EIMSK |= (1 << INT0);
      break;
    case 1:
      EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
      EIMSK |= (1 << INT1);
      break;
    case 2:
      EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
      EIMSK |= (1 << INT2);
      break;
    case 3:
      EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
      EIMSK |= (1 << INT3);
      break;
    case 4:
      EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
      EIMSK |= (1 << INT4);
      break;
    case 5:
      EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
      EIMSK |= (1 << INT5);
      break;
    case 6:
      EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
      EIMSK |= (1 << INT6);
      break;
    case 7:
      EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
      EIMSK |= (1 << INT7);
      break;
#elif defined(EICRA) && defined(EICRB) && defined(EIMSK)
    case 2:
      EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
      EIMSK |= (1 << INT0);
      break;
    case 3:
      EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
      EIMSK |= (1 << INT1);
      break;
    case 4:
      EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
      EIMSK |= (1 << INT2);
      break;
    case 5:
      EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
      EIMSK |= (1 << INT3);
      break;
    case 0:
      EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
      EIMSK |= (1 << INT4);
      break;
    case 1:
      EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
      EIMSK |= (1 << INT5);
      break;
    case 6:
      EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
      EIMSK |= (1 << INT6);
      break;
    case 7:
      EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
      EIMSK |= (1 << INT7);
      break;
#else		
    case 0:
    #if defined(EICRA) && defined(ISC00) && defined(EIMSK)
      EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
      EIMSK |= (1 << INT0);
    #elif defined(MCUCR) && defined(ISC00) && defined(GICR)
      MCUCR = (MCUCR & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
      GICR |= (1 << INT0);
    #elif defined(MCUCR) && defined(ISC00) && defined(GIMSK)
      MCUCR = (MCUCR & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
      GIMSK |= (1 << INT0);
    #else
      #error attachInterrupt not finished for this CPU (case 0)
    #endif
      break;

    case 1:
    #if defined(EICRA) && defined(ISC10) && defined(ISC11) && defined(EIMSK)
      EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
      EIMSK |= (1 << INT1);
    #elif defined(MCUCR) && defined(ISC10) && defined(ISC11) && defined(GICR)
      MCUCR = (MCUCR & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
      GICR |= (1 << INT1);
    #elif defined(MCUCR) && defined(ISC10) && defined(GIMSK) && defined(GIMSK)
      MCUCR = (MCUCR & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
      GIMSK |= (1 << INT1);
    #else
      #warning attachInterruptArg may need some more work for this cpu (case 1)
    #endif
      break;
    
    case 2:
    #if defined(EICRA) && defined(ISC20) && defined(ISC21) && defined(EIMSK)
      EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
      EIMSK |= (1 << INT2);
    #elif defined(MCUCR) && defined(ISC20) && defined(ISC21) && defined(GICR)
      MCUCR = (MCUCR & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
      GICR |= (1 << INT2);
    #elif defined(MCUCR) && defined(ISC20) && defined(GIMSK) && defined(GIMSK)
      MCUCR = (MCUCR & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
      GIMSK |= (1 << INT2);
    #endif
      break;
#endif
    }
  }
}

#define IMPLEMENT_ISR(vect, interrupt) \
  ISR(vect##_new) { \
    void* arg = interruptArgument[interrupt]; \
    interruptFunction[interrupt](arg); \
  }

#if defined(__AVR_ATmega32U4__)

IMPLEMENT_ISR(INT0_vect, EXTERNAL_INT_0)
IMPLEMENT_ISR(INT1_vect, EXTERNAL_INT_1)
IMPLEMENT_ISR(INT2_vect, EXTERNAL_INT_2)
IMPLEMENT_ISR(INT3_vect, EXTERNAL_INT_3)
IMPLEMENT_ISR(INT6_vect, EXTERNAL_INT_4)

#elif defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__) || defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega8U2__)

IMPLEMENT_ISR(INT0_vect, EXTERNAL_INT_0)
IMPLEMENT_ISR(INT1_vect, EXTERNAL_INT_1)
IMPLEMENT_ISR(INT2_vect, EXTERNAL_INT_2)
IMPLEMENT_ISR(INT3_vect, EXTERNAL_INT_3)
IMPLEMENT_ISR(INT4_vect, EXTERNAL_INT_4)
IMPLEMENT_ISR(INT5_vect, EXTERNAL_INT_5)
IMPLEMENT_ISR(INT6_vect, EXTERNAL_INT_6)
IMPLEMENT_ISR(INT7_vect, EXTERNAL_INT_7)

#elif defined(EICRA) && defined(EICRB)

IMPLEMENT_ISR(INT0_vect, EXTERNAL_INT_2)
IMPLEMENT_ISR(INT1_vect, EXTERNAL_INT_3)
IMPLEMENT_ISR(INT2_vect, EXTERNAL_INT_4)
IMPLEMENT_ISR(INT3_vect, EXTERNAL_INT_5)
IMPLEMENT_ISR(INT4_vect, EXTERNAL_INT_0)
IMPLEMENT_ISR(INT5_vect, EXTERNAL_INT_1)
IMPLEMENT_ISR(INT6_vect, EXTERNAL_INT_6)
IMPLEMENT_ISR(INT7_vect, EXTERNAL_INT_7)



#else

IMPLEMENT_ISR(INT0_vect, EXTERNAL_INT_0)
IMPLEMENT_ISR(INT1_vect, EXTERNAL_INT_1)

#if defined(EICRA) && defined(ISC20)
IMPLEMENT_ISR(INT2_vect, EXTERNAL_INT_2)
#endif

#endif
#endif
#endif