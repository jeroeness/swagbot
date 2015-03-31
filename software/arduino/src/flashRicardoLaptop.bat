@echo off
cd "C:\Users\Jucko13\Documents\GitHub\swagbot\software\arduino\src"
avrdude -p m2560 -D -c stk500v2 -P com7 -b 115200 -F -V -U flash:w:main.hex
pause