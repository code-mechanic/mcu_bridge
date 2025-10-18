/*
 * check compiler predefined macro
 */

#ifdef __XC
#warning "MPLAB XC compiler for Microchip is in use"
#else
#warning "__XC is not defined"
#endif

#ifdef __XC8
#warning "MPLAB XC compiler for Microchip 8-bit devices is in use"
#else
#warning "__XC8 is not defined"
#endif

#ifdef __XC8_VERSION
#warning "The compiler version number multiplied by 1000"
#else
#warning "__XC8_VERSION is not defined"
#endif

#ifdef __TRADITIONAL18__
#warning "Non-extended instruction set is selected in PIC18 device"
#else
#warning "__TRADITIONAL18__ is not defined"
#endif

#ifdef __STRICT
#warning "-Wpedantic option is enabled"
#else
#warning "__STRICT is not defined"
#endif

#ifdef __STACK
#warning "indicate the global stack setting: compiled, hybrid or software"
#else
#warning "__STACK is not defined"
#endif

#ifdef __SIZEOF_TYPE__
#warning "Indicates the size in bytes of the specified type"
#else
#warning "__SIZEOF_TYPE__ is not defined"
#endif

#ifdef __RESETBITS_ADDR
#warning "Indicates the address at which STATUS register will be saved"
#else
#warning "__RESETBITS_ADDR is not defined"
#endif

#ifdef __PICC18__
#warning "Not in C18 compatibility mode."
#else
#warning "__PICC18__ is not defined"
#endif

#ifdef __OPTIMIZE_NONE__
#warning "No optimizations are in effect"
#else
#warning "__OPTIMIZE_NONE__ is not defined"
#endif

#ifdef __PICC__
#warning "Building for any PIC10/12/14/16 device"
#else
#warning "__PICC__ is not defined"
#endif

#ifdef _PIC12
#warning "Building for a Baseline device (12-bit instruction)"
#else
#warning "_PIC12 is not defined"
#endif

#ifdef _PIC12E
#warning "Building for an Enhanced Baseline device (12-bit instruction)"
#else
#warning "_PIC12E is not defined"
#endif

#ifdef _PIC12IE
#warning "building for an Enhanced Baseline device with interrupts"
#else
#warning "_PIC12IE is not defined"
#endif

#ifdef _PIC14
#warning "building for an Mid-range device (14-bit instruction)"
#else
#warning "_PIC14 is not defined"
#endif

#ifdef _PIC14E
#warning "building for an Enhanced Mid-range device (14-bit instruction)"
#else
#warning "_PIC14E is not defined"
#endif

#ifdef _PIC14EX
#warning "building for an extended-bank Enhanced Mid-range PIC device (14-bit instruction)"
#else
#warning "_PIC14EX is not defined"
#endif

#ifdef _PIC18
#warning "building for a PIC18 device (16-bit instruction)"
#else
#warning "_PIC18 is not defined"
#endif

#ifdef __18CXX
#warning "18CXX is defined"
#else
#warning "__18CXX is not defined"
#endif
