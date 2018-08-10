#include "twi.h"

void twi_init()
{
    TWSR = 0;
#if F_CPU < 3600000UL
    TWBR = 10;
#else
    TWBR = (F_CPU/(2*SCL_FREQ)) - 8;
#endif
}

// return ...
int twi_start()
{
    while(1)
    {
        TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
        switch(twi_wait_for_twint())
        {
            case TW_REP_START:
                return 0;           // 0:ok -> go on
            case TW_START:
                return 0;           // 0:ok -> go on
            case TW_MT_ARB_LOST:
                break;              // try again
            default:
                return 10;          // 10:error before start -> error
        }
    }
}

//return 
int twi_address(uint8_t address, uint8_t write)
{
    TWDR = (address<<1) | write;
    TWCR = (1<<TWINT) | (1<<TWEN);
    switch(twi_wait_for_twint())
    {
        case TW_MT_SLA_ACK:
            return 0;           // 0:ok -> go on
        case TW_MT_SLA_NACK:
            return 1;           // 1:slave busy -> try again later
        case TW_MT_ARB_LOST:
            return 2;           // 2:ARB_LOST -> try again later
        default:
            return 10;          // 11:error after start -> error
    }
}

int twi_data(uint8_t *data, uint8_t len)
{
    for(; len>0; len--)
    {
        TWDR = *(data++);
        TWCR = (1<<TWINT) | (1<<TWEN);
        switch(twi_wait_for_twint())
        {
            case TW_MT_DATA_NACK:
                return 1;      // 1:slave nacks -> try again later
            case TW_MT_DATA_ACK:
                continue;       // go on
            case TW_MT_ARB_LOST:
                return 2;       // 2:ARB_LOST -> try again later
            default:
                return 10;      // 10:error after start -> error
        }
    }
    return 0;                   // 0:data successfully sent
}


void twi_stop()
{
    TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

// return TW_STATUS
int twi_wait_for_twint()
{
    while((TWCR & (1<<TWINT)) == 0);
    return TW_STATUS;
}


//return:   0:data successfully sent
//          1:problem with start-bit
//          2:problem at address stage
//          3:problem at data stage
//          4:MAX_ATTEMPTS exceeded
int twi_write_data(uint8_t address, uint8_t *data, uint8_t len)
{
    uint8_t attempts = 0;

    while(attempts < MAX_ATTEMPTS)
    {
        switch(twi_start())
        {
            case 0:
                break;
            case 10:
                return 1;              // problem with start bit
        }

        switch(twi_address(address, TW_WRITE))
        {
            case 0:
                break;
            case 1:
                attempts++;
                continue;
            case 2:
                continue;
            case 10:
                twi_stop();
                return 2;
        }

        switch(twi_data(data,len))
        {
            case 0:
                break;
            case 1:
                attempts++;
                continue;
            case 2:
                continue;
            case 10:
                twi_stop();
                return 3;
        }
        return 0;
    }
    return 4;
}
