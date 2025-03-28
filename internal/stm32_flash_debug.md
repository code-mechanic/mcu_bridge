# Embedded VScode

## VScode Extentions

1. [Makefile Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools)
2. [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
3. [cortex-debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)

## Resolving include path missing for C/C++

1. Create a `c_cpp_properties.json` file under `.vscode` directory and add below configurations.

    ```json
    {
        "configurations": [
            {
                "name": "Linux",
                "includePath":
                [
                    "${workspaceRoot}",
                    "${workspaceRoot}/Core/Inc",
                    "${workspaceRoot}/Drivers/STM32F4xx_HAL_Driver/Inc",
                    "${workspaceRoot}/Drivers/CMSIS/Include",
                    "${workspaceRoot}/Drivers/CMSIS/Device/ST/STM32F4xx/Include",
                    "/usr/arm-none-eabi/include",
                    "/usr/arm-none-eabi/include/c++/10.2.0",
                    "/lib/gcc/arm-none-eabi/10.2.0/include",
                    "/lib/gcc/arm-none-eabi/10.2.0/include-fixed",
                    "/usr/arm-none-eabi/include/machine",
                    "/usr/arm-none-eabi/include/newlib-nano",
                    "/usr/arm-none-eabi/include/sys"
                ],
                "defines":
                [
                    "USE_HAL_DRIVER",
                    "STM32F407xx"
                ],
                "intelliSenseMode": "linux-gcc-x64",
                "cStandard": "c11",
                "cppStandard": "c++20",
                "browse":
                {
                    "path":
                    [
                        "${workspaceRoot}",
                        "${workspaceRoot}/Core/Inc",
                        "${workspaceRoot}/Drivers/STM32F4xx_HAL_Driver/Inc",
                        "${workspaceRoot}/Drivers/CMSIS/Include",
                        "${workspaceRoot}/Drivers/CMSIS/Device/ST/STM32F4xx/Include",
                        "/usr/arm-none-eabi/include",
                        "/usr/arm-none-eabi/include/c++/10.2.0",
                        "/lib/gcc/arm-none-eabi/10.2.0/include",
                        "/lib/gcc/arm-none-eabi/10.2.0/include-fixed"
                    ],
                    "limitSymbolsToIncludedHeaders": true,
                    "databaseFilename": "${workspaceRoot}/.vscode/browse.vc.db"
                }
            }
        ],
        "version": 4
    }
    ```

2. Add the include path directory in `includePath` key property so that VScode know where the file located.
3. `defines` key property let the preprocessor to know where the code located.

## How to create a build tasks in VScode

1. `ctrl + p`
2. type `>Tasks: Configure Task`
3. click `Create task.json file from template` -> `others`
4. Add below configuration

    ```json
    {
        "version": "2.0.0",
        "tasks": [
            {
                "label": "task1",
                "group": "build",
                "type": "shell",
                "command": "echo",
                "args": [
                    "Hello",
                    "task1"
                ]
            },
            {
                "label": "task2",
                "group": "build",
                "type": "shell",
                "command": "echo",
                "args": [
                    "Hello",
                    "task2"
                ]
            },
            {
                "label": "JFlash",
                "group": "build",
                "type": "shell",
                "command": "make",
                "args": ["-j4","jflash"]
            },
            {
                "label": "STflash",
                "group": "build",
                "type": "shell",
                "command": "make",
                "args": ["-j4","stflash"]
            },
            {
                "label": "UARTFlash",
                "group": "build",
                "type": "shell",
                "command": "make",
                // Replace PORT= with your UART port
                // Linux has ttyUSBx or ttyACMx, windows has COMx
                "args": ["-j4","uflash", "PORT=/dev/ttyUSB1"]
            }
        ]
    }
    ```

5. To invoke build task use `ctrl + shift + b`

## Flashing STM32 MCU

There are many methods to flash STM32 MCU but here are the 5 ways to flash firmware onto STM32 using 3 different interfaces (stlink, jlink, uart bootloader)

1. ST-LINK: `STM32CubeProgrammer (gui)`
    - use [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) to flash MCU.

2. ST-LINK: `ST-Flash (terminal)`
    - In linux: use `sudo apt install stlink-tools` to install stlink tools for flashing using terminal.
    - [GitHub link](https://github.com/stlink-org/stlink) to install from source code.
    - once  installation is done use below command to flash STM32 MCU
        - `st-flash --reset write <path/to/bin/file> 0x08000000`
    - Below target in Make file will be useful in automation.

        ```Makefile
        # FLash with ST-LINK
        stflash: $(BUILD_DIR)/$(TARGET).bin
            st-flash --reset write $< 0x8000000
        ```

3. JLINK: `Interactive terminal method`
    - Download [jlink](https://www.segger.com/downloads/jlink/) software.
    - Once downloaded, go inside the downloaded package and run `JLinkExe` to start jlink software.
    - Use below commands inside jlink
        - `connect`
        - select device
        - specify the target interface.
        - `loadbin <path/to/bin/file> 0x08000000`
        - `r` - reset the hardware
        - `g` - run the hardware
        - `qc` - to exit the JLinkExe software

4. JLINK: `Automated download using Make`
    - Below target in Make file will be useful in automation.

        ```Makefile
        # Flash with J-Link
        # Configure device name, everything else should remain the same
        jflash: $(BUILD_DIR)/jflash
            JLinkExe -commanderscript $<

        # Change to yours
        device = STM32F407VG

        # First create a file with all commands
        $(BUILD_DIR)/jflash: $(BUILD_DIR)/$(TARGET).bin
            @touch $@
            @echo device $(device) > $@
            @echo -e si 1'\n'speed 4000 >> $@
            @echo loadbin $< 0x8000000 >> $@
            @echo -e r'\n'g'\n'qc >> $@
        ```

    - Add a [VScode task](#how-to-create-a-build-tasks-in-vscode) as well for automation

5. stm32flash: `ST serial bootloader over UART`
    - Download [stm32flash](https://sourceforge.net/p/stm32flash/wiki/Home/) software.
    - Download [Application note](https://www.st.com/resource/en/application_note/an3155-usart-protocol-used-in-the-stm32-bootloader-stmicroelectronics.pdf) on USART protocol used in the STM32 bootloader for reference.
    - Download [Application note](https://www.st.com/resource/en/application_note/an2606-stm32-microcontroller-system-memory-boot-mode-stmicroelectronics.pdf) on ntroduction to system memory boot mode on STM32 MCUs for reference.
    - Below target in Make file will be useful in automation.

        ```Makefile
        # Flash with UART module
        # If you have problem with flashing but it does connect,
        # remove '-e 0' so that it will erase flash contents and
        # flash firmware fresh
        uflash: $(BUILD_DIR)/$(TARGET).bin
            # This one is used if you have UART module with RTS and DTR pins
            stm32flash -b 115200 -e 0 -R -i rts,dtr,-rts:rts,-dtr,-rts -v -w $< $(PORT)
            # Else use this one and manualy set your MCU to bootloader mode
            #stm32flash -b 115200 -e 0 -v -w $< $(PORT)
        ```

    - Add a [VScode task](#how-to-create-a-build-tasks-in-vscode) as well for automation

## Debugging STM32 in VScode

### MCU Debuggers Overview

| **Debugger (HW Probe)**                             | **Host-side Software/IDE/Tools**                                                             | **MCU/SoC Companies Supported**                                         | **Cost**                                                    |
| --------------------------------------------------- | -------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------- | ----------------------------------------------------------- |
| **ST-LINK / ST-LINK V3**                            | STM32CubeIDE, STM32CubeProgrammer, OpenOCD, stlink-tools, GDB                                | STMicroelectronics (STM32, STM8)                                        | **Free** (on Nucleo/Discovery boards) / Low-cost standalone |
| **J-Link (Segger)**                                 | J-Link Software (GDB Server, J-Flash), IDEs (Keil, IAR, Eclipse, VS Code), OpenOCD (partial) | Multi-vendor: ST, NXP, Renesas, TI, Nordic, Microchip, SiLabs, etc.     | **Paid** (Edu version free for hobby use)                   |
| **CMSIS-DAP / DAPLink** (ARM mbed, LPC-Link2, etc.) | pyOCD, Keil µVision (free edition), OpenOCD, GDB                                             | ARM Cortex-M MCUs (NXP, ST, TI, Microchip SAM, etc.)                    | **Free** (on dev boards)                                    |
| **TI XDS110 / XDS200 / XDS560**                     | Code Composer Studio (CCS), OpenOCD (partial)                                                | Texas Instruments (MSP430, Tiva, C2000, Sitara, etc.)                   | **Paid** (some XDS110 on LaunchPads free)                   |
| **PEMicro Multilink / Cyclone**                     | PEmicro tools, GDB server, IAR, Keil                                                         | NXP (Kinetis, ColdFire, PowerPC), ST, Renesas, etc.                     | **Paid**                                                    |
| **Lauterbach TRACE32**                              | TRACE32 PowerView software                                                                   | ARM (Cortex-M/A/R), RISC-V, Infineon, NXP, Renesas, TI, ST, many others | **Paid (very expensive)**                                   |
| **Microchip PICkit / ICD4**                         | MPLAB X IDE                                                                                  | Microchip (PIC, dsPIC, AVR, SAM)                                        | **Paid** (low-cost)                                         |
| **Atmel-ICE**                                       | Microchip Studio (free), OpenOCD, GDB                                                        | Microchip/Atmel (AVR, SAM ARM Cortex-M)                                 | **Paid**                                                    |
| **NXP LinkServer (LPC-Link2, MCU-Link)**            | MCUXpresso IDE, pyOCD, GDB                                                                   | NXP (LPC, i.MX RT, Kinetis)                                             | **Free** (bundled with boards) / Low-cost standalone        |
| **SiLabs USB Debug Adapter / WSTK**                 | Simplicity Studio IDE                                                                        | Silicon Labs (EFM32, EFR32)                                             | **Free** (included in kits) / Paid standalone               |
| **RISC-V Probes (SiFive, OpenOCD-compatible)**      | OpenOCD, GDB, Freedom Studio, VS Code                                                        | RISC-V based SoCs (SiFive, Microchip PolarFire, etc.)                   | **Free** (dev boards)                                       |
| **FTDI-based Adapters (Olimex ARM-USB-TINY, etc.)** | OpenOCD, GDB                                                                                 | Generic ARM Cortex-M, RISC-V (depends on config)                        | **Low-cost / Paid**                                         |

### Stlink and Jlink debugger

- Hardware debugger probe comparison
  - `stlink`: [STlink tools pverview](https://www.st.com/resource/en/product_presentation/stlink-debugging-and-programming-tools-overview.pdf)
  - `jlink` : [Jlink probe](https://www.segger.com/products/debug-probes/j-link/#comparison)

- Software for stlink and jlink debugger probe upgrade and reflash
  - `stlink`: Use [firmware upgrade application](https://www.st.com/en/development-tools/stsw-link007.html) to updrade STlink debugger.
  - `jlink` : Use [ST-LINK on-board](https://www.segger.com/products/debug-probes/j-link/models/other-j-links/st-link-on-board/) to converting ST-LINK On-Board into a J-Link.

- Host-side software for stlink and jlink debugger
  - `stlink`: Use `st-utils` software to debug which can be obtained by executing `sudo apt install stlink-tools`.
  - `stlink`: Use `openocd` software to debug which can be obtained by executing `sudo apt install openocd`.
  - `jlink` : Use `JLinkGDBServer` software to debug which can be obtained in [segger J-Link / J-Trace Downloads](https://www.segger.com/downloads/jlink/) page.

- VSCode Cortex-Debug configuration
  - Create `setting.json` under .vscode folder and add below configurations.

    ```json
    {
        "cortex-debug.gdbPath": "/path/to/bin/arm-none-eabi-gdb",
        // "cortex-debug.gdbPath": "/path/to/bin/gdb-multiarch",
        "cortex-debug.JLinkGDBServerPath": "/path/to/bin/JLinkGDBServer",
        "cortex-debug.stutilPath": "/path/to/bin/st-util",
        "cortex-debug.openocdPath": "/path/to/bin/openocd"
    }
    ```

  - Create launch.json under .vscode folder and add below configurations.

    ```json
    // Configure debug launch settings
    // Feel free to copy these and modify them for your debugger and MCU
    {
        "version": "0.2.0",
        "projectName": "test-f407vg",
        "configurations": [
            {
                "name": "JLink launch",
                "cwd": "${workspaceRoot}",
                "executable": "${workspaceRoot}/build/test-f407vg.elf",
                "request": "launch",
                "type": "cortex-debug",
                "servertype": "jlink",
                "device": "STM32F407VG",
                "interface": "swd",
                "runToMain": true, // else it starts at reset handler - not interested
                "preLaunchTask": "Build all", // configured in tasks.json
                // "preLaunchCommands": ["Build all"], // you can execute command instead of task
                "svdFile": "", // Include svd to watch device peripherals
                "swoConfig":
                {
                    "enabled": true,
                    "cpuFrequency": 160000000,
                    "swoFrequency": 4000000,
                    "source": "probe",
                    "decoders":
                    [
                        {
                            "label": "ITM port 0 output",
                            "type": "console",
                            "port": 0,
                            "showOnStartup": true,
                            "encoding": "ascii"
                        }
                    ]
                }
            },
            {
                "name": "JLink attach",
                "cwd": "${workspaceRoot}",
                "executable": "${workspaceRoot}/build/test-f407vg.elf",
                "request": "attach",
                "type": "cortex-debug",
                "servertype": "jlink",
                "device": "STM32F407VG",
                "interface": "swd",
                "runToMain": true, // else it starts at reset handler - not interested
                "preLaunchTask": "Build all", // configured in tasks.json
                // "preLaunchCommands": ["Build all"], // you can execute command instead of task
                "svdFile": "", // Include svd to watch device peripherals
                "swoConfig":
                {
                    "enabled": true,
                    "cpuFrequency": 160000000,
                    "swoFrequency": 4000000,
                    "source": "probe",
                    "decoders":
                    [
                        {
                            "label": "ITM port 0 output",
                            "type": "console",
                            "port": 0,
                            "showOnStartup": true,
                            "encoding": "ascii"
                        }
                    ]
                }
            },
            {
                "name": "STlink launch",
                "cwd": "${workspaceRoot}",
                "executable": "${workspaceRoot}/build/test-f407vg.elf",
                "request": "launch",
                "type": "cortex-debug",
                "servertype": "stutil",
                "device": "STM32F407VG",
                "interface": "swd",
                "runToMain": true, // else it starts at reset handler - not interested
                "preLaunchTask": "Build all", // configured in tasks.json
                // "preLaunchCommands": ["Build all"], // you can execute command instead of task
                "svdFile": "", // Include svd to watch device peripherals
                "swoConfig": {} // currently (v1.7.0) not supported
            },
            {
                "name": "STlink attach",
                "cwd": "${workspaceRoot}",
                "executable": "${workspaceRoot}/build/test-f407vg.elf",
                "request": "attach",
                "type": "cortex-debug",
                "servertype": "stutil",
                "device": "STM32F407VG",
                "interface": "swd",
                "runToMain": true, // else it starts at reset handler - not interested
                "preLaunchTask": "Build all", // configured in tasks.json
                // "preLaunchCommands": ["Build all"], // you can execute command instead of task
                "svdFile": "", // Include svd to watch device peripherals
                "swoConfig": {} // currently (v1.7.0) not supported
            },
            {
                "name": "Debug with OpenOCD",
                "cwd": "${workspaceRoot}",
                "executable": "/path/to/elf",
                "request": "launch",
                "type": "cortex-debug",
                "servertype": "openocd",
                "device": "stm32g474re",
                "interface": "swd",
                "configFiles": [
                    "/usr/share/openocd/scripts/interface/stlink.cfg",
                    "/usr/share/openocd/scripts/target/stm32g4x.cfg"
                ],
                "searchDir": [],
                "runToEntryPoint": "main",
                "showDevDebugOutput": "none"
            }
        ]
    }
    ```
