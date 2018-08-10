//#include <inttypes.h>
//#include <stdio.h>
//#include <stdlib.h>
#ifndef F_CPU
#   define  F_CPU           8000000UL
#endif

#include <avr/io.h>
#include <util/twi.h>

#define  SCL_FREQ        100000UL
#define  MAX_ATTEMPTS    200

void twi_init();

// return ...
int twi_start();

//return ...
int twi_address(uint8_t address, uint8_t write);

int twi_data(uint8_t *data, uint8_t len);

void twi_stop();

// return TW_STATUS
int twi_wait_for_twint();

//return:   0:data successfully sent
//          1:problem with start-bit
//          2:problem at address stage
//          3:problem at data stage
//          4:MAX_ATTEMPTS exceeded
int twi_write_data(uint8_t address, uint8_t *data, uint8_t len);
