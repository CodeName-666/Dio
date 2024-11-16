/**
 * @file Dio.cpp
 * @brief Implementation file for the Dio class representing a digital I/O pin.
 *
 * This file contains the method implementations for handling digital I/O pins.
 *
 * @author AP02
 * @date 04.12.2017
 */

#include "Dio.h"
#include "Dio_Debug.h"

Dio::Dio() : m_dio(GPIO_NV), m_mode(DIO_AS_INPUT_WITH_PULLUP), m_interrupt_mode(DIO_INTERRUPT_NOT_USED)
{
}

Dio::Dio(Dio_t dio, Mode_t mode) : m_dio(dio), m_mode(mode), m_interrupt_mode(DIO_INTERRUPT_NOT_USED)
{
    init(dio, mode);
}

Dio::~Dio()
{
    // Destructor logic if needed
}

void Dio::init(void)
{
    if (m_dio != GPIO_NV)
    {
        setMode(m_mode);
    }
}

void Dio::setMode(Mode_t mode)
{
    m_mode = mode;
    if (m_dio != GPIO_NV)
    {
        pinMode(static_cast<uint8_t>(m_dio), static_cast<uint8_t>(m_mode));
    }
}

void Dio::setDio(Dio_t dio)
{
    m_dio = dio;
}

Mode_t Dio::getMode(void)
{
    return m_mode;
}

Dio_t Dio::getDio(void) const
{
    return m_dio;
}

void Dio::set(Level_t status)
{
    if (m_dio != GPIO_NV)
    {
        digitalWrite(static_cast<uint8_t>(m_dio), static_cast<uint8_t>(status));
    }
}

Level_t Dio::get(void)
{
    Level_t ret = DIO_LOW;
    if (m_dio != GPIO_NV)
    {
        ret = static_cast<Level_t>(digitalRead(static_cast<uint8_t>(m_dio)));
    }
    return ret;
}

void Dio::enableInterrupts(InterruptMode_t interrupt_mode)
{
    if (m_dio != GPIO_NV && interrupt_mode != DIO_INTERRUPT_NOT_USED)
    {
        m_interrupt_mode = interrupt_mode;
        Dio_attachInterrupt(m_dio, static_cast<uint8_t>(interrupt_mode), this);
    }
}

void Dio::disableInterrupts(void)
{
    detachInterrupt(digitalPinToInterrupt(static_cast<uint8_t>(m_dio)));
    m_interrupt_mode = DIO_INTERRUPT_NOT_USED;
}

void Dio::loop(void)
{
    if (m_interrupt_mode != DIO_INTERRUPT_NOT_USED)
    {
        Level_t current_level = get();
        eventHandler(current_level);
    }
}

void Dio::onInterrupt(DIO_INTERFACE callback_or_signal)
{
#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_EVENTS
    EVENT_EMIT(*callback_or_signal, this);
#elif DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_CALLBACKS
    execCallback(callback_or_signal);
#endif
}

void Dio::init(Dio_t dio, Mode_t mode)
{
    m_dio = dio;
    m_mode = mode;
    if (dio != GPIO_NV)
    {
        setMode(mode);
    }
}

void Dio::eventHandler(Level_t current_level)
{
    static Level_t old_level = DIO_LOW;
    if (old_level != current_level)
    {
        if (current_level == DIO_LOW)
        {
#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_EVENTS
            EVENT_EMIT(m_on_low_signal, this);
#elif DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_CALLBACKS
            execCallback(m_on_low_callback);
#endif
        }
        else
        {
#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_EVENTS
            EVENT_EMIT(m_on_high_signal, this);
#elif DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_CALLBACKS
            execCallback(m_on_high_callback);
#endif
        }

        if (old_level == DIO_LOW && current_level == DIO_HIGH)
        {
#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_EVENTS
            EVENT_EMIT(m_on_rising_signal, this);
#elif DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_CALLBACKS
            execCallback(m_on_rising_callback);
#endif
        }
        else if (old_level == DIO_HIGH && current_level == DIO_LOW)
        {
#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_EVENTS
            EVENT_EMIT(m_on_falling_signal, this);
#elif DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_CALLBACKS
            execCallback(m_on_falling_callback);
#endif
        }

#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_EVENTS
            EVENT_EMIT(m_on_change_signal,this);
#elif DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_CALLBACKS
            execCallback(m_on_change_callback);
#endif
        old_level = current_level;
    }
}


#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_CALLBACKS
void Dio::setOnChangeCbk(DioCallback cbk)
{
    m_on_change_callback = cbk;
}

void Dio::setOnRisingCbk(DioCallback cbk)
{
    m_on_rising_callback = cbk;
}

void Dio::setOnFallingCbk(DioCallback cbk)
{
    m_on_falling_callback = cbk;
}

void Dio::setOnLowCbk(DioCallback cbk)
{
    m_on_low_callback = cbk;
}

void Dio::setOnHighCbk(DioCallback cbk)
{
    m_on_high_callback = cbk;
}

inline void Dio::execCallback(DioCallback cbk)
{
    if (cbk != nullptr)
    {
        cbk(this);
    }
}
#endif


 void Dio::interruptHandler(void)
 {
    //DBIF_LOG_INFO("INTERRUPT TRIGGERED FROM IO %i", (int)interrupt_source->getDio());
    eventHandler(get());

 }