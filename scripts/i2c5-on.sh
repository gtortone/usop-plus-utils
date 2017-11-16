#!/bin/bash

/bin/echo 105 > /sys/class/gpio/export
/bin/echo "out" > /sys/class/gpio/gpio105/direction
/bin/echo "1" > /sys/class/gpio/gpio105/value 
## echo 105 > /sys/class/gpio/unexport
