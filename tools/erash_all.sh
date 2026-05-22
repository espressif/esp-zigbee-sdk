#!/bin/bash

ESPTOOL_HELP="$(python -m esptool --help 2>&1)"

if [[ "$ESPTOOL_HELP" == *"erase_flash"* ]]; then
    ERASE_OP="erase_flash"
elif [[ "$ESPTOOL_HELP" == *"erase-flash"* ]]; then
    ERASE_OP="erase-flash"
else
    echo "Failed to find a supported esptool erase flash operation." >&2
    exit 1
fi

for port in /dev/ttyUSB* /dev/ttyACM*; do
    [ -e "$port" ] || continue
    (
        echo "Erasing flash on $port"
        python -m esptool --port "$port" "$ERASE_OP"
    ) &
    sleep 0.1
done

wait

echo "All erase operations completed."
