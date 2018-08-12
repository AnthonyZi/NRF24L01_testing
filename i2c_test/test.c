#include "twi.h"
#include <util/delay.h>

int main()
{
    char* s = "abcdefghijklmnopqrstuvwxyz";
//    uint8_t data[10];
//    data[0] = 10;
//    data[1] = 179;
//    data[2] = 230;
//    data[3] = 77;
    while(1)
    {
        twi_init(3, 255);
        twi_write_data(0x4d,(uint8_t*)s,26);
        _delay_ms(2000);
    }
}
