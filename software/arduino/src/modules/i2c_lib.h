// i2c_lib.h

#ifndef I2CLIBHEADER
#define I2CLIBHEADER

#include "../globalincsanddefs.h"

void i2c_init(uint8_t);
void i2c_waitforidle(void);

void i2c_writeToRP6(void);
void i2c_readFromRP6(void);
void i2c_readFromCompass(void);

void i2c_write(uint8_t, uint8_t, uint8_t, uint8_t);
void i2c_read(uint8_t, uint8_t, uint8_t, uint8_t);
void i2c_continue(void);
void i2c_stop(void);

void i2c_SR_done(void);
void i2c_MR_done(void);

#endif
