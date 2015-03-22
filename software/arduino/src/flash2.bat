@echo off
avrdude -p m2560 -D -c stk500v2 -P com6 -b 115200 -F -V -U flash:w:main.hex