# MCU Bridge

## Overview

The **MCU-Agnostic Driver Framework** is a portable and modular software layer designed to work seamlessly across multiple microcontroller families — such as **STM32**, **PIC**, **AVR**, and **TI**.  

It abstracts vendor-specific hardware details into a unified and consistent API layer, enabling developers to write platform-independent embedded applications with minimal code changes.

---

## Documentation Structure

- **API Reference** — Detailed documentation for all drivers (GPIO, UART, SPI, I2C, etc.)
- **HAL Integration Layer** — Describes how the vendor HALs are integrated into this framework.
- **Configuration & Build Guide** — Information on how to configure, build, and integrate the SDK.
- **Examples** — Real use cases demonstrating initialization, configuration, and peripheral usage.
- **Porting Guide** — Steps to add support for a new MCU family.

---

## Getting Started

1. Browse the **Modules** or **Files** section from the sidebar to explore the available APIs.
2. Review the **Examples** section for quick start code samples.
3. Refer to the **Porting Guide** to add a new microcontroller or vendor HAL.

---

## Developer Notes

This framework follows:

- **Modular architecture** — Each driver is independent and loosely coupled.
- **MCU abstraction** — Hardware differences are hidden behind generic APIs.
- **Portable C code** — Compatible with multiple compilers and toolchains.
- **Memory-efficient design** — Suitable for low-resource embedded systems.

---

## Block Diagram

\image html mcu_bridge_block_diagram.jpg "Software block diagram"
