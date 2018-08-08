#define F_CPU       8000000UL // 1MHz

#include <avr/io.h>
#include <util/delay.h>

#define DDR_LED     DDRD

#define PORT_LED    PORTB

void init_leds()
{
    DDR_LED = 0xFF
}

void led_show(uint8_t number)
{
    PORT_LED = number;
}

int main(void)
{
    init_leds();
    uint8_t counter = 0;
    while(1)
    {
        led_show(counter++);
        _delay_ms(1000);
    }
}
