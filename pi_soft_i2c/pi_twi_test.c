#include "pi_twi.h"

twi_interrupt(uint8_t byte)
{
    uint8_t i;
    printf("received: ");
    for(i=0; i<8; i++)
    {
        printf("%d", (byte & 1));
        byte >>= 1;
    }
    printf("\n");
}

int main()
{
    twi_init(21,22,&twi_interrupt);
    return 0;
}
