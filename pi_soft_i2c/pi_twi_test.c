#include "pi_twi.h"

int main()
{
    twi_lines port = twi_init(23,24);
    twi_reset(port);
    return 0;
}
