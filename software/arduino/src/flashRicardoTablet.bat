@echo off
cd "C:\Users\ricardo\Documents\GitHub\swagbot\software\arduino\src"
avrdude -p m2560 -D -c stk500v2 -P com14 -b 115200 -F -V -U flash:w:main.hex
pause