#ifndef _SPI_H_
#define _SPI_H_
#include <avr/io.h>

void spi_init();
void spi_miso();
void spi_miso_mosi();
uint8_t spi_miso_mosi_byte();

#endif /*_SPI_H_*/
