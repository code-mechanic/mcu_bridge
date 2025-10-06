# MCU BRIDGE

MCU agnostic driver

- [MCU BRIDGE](#mcu-bridge)
  - [Start the Docker container](#start-the-docker-container)
  - [Build MCU Bridge](#build-mcu-bridge)
    - [STM32 MCU build](#stm32-mcu-build)
      - [STM32F0xx series](#stm32f0xx-series)
      - [STM32F1xx series](#stm32f1xx-series)
      - [STM32G0xx series](#stm32g0xx-series)
      - [STM32G4xx series](#stm32g4xx-series)
    - [STM32 MCU environment setup](#stm32-mcu-environment-setup)
    - [Build for STM32](#build-for-stm32)
  - [Clean MCU Bridge](#clean-mcu-bridge)

## Start the Docker container

```C
make docker_start # One time execution is fine
```

## Build MCU Bridge

### STM32 MCU build

- For all the STM32 MCU, MCU Bridge will get the dependancy from [STMicroelectronics](https://github.com/STMicroelectronics) github.
- While building STM32 HAL, MCU Bridge will ignore all the source files (.c) that ends with `_template.c`.
- Almost all the STM32 MCU supported in MCU Bridge. Below table contains the details.

#### STM32F0xx series

| MCU_BRIDGE_HW | MCU_BRIDGE_MCU |
| ------------- | -------------- |
| stm32         | **stm32f0xx**  |

| MCU_BRIDGE_MCU_VERSION |
| ---------------------- |
| stm32f030x6            |
| stm32f030x8            |
| stm32f031x6            |
| stm32f038xx            |
| stm32f042x6            |
| stm32f048xx            |
| stm32f051x8            |
| stm32f058xx            |
| stm32f070x6            |
| stm32f070xb            |
| stm32f071xb            |
| stm32f072xb            |
| stm32f078xx            |
| stm32f091xc            |
| stm32f098xx            |
| stm32f030xc            |

#### STM32F1xx series

| MCU_BRIDGE_HW | MCU_BRIDGE_MCU |
| ------------- | -------------- |
| stm32         | **stm32f1xx**  |

| MCU_BRIDGE_MCU_VERSION |
| ---------------------- |
| stm32f100xb            |
| stm32f100xe            |
| stm32f101x6            |
| stm32f101xb            |
| stm32f101xe            |
| stm32f101xg            |
| stm32f102x6            |
| stm32f102xb            |
| stm32f103x6            |
| stm32f103xb            |
| stm32f103xe            |
| stm32f103xg            |
| stm32f105xc            |
| stm32f107xc            |

#### STM32G0xx series

| MCU_BRIDGE_HW | MCU_BRIDGE_MCU |
| ------------- | -------------- |
| stm32         | **stm32g0xx**  |

| MCU_BRIDGE_MCU_VERSION |
| ---------------------- |
| stm32g0b1xx            |
| stm32g0c1xx            |
| stm32g0b0xx            |
| stm32g071xx            |
| stm32g081xx            |
| stm32g070xx            |
| stm32g031xx            |
| stm32g041xx            |
| stm32g030xx            |
| stm32g051xx            |
| stm32g061xx            |
| stm32g050xx            |

#### STM32G4xx series

| MCU_BRIDGE_HW | MCU_BRIDGE_MCU |
| ------------- | -------------- |
| stm32         | **stm32g4xx**  |

| MCU_BRIDGE_MCU_VERSION |
| ---------------------- |
| stm32g474xx            |
| stm32g431xx            |
| stm32g441xx            |
| stm32g471xx            |
| stm32g473xx            |
| stm32g483xx            |
| stm32g474xx            |
| stm32g484xx            |
| stm32g491xx            |
| stm32g4a1xx            |
| stm32gbk1cb            |
| stm32g411xb            |
| stm32g411xc            |
| stm32g414xx            |

### STM32 MCU environment setup

1. Get the required STM32 MCU HAL layer. The below commands will clone the STM32 HAL layer under the `external/stm32` and place the HAL configuration file under the `config/stm32/$(MCU_BRIDGE_MCU)_hal_confh`.

```C
make add-stm32-family MCU_BRIDGE_MCU=stm32g4xx
make add-cmsis-5
```

2. If required, Update the `config/stm32/$(MCU_BRIDGE_MCU)_hal_confh` based on requirement.

3. If required, Update the STM32 specific compiler flags in `STM32_MCU_FLAGS` cmake variable available under `cmake/toolchain/stm32_toolchain-arm-none-eabi.cmake`.
    - Compiler version used in MCU Bridge is `gcc-arm-none-eabi-10.3-2021.10`
    - Refer the [GCC](https://gcc.gnu.org/onlinedocs/gcc-10.3.0/gcc/) document for more info on [ARM options](https://gcc.gnu.org/onlinedocs/gcc-10.3.0/gcc/ARM-Options.html#ARM-Options).

### Build for STM32

Method 1:

```C
make mcu_bridge MCU_BRIDGE_HW=stm32 MCU_BRIDGE_MCU=stm32g4xx MCU_BRIDGE_MCU_VERSION=stm32g474xx
```

Method 2:

- Update the required variables in `config/developement_config.mk`
- execute `make mcu_bridge`

## Clean MCU Bridge

```C
make clean
```
