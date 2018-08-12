#include "pi_twi_slave.h"

//struct timeval t0; gettimeofday(&t0, NULL);
float get_timediff_usec(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec-t0.tv_sec)*1e6f + (t1.tv_usec-t0.tv_usec);
}

struct timeval get_tnow()
{
    struct timeval t0;
    gettimeofday(&t0, NULL);
    return t0;
}

void time_fill(struct timeval t0, uint32_t usec)
{
    struct timeval t1 = get_tnow();
    uint32_t t_fill_now = (uint32_t)get_timediff_usec(t0, t1);
    uint32_t t_fill_rest = usec-t_fill_now;
    delayMicroseconds(t_fill_rest);
}

void twi_init(uint8_t scl, uint8_t sda, void (*twi_interrupt_function)(uint8_t))
{
    twi.scl = scl;
    twi.sda = sda;

    pinMode(twi.scl, INPUT);
    pinMode(twi.sda, INPUT);
    pullUpDnControl(twi.scl, PUD_OFF);
    pullUpDnControl(twi.sda, PUD_OFF);

    if(wiringPiISR(twi.sda,INT_EDGE_BOTH, &twi_isr_sda) < 0)
        fprintf(stderr, "Unable to setup ISR for SDA");
    if(wiringPiISR(twi.scl,INT_EDGE_BOTH, &twi_isr_scl) < 0)
        fprintf(stderr, "Unable to setup ISR for SCL");

    twi.byte = 0;
    twi.twi_interrupt_function = twi_interrupt_function;
    twi_reset();
//    twi_reset(port);
}

void twi_reset()
{
    twi.active = 0;
    twi.bitcounter = 0;
    twi.receiver = 1;
    twi.sender = 0;
    twi.address_check = 1;
}

void twi_scl_pull()
{
    pinMode(twi.scl, OUTPUT);
    digitalWrite(twi.scl, 0);
}

void twi_scl_release()
{
    pinMode(twi.scl, INPUT);
}

void twi_isr_sda()
{
    printf("d");
    if(digitalRead(twi.scl))            // SCL_HIGH -> START or STOP condition
    {
        if(digitalRead(twi.sda))        // SDA_RISING -> STOP
        {
            twi.active = 0;
            printf(" stop\n");
            twi_reset();
        }
        else                            // SDA_FALLING -> START
        {
            twi.active = 1;
            printf(" start\n");
        }
        fflush(stdout);
    }
}

void twi_isr_scl()
{
    printf("c");
    if(twi.active)
    {
        if(twi.receiver)
        {
            if(digitalRead(twi.scl))    // SCL_RISING
            {
                twi.byte = (twi.byte << 1) | digitalRead(twi.sda);
                printf(" %d",(twi.byte & 1));
                twi.bitcounter += 1;

                if(twi.bitcounter == 8)
                {
                    twi_check_byte();
                    twi.bitcounter = 0;
                }
                fflush(stdout);
            }
        }
    }
}

void twi_check_byte()
{
    if(twi.address_check)
    {
        if(twi.byte != TWI_SLA_ADDR)
            twi.receiver = 0;
    }
    else
    {
        twi.twi_interrupt_function(twi.byte);
    }
}
