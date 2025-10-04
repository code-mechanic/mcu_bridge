# Build Analysis tools

## List of build artifacts

| File Type                          | Tool(s)                                       | Info You Get                                                                                                                                                                                          |
| ---------------------------------- | --------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **`.o` (Object file)**     | `nm`                                        | Defined/undefined symbols, globals, functions                                                                                                                                                         |
|                                    | `objdump -d`                                | Disassembly of compiled code                                                                                                                                                                          |
|                                    | `readelf -Ws`                               | Symbol table with addresses & sections                                                                                                                                                                |
|                                    | `size`                                      | Contribution to `.text`, `.data`, `.bss`                                                                                                                                                        |
| **`.elf` (Executable)**    | `nm`                                        | Final resolved symbols                                                                                                                                                                                |
|                                    | `objdump -d`                                | Full program disassembly                                                                                                                                                                              |
|                                    | `readelf -Wa`                               | ELF headers, sections, symbol table, relocation                                                                                                                                                       |
|                                    | `size`                                      | Flash vs RAM usage (text/data/bss)                                                                                                                                                                    |
|                                    | `gdb`                                       | Debugging with source/assembly mapping                                                                                                                                                                |
| **`.bin` (Raw binary)**    | `hexdump -C`                                | Raw bytes + ASCII dump                                                                                                                                                                                |
|                                    | `xxd`                                       | Hex + ASCII side-by-side                                                                                                                                                                              |
|                                    | `cmp`                                       | Compare binaries for differences                                                                                                                                                                      |
|                                    | `binwalk`                                   | Detect firmware structure, padding, embedded data                                                                                                                                                     |
| **`.a` (Static library)**  | `ar -t`                                     | List `.o` files in archive                                                                                                                                                                          |
|                                    | `nm`                                        | Symbols provided by the library                                                                                                                                                                       |
|                                    | `objdump -d`                                | Disassembly of included object files                                                                                                                                                                  |
|                                    | `size`                                      | Memory contribution per object file                                                                                                                                                                   |
| **`.so` (Shared library)** | `nm -D`                                     | Exported/imported dynamic symbols                                                                                                                                                                     |
|                                    | `objdump -T`                                | Symbol table with version info                                                                                                                                                                        |
|                                    | `readelf -Wd`                               | Dynamic section (relocations, needed libs)                                                                                                                                                            |
|                                    | `ldd`                                       | Dependency list (other shared libs required)                                                                                                                                                          |
| **`.map` (Linker Map)**    | Generated by linker (`-Wl,-Map=output.map`) | Complete memory map (address of each function/variable), section placement (`.text`, `.data`, `.bss`), symbol sizes, ROM vs RAM usage breakdown, identification of duplicate or missing symbols |

## nm symbols details

| **Letter** | **Section** | **Meaning**                                                      | **Typical Example in C**          |
| ---------------- | ----------------- | ---------------------------------------------------------------------- | --------------------------------------- |
| **T**      | `.text`         | Global**function** (defined in this file).                       | `void foo() {}`                       |
| **t**      | `.text`         | Local (static)**function**.                                      | `static void bar() {}`                |
| **D**      | `.data`         | Global**initialized variable**.                                  | `int x = 5;`                          |
| **d**      | `.data`         | Local (static)**initialized variable**.                          | `static int y = 7;`                   |
| **B**      | `.bss`          | Global**uninitialized variable**.                                | `int z;`                              |
| **b**      | `.bss`          | Local (static)**uninitialized variable**.                        | `static int q;`                       |
| **R**      | `.rodata`       | Global**read-only data**.                                        | `const int k = 10;`                   |
| **r**      | `.rodata`       | Local (static)**read-only data**.                                | `static const int m = 20;`            |
| **U**      | (undefined)       | Symbol declared but not defined here (needs to be resolved by linker). | `extern int w;`                       |
| **W**      | (any)             | **Weak function** — can be overridden by a strong symbol.       | `__attribute__((weak)) void f() {}`   |
| **w**      | (any)             | Local weak function.                                                   | Rare                                    |
| **V**      | (any)             | Weak object (variable).                                                | `__attribute__((weak)) int x;`        |
| **v**      | (any)             | Local weak object.                                                     | Rare                                    |
| **C**      | Common            | Tentative definition (uninitialized global, may merge across files).   | `int g;` (without `-fno-common`)    |
| **A**      | Absolute          | Absolute symbol (fixed addr, not relocatable).                         | Linker-provided value (e.g.,`_etext`) |
| **N**      | Debug only        | Debugging symbol (line numbers, file paths).                           | Appears only with `-g`.               |

```plain
+------------------------------------------------------+
|                     Flash (ROM)                      |
|                                                      |
|  .text      --> Code / Functions (T, t)              |
|                (global + static functions)           |
|                                                      |
|  .rodata    --> Read-only data (R, r)                |
|                (const vars, string literals)         |
|                                                      |
+------------------------------------------------------+
|                     RAM (SRAM)                       |
|                                                      |
|  .data      --> Initialized variables (D, d)         |
|                (copied from Flash at startup)        |
|                                                      |
|  .bss       --> Uninitialized variables (B, b)       |
|                (zero-initialized at startup)         |
|                                                      |
|  Heap       --> malloc/new area (grows upward)       |
|                                                      |
|  Stack      --> Local vars, function frames          |
|                (grows downward)                      |
|                                                      |
+------------------------------------------------------+
```
