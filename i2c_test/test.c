#include "twi.h"
#include <util/delay.h>

int main()
{
    uint8_t data[4];
    data[0] = 0x0a;
    data[1] = 0xb3;
    data[2] = 0x5e;
    data[3] = 0x33;
    while(1)
    {
        twi_init();
        twi_write_data(0xa5,data,4);
        _delay_ms(2000);
    }
}
