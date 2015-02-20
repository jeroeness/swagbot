@echo off
cd %1
set port=%3
avrdude.exe -p m2560 -P %port% -c wiring -U flash:w:%2
start /b putty -serial %port%