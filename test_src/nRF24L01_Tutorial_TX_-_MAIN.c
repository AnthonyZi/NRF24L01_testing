/*
 * nRF24L01_Tutorial_Sender.c
 *
 * Created: 06.01.2012 20:15:04
 *  Author: Ernst Buchmann
 */

#ifndef F_CPU                           //Define F_CPU if not done
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "spi.h"
#include "wl_module.h"
#include "nRF24L01.h"

#include <string.h>

#include "twi.h"
#include <util/delay.h>

int main(void)
{
    uint8_t payload[wl_module_PAYLOAD];             //Array for Payload
    uint8_t maincounter =0;
    uint8_t k;

    twi_init(2,255); //prescaler 2, bitrate 255 -> ~1kHz SCL
    char twi_string[32];
    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"twi_initialised");
    twi_write_data(0x73,(uint8_t*)twi_string, 32);
    _delay_ms(2000);


    wl_module_init();       //initialise nRF24L01+ Module
    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"wl_module_init finished");
    twi_write_data(0x73,(uint8_t*)twi_string, 32);
    _delay_ms(2000);

    _delay_ms(50);          //wait for nRF24L01+ Module
    sei();

    wl_module_tx_config(wl_module_TX_NR_0);         //Config Module
    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"wl_module tx confred");
    twi_write_data(0x73,(uint8_t*)twi_string, 32);
    _delay_ms(2000);

    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"entering while(1)");
    twi_write_data(0x73,(uint8_t*)twi_string, 32);
    _delay_ms(2000);

    while(1)
    {
        memset(twi_string, '\0',sizeof(twi_string));
        strcpy(twi_string,"while");
        twi_write_data(0x73,(uint8_t*)twi_string, 32);

        for (k=0; k<=wl_module_PAYLOAD-1; k++)
        {
            payload[k] = k;
        }

        payload[0] = maincounter;
        payload[1] = maincounter+1;

        wl_module_send(payload,wl_module_PAYLOAD);

        maincounter++;
        if (maincounter >250)
        {
            maincounter = 0;
        }
        _delay_ms(5000);
    }
}
