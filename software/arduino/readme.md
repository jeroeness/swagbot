Arduino Software
=======================

This is the Arduino Codeblocks project (cbp). It's recommended that you use Codeblocks for development in this arduino project. To state the obvious, Codeblocks speeds up the development process.

Using Codeblocks
--------------
When you installed Codeblocks the project probably won't compile out-of-the-box, follow this checklist to make this thing working:
 * setup winAVR and Arduino
 * check if you selected the correct compiler: GNU GCC Compiler for AVR
 * add arduino core directory: go in Codeblocks to > settings > compiler... > select GNU GCC Compiler for AVR > search directories > add the android core directory (e.g. C:\Arduino\hardware\arduino\avr\cores\arduino)

Flashing arduino
--------------
To flash arduino mega 2560 using avrdude:
```
avrdude -p m2560 -P COM3 -c wiring -U flash:w:HEX_FILE_HERE
```