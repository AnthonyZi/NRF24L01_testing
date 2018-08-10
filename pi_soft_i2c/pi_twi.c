#include "pi_twi.h"

void twi_pull(uint8_t pin)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay_Microsecondds((1e6/TWI_FREQ)/2);
}

int twi_release(uint8_t pin)
{
    pinMode(pin, INPUT);
    delayMicroseconds((1e6/TWI_FREQ)/2);
    return digitalREAD(pin);
}

void twi_release_wait(uint8_t pin)
{
    int n = 0;
    pinMode(pin, INPUT);
    delayMicroseconds((1e6/TWI_FREQ)/2);
    while(!digitalRead(pin))
    {
        if(++n >= 50)
        {
            if(WARN)
                fprintf(stderr, "WARNING: TWI Bus busy or defective. Pin %d is LOW for 5s.\n", pin);
            return;
        }
        delay(100);
        pinMode(pin,INPUT);
    }
    delayMicroseconds((1e6/TWI_FREQ)/2);
}

twi_lines twi_init(uint8_t scl, uint8_t sda)
{
    twi_lines port;
    port.scl = scl;
    port.sda = sda;

    pinMode(scl, INPUT);
    pinMode(sda, INPUT);
    pullUpDnControl(scl, PUD_UP);
    pullUpDnControl(sda, PUD_UP);

    twi_reset(port);
}

void twi_start(twi_lines port)
{
    if(!twi_release(port.sda))
        twi_reset(port);
    twi_release_wait(port.scl);
    twi_pull(port.sda);
    twi_pull(port.scl);
}

void twi_stop(twi_lines port)
{
    twi_release_wait(port.scl);
    if(!twi_release(port.sda))
        twi_reset(port);
}

void twi_reset(twi_lines port)
{
    int i;
    int n = 0;

    twi_release(port.sda);

    do
    {
        for(i = 0; i<10; i++)
        {
            twi_pull(port.scl);
            twi_release(port.scl);
        }
        if(++n >= 100)
        {
            if(WARN)
                fprintf(stderr, "WARNING: TWI Bus busy or defective. SDA doesn't go UP after reset.\n");
                return;
        }
        delay(10);
    }
    while(!digitalRead(port.sda));

    twi_pull(port.scl);
    twi_pull(port.sda);
    twi_stop(port);
}


void twi_send_bit(twi_lines port, uint8_t bit)
{
    if(bit)
        twi_release(port.sda);
    else
        twi_pull(port.sda);
    twi_release_wait(port.scl);
    twi_pull(port.scl);
    twi_pull(port.sda);
}

int twi_read_bit(twi_lines port)
{
    int s;
    twi_release(port.sda);
    twi_release_wait(port.scl);
    s = digitalRead(port.sda);
    twi_pull(port.scl);
    twi_pull(port.sda);
    return s;
}

int twi_send_byte(twi_lines port, uint8_t byte)
{
    int i;
    for(i=0; i<8; i++)
    {
        twi_send_bit(port, byte & 0x80);
        byte <<= 1;
    }
    return twi_read_bit(port);
}

uint8_t twi_read_byte(twi_lines port)
{
    int byte = 0x00;
    int i;
    for(i=0; i<8; i++)
        byte = (byte<<1) | i2c_read_bit(port);
    return byte;
}
