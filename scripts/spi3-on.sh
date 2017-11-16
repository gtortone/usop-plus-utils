#!/bin/bash

/bin/echo 94 > /sys/class/gpio/export
/bin/echo "out" > /sys/class/gpio/gpio94/direction
/bin/echo "1" > /sys/class/gpio/gpio94/value 
## echo 94 > /sys/class/gpio/unexport
