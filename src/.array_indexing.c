#include <stdio.h>
#include <stdint.h>

void increment1(uint8_t *vals, uint8_t len)
{
    int i;
    for(i=0; i<len; i++)
    {
        vals[i] += 1;
    }
}

void increment2(uint8_t *vals, uint8_t len)
{
    int i;
    for(i=0; i<len; i++)
    {
        *(vals+i) += 1;
    }
}

void print_byte(uint8_t byte)
{
    int i;
    for(i=0; i<8; i++)
    {
        printf("%d",((byte & 0b10000000)>0));
        byte <<= 1;
    }
    printf(" ");
}

void print_arr(uint8_t *vals, uint8_t len)
{
    int i;
    for(i=0; i<len; i++)
    {
        print_byte(*(vals+i));
    }
    printf("\n");
}



int main()
{
    uint8_t data[2];
    data[0] = 0xFF;
    data[1] = 0x1A;

    print_arr(data,2);
    increment1(data,2);
    print_arr(data,2);
    increment2(data,2);
    print_arr(data,2);
}
