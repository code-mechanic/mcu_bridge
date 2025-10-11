TARGET=stm32g4x
INTERFACE=stlink

if [ -z $1 ]; then
    echo "Must provide binary file path"
    exit 1
else
    BIN=$1
fi

openocd -f interface/$INTERFACE.cfg -f target/$TARGET.cfg -c "program $BIN verify reset exit 0x08000000"
