@echo off
set port=%3
REM avrdude.exe -p m2560 -P %port% -c stk500v2 -U flash:w:main.hex -D
avrdude.exe -p m2560 -P %port% -c wiring -U flash:w:%2 -D
start /b putty.exe -serial %port%
