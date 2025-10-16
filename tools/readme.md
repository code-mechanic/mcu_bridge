
# Debug STM32 MCU with OpenOCD

Build Application with debug option

## Host side
1. Connect the MCU to host machine.
2. Run the `openocd_start_gdb_server.sh <STM MCU: stm32g4x>` on Host side and keep GDB server running.
3. Run the command `make docker_check_gdb` to make sure GDB server is reachable in docker side.
    - `Connection to host.docker.internal 3333 port [tcp/*] succeeded!` will appear.

## Docker side
1. Connect the VSCode to the container `mcu_bridge_builder`.
2. Configure `launch.json`.
3. Click `Run and Debug` symbol or `ctrl + shift + D`.
4. Then debug binary.