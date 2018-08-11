#ifndef _PI_TWI_SLAVE_H_
#define _PI_TWI_SLAVE_H_

#include <stdint.h>
#include <wiringPi.h>
#include <stdio.h>

#define TWI_FREQ        100000

#define TWI_SLA_ADDR    0xa5

typedef struct {
    uint8_t scl;
    uint8_t sda;

    uint8_t active;
    uint8_t byte;
    uint8_t bitcounter;
    uint8_t receiver;
    uint8_t sender;
    uint8_t address_check;
    void (*twi_interrupt_function)(uint8_t);
} twi_s;

struct twi_s twi;

float get_timediff_usec(struct timeval t0, struct timeval t1);
struct timeval get_tnow();
void time_fill(struct timeval t0, uint32_t usec);
void twi_init(uint8_t scl, uint8_t sda, void (*twi_interrupt_function)(uint8_t));
void twi_isr_sda();
void twi_isr_scl();

void twi_check_byte();

#endif /* _PI_TWI_SLAVE_H_ */
