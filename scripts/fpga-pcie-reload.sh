#!/bin/bash
/bin/echo 92 > /sys/class/gpio/export
/bin/echo out > /sys/class/gpio/gpio92/direction
/bin/echo 0 > /sys/class/gpio/gpio92/value
/bin/echo 1 > /sys/class/gpio/gpio92/value
/bin/echo 92 > /sys/class/gpio/unexport
/bin/sleep 5
/bin/echo 1 > /sys/bus/pci/rescan 
