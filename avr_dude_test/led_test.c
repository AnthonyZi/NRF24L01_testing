#define F_CPU       1000000UL // 1MHz

#include <avr/io.h>
#include <util/delay.h>

#define DDR_LED     DDRB
#define DD_LED1     DDB0
#define DD_LED2     DDB1

#define PORT_LED    PORTB
#define P_LED1      PB0
#define P_LED2      PB1

void init_leds()
{
    DDR_LED = (1<<DD_LED1);
}

void toggle_leds()
{
    PORT_LED ^= ((1<<P_LED1)|(1<<P_LED2));
}

int main(void)
{
    init_leds();
    while(1)
    {
        toggle_leds();
        _delay_ms(1000);
    }
}
