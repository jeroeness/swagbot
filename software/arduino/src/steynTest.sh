#/bin/sh
sudo avrdude -p m2560 -D -c stk500v2 -P /dev/ttyACM0 -b 115200 -F -V -U flash:w:main.hex
sudo screen /dev/ttyACM0 19200
