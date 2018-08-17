#ifndef _RF24_H_
#define _RF24_H_

#define RF24_R_REGISTER                 0x00
#define RF24_W_REGISTER                 0x20
#define RF24_REGISTER_MASK              0x1F
#define RF24_R_RX_PAYLOAD               0x61
#define RF24_W_TX_PAYLOAD               0xA0
#define RF24_FLUSH_TX                   0xE1
#define RF24_FLUSH_RX                   0xE2
#define RF24_RESUE_TX_PL                0xE3
#define RF24_R_RX_PL_WID                0x60
#define RF24_W_ACK_PAYLOAD              0xA8
#define RF24_ACK_PAYLOAD_MASK           0x07
#define RF24_W_TX_PAYLOAD_NOACK         0xB0
#define RF24_NOP                        0xFF


// Register Map
#define RF24_CONFIG                     0x00
#define RF24_CONFIG_MASK_RX_DR          0x40
#define RF24_CONFIG_MASK_TX_DS          0x20
#define RF24_CONFIG_MASK_MAX_RT         0x10
#define RF24_CONFIG_EN_CRC              0x08
#define RF24_CONFIG_CRCO                0x04
#define RF24_CONFIG_PWR_UP              0x02
#define RF24_CONFIG_PRIM_RX             0x01

#define RF24_EN_AA                      0x01
#define RF24_EN_ENAA_P5                 0x20
#define RF24_EN_ENAA_P4                 0x10
#define RF24_EN_ENAA_P3                 0x08
#define RF24_EN_ENAA_P2                 0x04
#define RF24_EN_ENAA_P1                 0x02
#define RF24_EN_ENAA_P0                 0x01

#define RF24_EN_RXADDR                  0x02
#define RF24_EN_RXADDR_ERX_P5           0x20
#define RF24_EN_RXADDR_ERX_P4           0x10
#define RF24_EN_RXADDR_ERX_P3           0x08
#define RF24_EN_RXADDR_ERX_P2           0x04
#define RF24_EN_RXADDR_ERX_P1           0x02
#define RF24_EN_RXADDR_ERX_P0           0x01


#define RF24_SETUP_RETR                 0x04
#define RF24_SETUP_RETR_ARD_4000        0xF0
#define RF24_SETUP_RETR_ARD_3750        0xE0
#define RF24_SETUP_RETR_ARD_3500        0xD0
#define RF24_SETUP_RETR_ARD_3250        0xC0
#define RF24_SETUP_RETR_ARD_3000        0xB0
#define RF24_SETUP_RETR_ARD_2750        0xA0
#define RF24_SETUP_RETR_ARD_2500        0x90
#define RF24_SETUP_RETR_ARD_2250        0x80
#define RF24_SETUP_RETR_ARD_2000        0x70
#define RF24_SETUP_RETR_ARD_1750        0x60
#define RF24_SETUP_RETR_ARD_1500        0x50
#define RF24_SETUP_RETR_ARD_1250        0x40
#define RF24_SETUP_RETR_ARD_1000        0x30
#define RF24_SETUP_RETR_ARD_750         0x20
#define RF24_SETUP_RETR_ARD_500         0x10
#define RF24_SETUP_RETR_ARD_250         0x00
#define RF24_SETUP_RETR_ARC_15          0x0F
#define RF24_SETUP_RETR_ARC_14          0x0E
#define RF24_SETUP_RETR_ARC_13          0x0D
#define RF24_SETUP_RETR_ARC_12          0x0C
#define RF24_SETUP_RETR_ARC_11          0x0B
#define RF24_SETUP_RETR_ARC_10          0x0A
#define RF24_SETUP_RETR_ARC_9           0x09
#define RF24_SETUP_RETR_ARC_8           0x08
#define RF24_SETUP_RETR_ARC_7           0x07
#define RF24_SETUP_RETR_ARC_6           0x06
#define RF24_SETUP_RETR_ARC_5           0x05
#define RF24_SETUP_RETR_ARC_4           0x04
#define RF24_SETUP_RETR_ARC_3           0x03
#define RF24_SETUP_RETR_ARC_2           0x02
#define RF24_SETUP_RETR_ARC_1           0x01
#define RF24_SETUP_RETR_ARC_0           0x00


#define RF24_RF_CH                      0x05


#define RF24_RF_SETUP                   0x06
#define RF24_RF_SETUP_RF_DR_250         0x20
#define RF24_RF_SETUP_RF_DR_1000        0x00
#define RF24_RF_SETUP_RF_DR_2000        0x08
#define RF24_RF_SETUP_CONT_WAVE         0x80
#define RF24_RF_SETUP_PLL_LOCK          0x10
#define RF24_RF_SETUP_RF_PWR_0          0x06
#define RF24_RF_SETUP_RF_PWR_6          0x04
#define RF24_RF_SETUP_RF_PWR_12         0x02
#define RF24_RF_SETUP_RF_PWR_18         0x00


#define RF24_STATUS                     0x07
#define RF24_STATUS_RX_DR               0x40
#define RF24_STATUS_TX_DS               0x20
#define RF24_STATUS_MAX_RT              0x10
#define RF24_STATUS_RX_P_NO             0x0E
#define RF24_STATUS_TX_FULL             0x01


#define RF24_OBSERVE_TX                 0x08
#define RF24_OBSERVE_TX_PLOS_CNT        0xF0
#define RF24_OBSERVE_TX_ARC_CNT         0x0F


#define RF24_RX_ADDR_P0                 0x0A


#define RF24_RX_ADDR_P1                 0x0B


#define RF24_RX_ADDR_P2                 0x0C


#define RF24_RX_ADDR_P3                 0x0D


#define RF24_RX_ADDR_P4                 0x0E


#define RF24_RX_ADDR_P5                 0x0F


#define RF24_TX_ADDR                    0x10


#define RF24_RX_PW_P0                   0x11


#define RF24_RX_PW_P1                   0x12


#define RF24_RX_PW_P2                   0x13


#define RF24_RX_PW_P3                   0x14


#define RF24_RX_PW_P4                   0x15


#define RF24_RX_PW_P5                   0x16


#define RF24_FIFO_STATUS                0x17
#define RF24_FIFO_STATUS_TX_REUSE       0x40
#define RF24_FIFO_STATUS_TX_FULL        0x20
#define RF24_FIFO_STATUS_TX_EMPTY       0x10
#define RF24_FIFO_STATUS_RX_FULL        0x02
#define RF24_FIFO_STATUS_RX_EMPTY       0x01


#define RF24_DYNPD                      0x1C
#define RF24_DYNPD_DPL_P5               0x20
#define RF24_DYNPD_DPL_P4               0x10
#define RF24_DYNPD_DPL_P3               0x08
#define RF24_DYNPD_DPL_P2               0x04
#define RF24_DYNPD_DPL_P1               0x02
#define RF24_DYNPD_DPL_P0               0x01


#define RF24_FEATURE                    0x1D
#define RF24_FEATURE_EN_DPL             0x04
#define RF24_FEATURE_EN_ACK_PAY         0x02
#define RF24_FEATURE_EN_DYN_ACK         0x01


#endif /* _RF24_H_ */
