/*
 * nRF24L01_Tutorial_RX.c
 *
 * Created: 06.01.2012 22:51:57
 *  Author: Ernst Buchmann
 */

#ifndef F_CPU                           //define F_CPU if not done
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "spi.h"
#include "wl_module.h"
#include "nRF24L01.h"

#define DDR_LED1     DDRD
#define DDR_LED2     DDRB
#define PORT_LED1    PORTD
#define PORT_LED2    PORTB

//Variablen
volatile uint8_t PTX;                   //Global Variable
char itoabuffer[20];

void led_init()
{
    DDR_LED1 = 0b11111011;
    DDR_LED2 = 0b00000100;
}

void led_show(uint8_t number)
{
    PORT_LED1 &= 0b00000100;
    PORT_LED1 |= 0b11111011 & number;

    PORT_LED2 &= 0b00000100;
    PORT_LED2 |= (((0b00000100 & number) > 0)<<2);
}

int main(void)
{
        uint8_t payload[wl_module_PAYLOAD];             //holds the payload
        uint8_t nRF_status;                             //STATUS information of nRF24L01+
        uint8_t zaehler = 0;

//        lcd_init();
//        lcd_clear();
        led_init();
        led_show(0);
        wl_module_init();               //Init nRF Module
        _delay_ms(50);                  //wait for Module
        sei();                          //activate Interrupts
        wl_module_config();             //config nRF as RX Module, simple Version

    while(1)
    {
                while (!wl_module_data_ready());            //waits for RX_DR Flag in STATUS
                nRF_status = wl_module_get_data(payload);   //reads the incomming Data to Array payload
                zaehler = payload[0];
                led_show(zaehler);
//                lcd_clear();
//                lcd_home();
//                itoa(zaehler, itoabuffer, 10);              //conversion into String
//                lcd_string(itoabuffer);


    }
}

