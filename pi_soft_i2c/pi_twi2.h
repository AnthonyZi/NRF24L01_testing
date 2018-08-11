#ifndef _PI_I2C_H_
#define _PI_I2C_H_

#include <stdint.h>
#include <wiringPi.h>
#include <stdio.h>

#define TWI_READ    1
#define TWI_WRITE   0
#define TWI_ACK     0
#define TWI_NACK    1

#define TWI_FREQ    100000

#define WARN        1

typedef struct {
    uint8_t scl;
    uint8_t sda;
} twi_lines;

void twi_pull(uint8_t pin);

uint8_t twi_release(uint8_t pin);

// release line and wait until it goes up
void twi_release_wait(uint8_t pin);

twi_lines twi_init(uint8_t scl, uint8_t sda);

void twi_start(twi_lines port);
void twi_stop(twi_lines port);
void twi_reset(twi_lines port);
void twi_send_bit(twi_lines port, uint8_t bit);
uint8_t twi_read_bit(twi_lines port);
uint8_t twi_send_byte(twi_lines port, uint8_t byte);
uint8_t twi_read_byte(twi_lines);

#endif /* _PI_I2C_H_ */
