INTERFACE=stlink

if [ -z $1 ]; then
    TARGET=stm32g4x
else
    TARGET=$1
fi

# Make sure openocd version 0.11.0 installed in host machine
openocd -f interface/$INTERFACE.cfg -f target/$TARGET.cfg -c "bindto 0.0.0.0" -c "gdb_port 3333"
