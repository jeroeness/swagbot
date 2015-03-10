@echo off
set port=%3
avrdude.exe -p m2560 -P %port% -c stk500v2 -U flash:w:main.hex -D
start /b E:\"Program Files (x86)"\Putty\putty.exe -serial %port%
