#!/bin/bash
received_data=$(cat /dev/ttyS0)
echo "receieve data: $received_data"
while(received_data == 0xF0)
do  
    echo 123456789
    echo -e -n "\xC6" > /dev/ttyS0
    sleep 1
done

