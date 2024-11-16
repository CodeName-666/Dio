

#if ARDUINO_ARCH_ESP32

#include "Ecus/ESP32_Dio_Config.h"
#include "Dio.h"


void Dio_IsrFunction(void* dioPtr)
{
    Dio* dio = static_cast<Dio*>(dioPtr);
    if(dio != NULL)
    {
        dio->interruptHandler();
    }
}


void Dio_attachInterrupt(uint8_t pin, int mode, void * arg)
{
	// use the local interrupt routine which takes the ArgStructure as argument
	__attachInterruptFunctionalArg (digitalPinToGPIONumber(pin), (voidDioFuncPtrArg) Dio_IsrFunction, arg, mode, false);
}













#endif