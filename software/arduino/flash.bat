@echo off
cd %1
set port=%3
avrdude.exe -p m2560 -P %port% -c stk500v2 -U flash:w:%2 -D
start /b E:\"Program Files (x86)"\Putty\putty.exe -serial %port%
cd ..