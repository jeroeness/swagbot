/*
 * globalincsanddefs.h
 *
 * Created: 14-3-2015 13:04:35
 *  Author: gerald
 */


#ifndef GLOBALINCSANDDEFS_H_
#define GLOBALINCSANDDEFS_H_

#ifndef F_CPU
#define F_CPU 16000000
#endif // F_CPU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/pgmspace.h>
#include <util/delay.h>

#include "lib/sensor.h"
#include "lib/serial.h"
#include "lib/swagbotlib.h"

#include "modules/new_automatic_mode/automatic_mode.h"
#include "modules/communication.h"
#include "modules/i2c_lib.h"
#include "modules/manual_mode.h"
#include "modules/mode_manager.h"
#include "modules/motor.h"
#include "modules/ultrasonic_sensor.h"
#include "modules/startupchecks.h"
#include "modules/startupchecks_ledgrid.h"
#include "modules/ledgrid.h"

#endif /* GLOBALINCSANDDEFS_H_ */
