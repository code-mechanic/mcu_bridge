[TOC]

# MCU BRIDGE

MCU agnostic driver

### Start the Docker container

```C
make docker_start # One time execution is fine
```

### Build SDK

#### STM32 MCU setup

```C
make add-stm32-family MCU_BRIDGE_MCU=stm32g4xx
make sdk MCU_BRIDGE_HW=stm32 MCU_BRIDGE_MCU=stm32g4xx MCU_BRIDGE_MCU_VERSION=stm32g474xx
```

### Clean SDK

```C
make clean
```
