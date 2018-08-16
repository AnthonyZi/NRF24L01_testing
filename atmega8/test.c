#include "spi.h"
#include "twi.h"
#include "rf24.h"
#include <stdlib.h>
#include <string.h>

#define DDR_RF24        DDRD
#define DD_RF24_CE      DDD1
#define DD_RF24_IRQ     DDD2
#define PORT_RF24       PORTD
#define P_RF24_CE       PD1
#define P_RF24_IRQ      PD2

// 6:0 -> use rf channel 2
#define VAR_RF_CHANNEL  0x02
// datarate, tx power, continuous wave, pll lock
#define VAR_RF_SETUP    (RF24_RF_SETUP_RF_DR_250 | RF24_RF_SETUP_RF_PWR_0)
// IRQ setup, enable CRC, CRC-setting, RX/TX POWER UP, RX/TX control
#define VAR_CONFIG      (RF24_CONFIG_MASK_RX_DR | RF24_CONFIG_EN_CRC | RF24_CONFIG_CRCO)

void rf24_init()
{
    // set IRQ as input pin and CE as output pin
    DDR_RF24 &= ~(1<<DD_RF24_IRQ);
    DDR_RF24 |= (1<<DD_RF24_CE);

    // clear CE to for standy/power down mode
    PORT_RF24 &= ~(1<<P_RF24_CE);

    // enable interrupt on IRQ pin (PD2)
    MCUCR = (1<<ISC01)|(0<<ISC00);
    GICR = (1<<INT0);

    spi_init();
}

void rf24_config_register(uint8_t reg, uint8_t value)
{
    uint8_t data[] = {(RF24_W_REGISTER | (RF24_REGISTER_MASK & reg)), value};
    spi_write(data,2);
}

void rf24_config_register_r(uint8_t reg, uint8_t value, uint8_t *output)
{
    uint8_t data[] = {(RF24_W_REGISTER | (RF24_REGISTER_MASK & reg)), value};
    spi_write_read(data, output, 2);
}

void rf24_write_register(uint8_t reg, uint8_t *value, uint8_t len)
{
    uint8_t data_len = len+1;
    uint8_t *data = (uint8_t*)malloc((data_len)*sizeof(uint8_t));
    spi_write(data, data_len);
}

void rf24_write_register_r(uint8_t reg, uint8_t *value, uint8_t *output, uint8_t len)
{
    uint8_t data_len = len+1;
    uint8_t *data = (uint8_t*)malloc((data_len)*sizeof(uint8_t));
    spi_write_read(data, output, data_len);
}


void rf24_config_tx()
{
    rf24_config_register(RF24_RF_CH,VAR_RF_CHANNEL);
    rf24_config_register(RF24_RF_SETUP,VAR_RF_SETUP);
    rf24_config_register(RF24_CONFIG,VAR_CONFIG);
}

void rf24_config_tx_r()
{
    uint8_t debug[2];
    char twi_string[32];

    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"set up RF_CHANNEL");
    twi_write_data(0x44,(uint8_t*)twi_string, 32);

    rf24_config_register_r(RF24_RF_CH,VAR_RF_CHANNEL,debug);

    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"response:");
    twi_write_data(0x44,(uint8_t*)twi_string, 32);
    twi_write_data(0x44,debug,2);


    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"set up RF_SETUP");
    twi_write_data(0x44,(uint8_t*)twi_string, 32);

    rf24_config_register_r(RF24_RF_SETUP,VAR_RF_SETUP,debug);

    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"response:");
    twi_write_data(0x44,(uint8_t*)twi_string, 32);
    twi_write_data(0x44,debug,2);


    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"set up CONFIG");
    twi_write_data(0x44,(uint8_t*)twi_string, 32);

    rf24_config_register_r(RF24_CONFIG,VAR_CONFIG,debug);

    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"response:");
    twi_write_data(0x44,(uint8_t*)twi_string, 32);
    twi_write_data(0x44,debug,2);
}


int main()
{
    twi_init(2,255); //prescaler=2, bitrate=255 -> ~1kHz SCL
    char twi_string[32];
    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"twi_initialised");
    twi_write_data(0x44,(uint8_t*)twi_string, 32);

    rf24_init();
    memset(twi_string, '\0',sizeof(twi_string));
    strcpy(twi_string,"rf24 initialised");
    twi_write_data(0x44,(uint8_t*)twi_string, 32);

    rf24_config_tx_r();
    return 0;
}
