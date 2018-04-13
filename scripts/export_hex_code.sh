#!/bin/bash

cd ~/Dropbox/robotics/quadruped/
find /var/folders/pt -name  "code.ino.hex" -exec cp {} ~/Dropbox/robotics/quadruped/arduino/hex/ \;
git add .
git commit -m "Hex code updated"
git push origin master

