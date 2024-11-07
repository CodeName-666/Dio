# DIO - Digital I/O Library for Arduino

![DIO Logo](link_to_your_logo_image)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
  - [Creating a Dio Object](#creating-a-dio-object)
  - [Setting the Mode and Status](#setting-the-mode-and-status)
  - [Enabling and Disabling Interrupts](#enabling-and-disabling-interrupts)
  - [Setting Callbacks and Events](#setting-callbacks-and-events)
  - [Creating Interrupts with Macros](#creating-interrupts-with-macros)
  - [Using Events](#using-events)
- [Advanced Configuration](#advanced-configuration)
- [Examples](#examples)
- [Debugging and Troubleshooting](#debugging-and-troubleshooting)
- [Platform Compatibility](#platform-compatibility)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The DIO library provides a convenient and flexible way to work with digital input and output pins on Arduino boards. This library abstracts low-level details, allowing users to easily configure pins, set modes, manage interrupts, and execute callbacks or events in response to changes in pin levels.

## Features

- Abstraction for digital I/O pin management.
- Support for various interrupt modes: Rising edge, Falling edge, Change, Low level, and High level (on compatible platforms).
- Easy-to-use callback system or event system for responding to pin state changes.
- Cross-platform compatibility with Arduino boards (e.g., AVR, ESP32, ESP8266).
- Flexible configuration options using macros in `Dio_Config.h`.

## Installation

To use the DIO library, follow these steps:

1. Download the DIO library from the GitHub repository: [DIO Library](https://github.com/your_username/DIO-library).
2. Extract the downloaded folder to your Arduino libraries directory (usually located at `Documents/Arduino/libraries`).
3. Restart the Arduino IDE.

## Usage

### Creating a Dio Object

To manage a digital pin, create a `Dio` object and specify the pin number and mode. Modes can be `DIO_AS_INPUT`, `DIO_AS_OUTPUT`, or `DIO_AS_INPUT_WITH_PULLUP`.

```cpp
#include <Dio.h>

Dio myPin(13, DIO_AS_OUTPUT); // Create a Dio object for pin 13 in output mode
```

### Setting the Mode and Status

You can set the mode and status (level) of the digital pin using the following methods:

```cpp
myPin.setMode(DIO_AS_INPUT);    // Set the pin to input mode
myPin.set(DIO_HIGH);            // Set the pin level to high
```

### Enabling and Disabling Interrupts

The DIO library provides support for various interrupt modes. You can enable and disable interrupts on a pin and specify a callback function or event to be executed when the interrupt occurs.

```cpp
myPin.enableInterrupts(INTERRUPT_ON_RISING, myRisingCallback);  // Enable rising edge interrupt
myPin.disableInterrupts();                                      // Disable interrupts
```

### Setting Callbacks and Events

You can set different callbacks or events for various interrupt events using the following methods:

```cpp
myPin.setOnChangeCbk(myChangeCallback);
myPin.setOnRisingCbk(myRisingCallback);
myPin.setOnFallingCbk(myFallingCallback);
myPin.setOnLowCbk(myLowCallback);
myPin.setOnHighCbk(myHighCallback);
```

Alternatively, switch `DIO_ENABLE_INTERRUPT_OUTPUT` to `DIO_USE_EVENTS` to handle events instead of callbacks. Events provide a more flexible way to handle complex interrupt scenarios.

### Creating Interrupts with Macros

The library provides macros to simplify the creation of interrupt functions and pointers. These macros help to standardize the way you define and handle interrupts.

#### DIO_CREATE_INTERRUPT

The `DIO_CREATE_INTERRUPT` macro is used to define the interrupt function associated with a specific `Dio` object. It automatically calls the corresponding `onInterrupt` method of the object.

```cpp
DIO_CREATE_INTERRUPT(myPin);  // Creates an interrupt function for myPin
```

#### DIO_INTERRUPT_PTR

The `DIO_INTERRUPT_PTR` macro is used to obtain a pointer to the interrupt function created with `DIO_CREATE_INTERRUPT`.

```cpp
DioInterrupt myInterruptPtr = DIO_INTERRUPT_PTR(myPin);  // Get the pointer to the interrupt function of myPin
```

### Using Events

The DIO library's event system can be utilized to connect signals and slots, allowing for advanced event-driven programming. Here is how you can use events with `Dio`:

1. **Defining Event Signals and Slots**: Use the `EVENT_SIGNAL` macro to create signals and the `EVENT_SLOT` macro to create slots.

2. **Connecting Events**: Use the `EVENT_CONNECT` macro to connect a signal to a slot.

3. **Emitting Events**: Use the `EVENT_EMIT` macro to emit a signal.

#### Example: Using Event Signals and Slots

```cpp
#include <Dio.h>
#include "Event.h"

Dio eventPin(5, DIO_AS_INPUT);
EVENT_SIGNAL(onPinChange, Dio*);

void onPinChangeHandler(Dio* dioInstance) {
    // Handle the pin change event
    Serial.println("Pin state changed!");
}

void setup() {
    Serial.begin(9600);
    eventPin.init();
    EVENT_CONNECT(eventPin.m_on_change_signal, onPinChangeHandler);
    eventPin.enableInterrupts(INTERRUPT_ON_CHANGE, []() {
        EVENT_EMIT(eventPin.m_on_change_signal, &eventPin);
    });
}

void loop() {
    // Main loop logic
}
```

## Advanced Configuration

The library uses preprocessor directives like `DIO_ENABLE_INTERRUPT_OUTPUT` to configure whether callbacks or events are used. Adjust these settings in `Dio_Config.h` to customize the behavior of the library according to your project's requirements.

## Examples

### Example 1: Blinking LED

```cpp
#include <Dio.h>

Dio ledPin(13, DIO_AS_OUTPUT);

void setup() {
  ledPin.init();
}

void loop() {
  ledPin.set(DIO_HIGH);
  delay(1000);
  ledPin.set(DIO_LOW);
  delay(1000);
}
```

### Example 2: Interrupt-based Button

```cpp
#include <Dio.h>

Dio buttonPin(2, DIO_AS_INPUT_WITH_PULLUP);

void setup() {
  buttonPin.init();
  buttonPin.enableInterrupts(INTERRUPT_ON_FALLING, buttonPressCallback);
}

void loop() {
  // Main loop logic
}

void buttonPressCallback() {
  // Handle button press event
}
```

### Example 3: Using Macros for Interrupts

```cpp
#include <Dio.h>

Dio myPin(2, DIO_AS_INPUT);
DIO_CREATE_INTERRUPT(myPin);

void setup() {
  myPin.init();
  myPin.enableInterrupts(INTERRUPT_ON_CHANGE, DIO_INTERRUPT_PTR(myPin));
}

void loop() {
  // Continuous main loop logic
}
```

### Example 4: Using Events

```cpp
#include <Dio.h>
#include "Event.h"

Dio eventPin(5, DIO_AS_INPUT);
EVENT_SIGNAL(onPinChange, Dio*);

void onPinChangeHandler(Dio* dioInstance) {
    // Handle the pin change event
    Serial.println("Pin state changed!");
}

void setup() {
    Serial.begin(9600);
    eventPin.init();
    EVENT_CONNECT(eventPin.m_on_change_signal, onPinChangeHandler);
    eventPin.enableInterrupts(INTERRUPT_ON_CHANGE, []() {
        EVENT_EMIT(eventPin.m_on_change_signal, &eventPin);
    });
}

void loop() {
    // Main loop logic
}
```

## Debugging and Troubleshooting

- Ensure `Dio_Config.h` is configured correctly for your platform.
- Verify that the correct pin numbers and modes are used.
- For platforms like ESP32, ensure compatibility with the specific pin functions and interrupts.
- Use `Serial.print()` statements in callbacks to help debug the flow of interrupt handling.

## Platform Compatibility

This library supports the following platforms:
- AVR-based boards (e.g., Arduino Uno, Mega)
- ESP32
- ESP8266

Ensure that your platform's configuration supports the defined macros and interrupt modes in `Dio_Config.h`.

## Contributing

Contributions to the

