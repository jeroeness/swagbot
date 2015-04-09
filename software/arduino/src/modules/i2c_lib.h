// i2c_lib.h

#ifndef I2CLIBHEADER
#define I2CLIBHEADER

#include "../globalincsanddefs.h"

void i2c_init(void);
void i2c_writeToRP6(void);
void i2c_readFromRP6(void);
void i2c_SendCompassCalibrateCmd(void);
void i2c_readFromCompass(void);
void i2c_initCalibration(void);


// i2c core \/ .
void i2c_change_slave_buffers(uint8_t *, uint8_t, uint8_t *, uint8_t);
void i2c_init_M_S(uint8_t own_SLA, uint8_t *, uint8_t, uint8_t *, uint8_t);
void i2c_init_M(void);
uint8_t i2c_checkstatus(void);
void i2c_waitforidle(void);
void i2c_callback_attach(void (*i2c_master_Done) (void), void (*i2c_slave_Done) (void), void (*i2c_error) (void));
void i2c_write(uint8_t, uint8_t, uint8_t *, uint8_t);
void i2c_read(uint8_t, uint8_t, uint8_t *, uint8_t);
void i2c_continue(void);
void i2c_stop(void);
// i2c core /\ .

#endif
