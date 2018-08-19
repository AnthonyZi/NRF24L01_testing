#define  F_CPU           8000000UL

#include "spi.h"
#include "twi.h"
#include "rf24.h"
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#define DDR_RF24        DDRD
#define DD_RF24_CE      DDD1
#define DD_RF24_IRQ     DDD2
#define PORT_RF24       PORTD
#define P_RF24_CE       PD1
#define P_RF24_IRQ      PD2

#define RF24_SS_LO      SPI_SS_LO
#define RF24_SS_HI      SPI_SS_HI
#define RF24_CE_LO      PORT_RF24 &= ~(1<<P_RF24_CE)
#define RF24_CE_HI      PORT_RF24 |= (1<<P_RF24_CE)


// 6:0 -> use rf channel 2
#define VAR_RF_CHANNEL  0x01
// datarate, tx power, continuous wave, pll lock
#define VAR_RF_SETUP    (RF24_RF_SETUP_RF_DR_250 | RF24_RF_SETUP_RF_PWR_18)
// IRQ setup, enable CRC, CRC-setting, RX/TX POWER UP, RX/TX control
#define VAR_CONFIG      (RF24_CONFIG_MASK_RX_DR | RF24_CONFIG_EN_CRC | RF24_CONFIG_CRCO)

void twi_short_message(char *msg)
{
    char twi_string[32];
    memset(twi_string, '\0',sizeof(twi_string));
    memcpy(twi_string, msg, strlen(msg)+1);
    twi_write_data(0x44,(uint8_t*)twi_string, 32);
}

void twi_byte_message(uint8_t b)
{
    twi_write_data(0x44, &b,1);
}

void twi_bytes_message(uint8_t *b, uint8_t len)
{
    twi_write_data(0x44, b, len);
}


void rf24_init()
{
    // set IRQ as input pin and CE as output pin
    DDR_RF24 &= ~(1<<DD_RF24_IRQ);
    DDR_RF24 |= (1<<DD_RF24_CE);

    // clear CE to for standy/power down mode
    PORT_RF24 &= ~(1<<P_RF24_CE);

    // enable interrupt on IRQ pin (PD2)
//    MCUCR = (1<<ISC01)|(0<<ISC00);
//    GICR = (1<<INT0);

    spi_init();
}

void rf24_config_register(uint8_t reg, uint8_t value)
{
    RF24_SS_LO;
    spi_write_byte((RF24_W_REGISTER | (RF24_REGISTER_MASK & reg)));
    spi_write_byte(value);
    RF24_SS_HI;
}

void rf24_write_register(uint8_t reg, uint8_t *value, uint8_t len)
{
    RF24_SS_LO;
    spi_write_byte((RF24_W_REGISTER | (RF24_REGISTER_MASK & reg)));
    spi_write(value,len);
    RF24_SS_HI;
}

void rf24_config_tx()
{
    rf24_config_register(RF24_RF_CH,VAR_RF_CHANNEL);
    rf24_config_register(RF24_RF_SETUP,VAR_RF_SETUP);
    rf24_config_register(RF24_CONFIG,VAR_CONFIG);
    rf24_config_register(RF24_SETUP_RETR,(RF24_SETUP_RETR_ARD_4000 | RF24_SETUP_RETR_ARC_15));
}

uint8_t rf24_read_status()
{
    uint8_t out;
    RF24_SS_LO;
    out = spi_write_read_byte(RF24_NOP);
    RF24_SS_HI;
    return out;
}

void rf24_read_register(uint8_t reg, uint8_t *data_read, uint8_t len)
{
    RF24_SS_LO;
    spi_write_byte((RF24_R_REGISTER | (RF24_REGISTER_MASK & reg)));
    spi_write_read(data_read, data_read, len);
    RF24_SS_HI;
}

uint8_t rf24_read_register_byte(uint8_t reg)
{
    uint8_t out = 0;
    RF24_SS_LO;
    spi_write_byte((RF24_R_REGISTER | (RF24_REGISTER_MASK & reg)));
    out = spi_write_read_byte(out);
    RF24_SS_HI;
    return out;
}

void rf24_send_message(uint8_t *value, uint8_t len)
{
    rf24_config_register(RF24_CONFIG,(VAR_CONFIG | (RF24_CONFIG_PWR_UP)));
    _delay_us(1500);

    RF24_CE_LO;
    _delay_us(130);

    RF24_SS_LO;
    spi_write_byte(RF24_FLUSH_TX);
    RF24_SS_HI;

    rf24_config_register(RF24_STATUS,0x70); //clear bits:6,5,4

    RF24_SS_LO;
    spi_write_byte(RF24_W_TX_PAYLOAD);
    spi_write(value,len);
    RF24_SS_HI;

    RF24_CE_HI;
    _delay_us(10);
    RF24_CE_LO;

    _delay_ms(2);
}



int main()
{
    uint8_t debug;
    uint8_t debug2[8];
    twi_init(3,255); //prescaler=2, bitrate=255 -> ~1kHz SCL
    twi_short_message("twi initialised");

    rf24_init();
    twi_short_message("rf24 initialised");


    rf24_config_tx();
    twi_short_message("rf24 tx configured");

    twi_short_message("Status: ");
    debug = rf24_read_status();
    twi_byte_message(debug);
//
//    twi_short_message("RX_ADDR_P0: ");
//    rf24_read_register(RF24_RX_ADDR_P0,debug2,5);
//    twi_bytes_message(debug2,5);
//
//    twi_short_message("RX_ADDR_P1: ");
//    rf24_read_register(RF24_RX_ADDR_P1,debug2,5);
//    twi_bytes_message(debug2,5);
//
//    twi_short_message("RX_ADDR_P2: ");
//    rf24_read_register(RF24_RX_ADDR_P2,debug2,5);
//    twi_bytes_message(debug2,5);
//
//    twi_short_message("RX_ADDR_P3: ");
//    rf24_read_register(RF24_RX_ADDR_P3,debug2,5);
//    twi_bytes_message(debug2,5);
//
//    twi_short_message("RX_ADDR_P4: ");
//    rf24_read_register(RF24_RX_ADDR_P4,debug2,5);
//    twi_bytes_message(debug2,5);
//
//    twi_short_message("RX_ADDR_P5: ");
//    rf24_read_register(RF24_RX_ADDR_P5,debug2,5);
//    twi_bytes_message(debug2,5);
//
//    twi_short_message("TX_ADDR: ");
//    rf24_read_register(RF24_TX_ADDR,debug2,5);
//    twi_bytes_message(debug2,5);
//
//    twi_short_message("RX_PW_P0: ");
//    debug = rf24_read_register_byte(RF24_RX_PW_P0);
//    twi_byte_message(debug);
//
//    twi_short_message("RX_PW_P1: ");
//    debug = rf24_read_register_byte(RF24_RX_PW_P1);
//    twi_byte_message(debug);
//
//    twi_short_message("RX_PW_P2: ");
//    debug = rf24_read_register_byte(RF24_RX_PW_P2);
//    twi_byte_message(debug);
//
//    twi_short_message("RX_PW_P3: ");
//    debug = rf24_read_register_byte(RF24_RX_PW_P3);
//    twi_byte_message(debug);
//
//    twi_short_message("RX_PW_P4: ");
//    debug = rf24_read_register_byte(RF24_RX_PW_P4);
//    twi_byte_message(debug);
//
//    twi_short_message("RX_PW_P5: ");
//    debug = rf24_read_register_byte(RF24_RX_PW_P5);
//    twi_byte_message(debug);
//
//    twi_short_message("EN_AA: ");
//    debug = rf24_read_register_byte(RF24_EN_AA);
//    twi_byte_message(debug);
//
//    twi_short_message("EN_RXADDR: ");
//    debug = rf24_read_register_byte(RF24_EN_RXADDR);
//    twi_byte_message(debug);
//
//    twi_short_message("RF_CH: ");
//    debug = rf24_read_register_byte(RF24_RF_CH);
//    twi_byte_message(debug);
//
//    twi_short_message("RF_SETUP: ");
//    debug = rf24_read_register_byte(RF24_RF_SETUP);
//    twi_byte_message(debug);
//
//    twi_short_message("CONFIG: ");
//    debug = rf24_read_register_byte(RF24_CONFIG);
//    twi_byte_message(debug);
//
//    twi_short_message("DYNPD: ");
//    debug = rf24_read_register_byte(RF24_DYNPD);
//    twi_byte_message(debug);
//
//    twi_short_message("FEATURE: ");
//    debug = rf24_read_register_byte(RF24_FEATURE);
//    twi_byte_message(debug);
//
//    twi_short_message("sending data");
//    twi_short_message("dummy message");


    uint8_t data[32];
    uint8_t data2[32];
    uint8_t data3[32];
    uint8_t data4[32];
    uint8_t i;
    for(i=0; i<32; i++)
    {
        data[i] = 0;
        data2[i] = 255-i;
        data3[i] = 3*i;
        data4[i] = (i/2*3)/2*i;
    }
    while(1)
    {
        data[0] += 1;
//        twi_short_message("send data");
        rf24_send_message(data,32);
//        twi_short_message("send data2");
//        rf24_send_message(data2,32);
//        twi_short_message("send data3");
//        rf24_send_message(data3,32);
//        twi_short_message("send data4");
//        rf24_send_message(data4,32);
        _delay_ms(1000);
    }


    twi_short_message("dummy message");

}
