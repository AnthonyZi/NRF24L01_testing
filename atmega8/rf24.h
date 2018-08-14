#ifndef _RF24_H_
#define _RF24_H_

#define RF24_R_REGISTER              0x00
#define RF24_W_REGISTER              0x20
#define RF24_REGISTER_MASK           0x1F
#define RF24_R_RX_PAYLOAD            0x61
#define RF24_W_TX_PAYLOAD            0xA0
#define RF24_FLUSH_TX                0xE1
#define RF24_FLUSH_RX                0xE2
#define RF24_RESUE_TX_PL             0xE3
#define RF24_R_RX_PL_WID             0x60
#define RF24_W_ACK_PAYLOAD           0xA8
#define RF24_ACK_PAYLOAD_MASK        0x07
#define RF24_W_TX_PAYLOAD_NOACK      0xB0
#define RF24_NOP                     0xFF


// Register Map
#define RF24_RF_CH                   0x05

#define RF24_RF_SETUP                0x06
#define RF24_RF_SETUP_RF_DR_250      0x20
#define RF24_RF_SETUP_RF_DR_1000     0x00
#define RF24_RF_SETUP_RF_DR_2000     0x08
#define RF24_RF_SETUP_CONT_WAVE      0x80
#define RF24_RF_SETUP_PLL_LOCK       0x10
#define RF24_RF_SETUP_RF_PWR_0       0x06
#define RF24_RF_SETUP_RF_PWR_6       0x04
#define RF24_RF_SETUP_RF_PWR_12      0x02
#define RF24_RF_SETUP_RF_PWR_18      0x00

#define RF24_CONFIG                  0x00
#define RF24_CONFIG_MASK_RX_DR       0x40
#define RF24_CONFIG_MASK_TX_DS       0x20
#define RF24_CONFIG_MASK_MAX_RT      0x10
#define RF24_CONFIG_EN_CRC           0x08
#define RF24_CONFIG_CRCO             0x04
#define RF24_CONFIG_PWR_UP           0x02
#define RF24_CONFIG_PRIM_RX          0x01

#endif /* _RF24_H_ */
