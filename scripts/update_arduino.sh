#!/bin/bash

cd ~/quadruped
git pull origin master
cd arduino/hex/

echo 12 > /sys/class/gpio/unexport
echo 24 > /sys/class/gpio/unexport
echo 23 > /sys/class/gpio/unexport
echo 18 > /sys/class/gpio/unexport
sudo avrdude -p atmega328p -c linuxgpio -v -U flash:w:code.ino.hex:i
