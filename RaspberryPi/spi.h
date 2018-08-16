#ifndef _SPI_H_
#define _SPI_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define DDR_SPI         DDRB
#define DD_SPI_SS       DDB2
#define DD_SPI_MOSI     DDB3
#define DD_SPI_MISO     DDB4
#define DD_SPI_SCK      DDB5
#define PORT_SPI        PORTB
#define P_SPI_SS        PB2
#define P_SPI_MOSI      PB3
#define P_SPI_MISO      PB4
#define P_SPI_SCK       PB5

#define SPI_SS_HI               PORT_SPI |= (1<<P_SPI_SS)
#define SPI_SS_LO               PORT_SPI &= ~(1<<P_SPI_SS)

void spi_init();

void spi_write(uint8_t *data_write, uint8_t len);
void spi_write_read(uint8_t *data_write, uint8_t *data_read, uint8_t len);

void spi_write_byte(uint8_t data_write);
uint8_t spi_write_read_byte(uint8_t data_write);

#endif /* _SPI_H_ */
