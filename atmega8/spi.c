#include "spi.h"

void spi_init()
{
    // however MISO is automatically declared as input by the spi-interface of atmel
    DDR_SPI &= ~(1<<DD_SPI_MISO);
    DDR_SPI |= (1<<DD_SPI_SCK)|(1<<DD_SPI_MOSI)|(1<<DD_SPI_SS);

    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

    SPI_SS_HI;
}

void spi_write(uint8_t *data_write, uint8_t len)
{
    uint8_t i;
    for(i=0; i<len; i++)
    {
        SPDR = *(data_write+i);
        while((SPSR & (1<<SPIF)) == 0);
    }
}

void spi_write_read(uint8_t *data_write, uint8_t *data_read, uint8_t len)
{
    uint8_t i;
    for(i=0; i<len; i++)
    {
        SPDR = *(data_write+i);
        while((SPSR & (1<<SPIF)) == 0);
        *(data_read+i) = SPDR;
    }
}

void spi_write_byte(uint8_t data_write)
{
    SPDR = data_write;
    while((SPSR & (1<<SPIF)) == 0);
}

uint8_t spi_write_read_byte(uint8_t data_write)
{
    SPDR = data_write;
    while((SPSR & (1<<SPIF)) == 0);
    return SPDR;
}
