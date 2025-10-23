# Development questions

Refer the Compiler documentation, Specifically the 3rd section `How Tos` to learn more.

1. Which compiler is used for PIC microcontroller?
    - xc8 (xc8-cc)
    - xc16
    - xc32
    - xc-dsc
  
2. Is there any toolchain file available for cmake build system?
    - No official toolchain by Microchip. Need to create a custom

3. Where can i get the xc8 compiler?
   - Refer: https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers/xc8

4. How to verify the version of xc8 compiler once installed?
   - execute `xc8 --help`

5. Where can i found the documentation of xc8 compiler in Website?
    - Under the https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers/xc8 find below documents
      - MPLAB XC8 C Compiler User's Guide for PIC MCU
      - MPLAB XC8 Compiler v3.10 Release Notes for PIC MCU
      - MPLAB XC8 User’s Guide for Embedded Engineers - PIC MCUs
      - MPLAB XC8 User’s Guide for EE- PIC MCU- Code Examples (signin required for MicroChip website)

6. Where can i found the documentation of xc8 compiler once installed?
    - - {COMPILER_INSTALLED_PATH}/microchip/xc8/v2.50/docs

7. Where can I found list of device supported by xc8 compiler?
    - Check Documentation.
    - Once XC8 compiler installed then execute `xc8 --chipinfo`
    - check header files in XC8 include directory

8. Where can I found the compiler include path which container device related headers?
    - {COMPILER_INSTALLED_PATH}/microchip/xc8/v2.50/pic/include/proc/

9.  Where can I get the archive compilers and documents?
    - https://www.microchip.com/en-us/tools-resources/archives/mplab-ecosystem

10. What are the input files that xc8-cc can accept?
    - Refer `Table 4-1. Input File Types` in MPLAB XC8 C Compiler User's Guide for PIC MCU document.

11. When working with xc.h header files, most of the macros are checked for conditional compilation. Where those macros defined?
    - Refer the xc8 compiler documentation for more details. Specifically `5.13.2 Predefined Macros` section.