/**
 * @file Dio.h
 * @brief Header file for the Dio class representing a digital I/O pin, including methods for configuration, setting, and interrupt handling.
 *
 * This file defines the interface and methods for handling digital I/O pins using the Arduino framework.
 *
 * @author AP02
 * @date 04.12.2017
 */

#ifndef _DIO_DIO_H_
#define _DIO_DIO_H_

#include <Arduino.h>
#include "../config/Dio_Config.h"


/**
 * @brief Enumeration representing the level of a digital I/O pin.
 */
typedef enum
{
   DIO_LOW,  /**< Low level */
   DIO_HIGH  /**< High level */
} Level_t;

/**
 * @brief Type definition for callback functions used in interrupts.
 */
typedef std::function<void(void)> DioCallback;

typedef void (*DioInterrupt)(void);

/**
 * @brief Class representing a digital I/O pin with configurable modes and interrupt handling.
 */
class Dio
{
#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_EVENTS
   EVENT_REGISTER_EVENTS(Dio)
#endif

public:
   /**
    * @brief Default constructor for Dio class.
    */
   Dio();

   /**
    * @brief Constructor with pin and mode parameters.
    * @param dio The digital I/O pin number.
    * @param mode The mode of the pin (default is DIO_AS_INPUT_WITH_PULLUP).
    */
   Dio(Dio_t dio, Mode_t mode = DIO_AS_INPUT_WITH_PULLUP);

   /**
    * @brief Destructor for the Dio class.
    */
   virtual ~Dio();

   /**
    * @brief Initializes the digital I/O pin.
    */
   void init(void);

   /**
    * @brief Sets the mode of the digital I/O pin.
    * @param mode The mode to set for the pin.
    */
   void setMode(Mode_t mode);

   /**
    * @brief Sets the digital I/O pin number.
    * @param dio The digital I/O pin number to set.
    */
   void setDio(Dio_t dio);

   /**
    * @brief Retrieves the current mode of the digital I/O pin.
    * @return The current mode of the pin.
    */
   Mode_t getMode(void);

   /**
    * @brief Retrieves the current digital I/O pin number.
    * @return The current digital I/O pin number.
    */
   Dio_t getDio(void) const;

   /**
    * @brief Sets the output level of the digital I/O pin.
    * @param status The level (DIO_HIGH or DIO_LOW) to set.
    */
   void set(Level_t status);

   /**
    * @brief Retrieves the current level of the digital I/O pin.
    * @return The current level (DIO_HIGH or DIO_LOW) of the pin.
    */
   inline Level_t get(void);

   /**
    * @brief Enables interrupts on the digital I/O pin with the specified mode and callback.
    * @param interrupt_mode The mode for the interrupt.
    * @param cbk The callback function for the interrupt.
    */
   void enableInterrupts(InterruptMode_t interrupt_mode);

   /**
    * @brief Disables interrupts on the digital I/O pin.
    */
   void disableInterrupts(void);

   /**
    * @brief Handles the loop operation for managing pin events.
    */
   void loop(void);

   /**
    * @brief Handles the interrupt event and emits or executes the appropriate callback.
    */
   inline void onInterrupt(void);

#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_CALLBACKS
   /**
    * @brief Sets the callback for change detection.
    * @param cbk The callback function.
    */
   void setOnChangeCbk(DioCallback cbk);

   /**
    * @brief Sets the callback for rising edge detection.
    * @param cbk The callback function.
    */
   void setOnRisingCbk(DioCallback cbk);

   /**
    * @brief Sets the callback for falling edge detection.
    * @param cbk The callback function.
    */
   void setOnFallingCbk(DioCallback cbk);

   /**
    * @brief Sets the callback for low-level detection.
    * @param cbk The callback function.
    */
   void setOnLowCbk(DioCallback cbk);

   /**
    * @brief Sets the callback for high-level detection.
    * @param cbk The callback function.
    */
   void setOnHighCbk(DioCallback cbk);

   /**
    * @brief Executes a callback function.
    * @param cbk The callback function to execute.
    */
   inline void execCallback(DioCallback cbk);
#endif

protected:
   /**
    * @brief Initializes the digital I/O pin with specified pin and mode.
    * @param dio The digital I/O pin number.
    * @param mode The mode for the pin.
    */
   void init(Dio_t dio, Mode_t mode);

   /**
    * @brief Configures the interrupt interface for the specified mode.
    * @param mode The mode for the interrupt.
    */
   void setInterrupInterface(InterruptMode_t mode);

   /**
    * @brief Event handler for processing pin level changes.
    * @param current_level The current level of the pin.
    */
   void eventHandler(Level_t current_level);

public: // Interrupt interfaces
#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_EVENTS
   EVENT_SIGNAL(on_change, Dio*);
   EVENT_SIGNAL(on_rising, Dio*);
   EVENT_SIGNAL(on_falling, Dio*);
   EVENT_SIGNAL(on_low, Dio*);
   EVENT_SIGNAL(on_high, Dio*);
#endif

private:
   static void interruptHandler(Dio* interrupt_source);
#if DIO_ENABLE_INTERRUPT_OUTPUT == DIO_USE_CALLBACKS
   DioCallback m_on_change_callback = nullptr;
   DioCallback m_on_rising_callback = nullptr;
   DioCallback m_on_falling_callback = nullptr;
   DioCallback m_on_low_callback = nullptr;
   DioCallback m_on_high_callback = nullptr;
#endif

   bool changed = false;
   Dio_t m_dio; /**< The digital I/O pin number. */
   Mode_t m_mode; /**< The mode of the pin. */
   InterruptMode_t m_interrupt_mode; /**< The interrupt mode for the pin. */
   DIO_INTERFACE m_interface; /**< The interface for handling interrupts. */
public:
   uint32_t start;
   uint32_t stop;
};

#endif /* _DIO_DIO_H_ */
