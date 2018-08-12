#include "pi_twi_slave.h"

int main()
{
    printf("program_start\n");
    wiringPiSetup();
    twi_s *twi = twi_init(28,29,0x4d);
    twi_listen(twi);
    return 0;
}
