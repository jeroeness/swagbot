@echo off
d:
cd "D:\Github\swagbot\software\arduino\src"
avrdude -p m2560 -D -c stk500v2 -P com6 -b 115200 -F -V -U flash:w:main.hex
pause