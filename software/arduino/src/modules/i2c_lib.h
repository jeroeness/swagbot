#ifndef I2CLIBHEADER
#define I2CLIBHEADER

#ifndef I2C_CLOCK
#define I2C_CLOCK 100000UL
#endif

void i2c_init(uint8_t slaveaddress);
void i2c_waitforidle(void);
void i2c_write_cmd_wrap(void);
void i2c_write_cmd(uint8_t);
void i2c_read_sensors(uint8_t amount);
void i2c_continue(void);
void i2c_stop(void);

#endif
