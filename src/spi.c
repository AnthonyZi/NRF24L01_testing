#include "spi.h"

#define PORT_SPI        PORTB
#define DDR_SPI         DDRB
#define DD_MOSI         DDB3
#define DD_MISO         DDB4
#define DD_SCK          DDB5
#define DD_SS           DDB2

void spi_init()
{
    DDR_SPI &= ~((1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS)|(1<<DD_SCK));
    DDR_SPI |= ((1<<DD_MOSI)|(1<<DD_SS)|(1<<DD_SCK));

    SPCR = ((1<<SPE)|(1<<MSTR)|(0<<SPR0));
    SPSR = (1<<SPI2X);
}

void spi_mosi(uint8_t *data_out,uint8_t len)
{
    uint8_t i;
    for(i=0; i<len; i++)
    {
        SPDR = *(data_out+i);
        while((SPSR & (1<<SPIF))==0);
    }
}

void spi_mosi_miso(uint8_t *data_out, uint8_t *data_in,uint8_t len)
{
    uint8_t i;
    for(i=0; i<len; i++)
    {
        SPDR = *(data_out+i);
        while((SPSR & (1<<SPIF))==0);
        *(data_in+i) = SPDR;
    }
}

uint8_t spi_mosi_miso_byte(uint8_t data_out)
{
    SPDR = data_out;
    while((SPSR & (1<<SPIF))==0);
    return SPDR;
}
