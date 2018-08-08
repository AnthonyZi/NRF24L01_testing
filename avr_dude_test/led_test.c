#define F_CPU       8000000UL // 1MHz

#include <avr/io.h>
#include <util/delay.h>

#define DDR_LED1    DDRD
#define DDR_LED2    DDRB

#define PORT_LED1   PORTD
#define PORT_LED2   PORTB

void led_init()
{
    DDR_LED1 = 0b11111011;
    DDR_LED2 = 0b00000001;
}

void led_show(uint8_t number)
{
    PORT_LED1 &= 0b00000100;
    PORT_LED1 |= 0b11111011 & number;

    PORT_LED2 &= 0b11111110;
    PORT_LED2 |= (((0b00000100 & number) > 0)<<0);
}

int main(void)
{
    led_init();
    uint8_t counter = 0;
    while(1)
    {
        led_show(counter++);
        _delay_ms(1000);
    }
}
