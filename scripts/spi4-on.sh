#!/bin/bash

/bin/echo 106 > /sys/class/gpio/export
/bin/echo "out" > /sys/class/gpio/gpio106/direction
/bin/echo "1" > /sys/class/gpio/gpio106/value 
## echo 106 > /sys/class/gpio/unexport
