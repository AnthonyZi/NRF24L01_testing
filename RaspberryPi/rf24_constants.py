R_REGISTER                 = 0x00
W_REGISTER                 = 0x20
REGISTER_MASK              = 0x1F
R_RX_PAYLOAD               = 0x61
W_TX_PAYLOAD               = 0xA0
FLUSH_TX                   = 0xE1
FLUSH_RX                   = 0xE2
RESUE_TX_PL                = 0xE3
R_RX_PL_WID                = 0x60
W_ACK_PAYLOAD              = 0xA8
ACK_PAYLOAD_MASK           = 0x07
W_TX_PAYLOAD_NOACK         = 0xB0
NOP                        = 0xFF


#Register Map
CONFIG                     = 0x00
CONFIG_MASK_RX_DR          = 0x40
CONFIG_MASK_TX_DS          = 0x20
CONFIG_MASK_MAX_RT         = 0x10
CONFIG_EN_CRC              = 0x08
CONFIG_CRCO                = 0x04
CONFIG_PWR_UP              = 0x02
CONFIG_PRIM_RX             = 0x01


EN_AA                      = 0x01
EN_ENAA_P5                 = 0x20
EN_ENAA_P4                 = 0x10
EN_ENAA_P3                 = 0x08
EN_ENAA_P2                 = 0x04
EN_ENAA_P1                 = 0x02
EN_ENAA_P0                 = 0x01


EN_RXADDR                  = 0x02
EN_RXADDR_ERX_P5           = 0x20
EN_RXADDR_ERX_P4           = 0x10
EN_RXADDR_ERX_P3           = 0x08
EN_RXADDR_ERX_P2           = 0x04
EN_RXADDR_ERX_P1           = 0x02
EN_RXADDR_ERX_P0           = 0x01


SETUP_RETR                 = 0x04
SETUP_RETR_ARD_4000        = 0xF0
SETUP_RETR_ARD_3750        = 0xE0
SETUP_RETR_ARD_3500        = 0xD0
SETUP_RETR_ARD_3250        = 0xC0
SETUP_RETR_ARD_3000        = 0xB0
SETUP_RETR_ARD_2750        = 0xA0
SETUP_RETR_ARD_2500        = 0x90
SETUP_RETR_ARD_2250        = 0x80
SETUP_RETR_ARD_2000        = 0x70
SETUP_RETR_ARD_1750        = 0x60
SETUP_RETR_ARD_1500        = 0x50
SETUP_RETR_ARD_1250        = 0x40
SETUP_RETR_ARD_1000        = 0x30
SETUP_RETR_ARD_750         = 0x20
SETUP_RETR_ARD_500         = 0x10
SETUP_RETR_ARD_250         = 0x00
SETUP_RETR_ARC_15          = 0x0F
SETUP_RETR_ARC_14          = 0x0E
SETUP_RETR_ARC_13          = 0x0D
SETUP_RETR_ARC_12          = 0x0C
SETUP_RETR_ARC_11          = 0x0B
SETUP_RETR_ARC_10          = 0x0A
SETUP_RETR_ARC_9           = 0x09
SETUP_RETR_ARC_8           = 0x08
SETUP_RETR_ARC_7           = 0x07
SETUP_RETR_ARC_6           = 0x06
SETUP_RETR_ARC_5           = 0x05
SETUP_RETR_ARC_4           = 0x04
SETUP_RETR_ARC_3           = 0x03
SETUP_RETR_ARC_2           = 0x02
SETUP_RETR_ARC_1           = 0x01
SETUP_RETR_ARC_0           = 0x00


RF_CH                      = 0x05


RF_SETUP                   = 0x06
RF_SETUP_RF_DR_250         = 0x20
RF_SETUP_RF_DR_1000        = 0x00
RF_SETUP_RF_DR_2000        = 0x08
RF_SETUP_CONT_WAVE         = 0x80
RF_SETUP_PLL_LOCK          = 0x10
RF_SETUP_RF_PWR_0          = 0x06
RF_SETUP_RF_PWR_6          = 0x04
RF_SETUP_RF_PWR_12         = 0x02
RF_SETUP_RF_PWR_18         = 0x00


STATUS                     = 0x07
STATUS_RX_DR               = 0x40
STATUS_TX_DS               = 0x20
STATUS_MAX_RT              = 0x10
STATUS_IRQ_MASK            = 0x70
STATUS_RX_P_NO             = 0x0E
STATUS_TX_FULL             = 0x01


OBSERVE_TX                 = 0x08
OBSERVE_TX_PLOS_CNT        = 0xF0
OBSERVE_TX_ARC_CNT         = 0x0F


RX_ADDR_P0                 = 0x0A


RX_ADDR_P1                 = 0x0B


RX_ADDR_P2                 = 0x0C


RX_ADDR_P3                 = 0x0D


RX_ADDR_P4                 = 0x0E


RX_ADDR_P5                 = 0x0F


TX_ADDR                    = 0x10


RX_PW_P0                   = 0x11


RX_PW_P1                   = 0x12


RX_PW_P2                   = 0x13


RX_PW_P3                   = 0x14


RX_PW_P4                   = 0x15


RX_PW_P5                   = 0x16


FIFO_STATUS                = 0x17
FIFO_STATUS_TX_REUSE       = 0x40
FIFO_STATUS_TX_FULL        = 0x20
FIFO_STATUS_TX_EMPTY       = 0x10
FIFO_STATUS_RX_FULL        = 0x02
FIFO_STATUS_RX_EMPTY       = 0x01


DYNPD                      = 0x1C
DYNPD_DPL_P5               = 0x20
DYNPD_DPL_P4               = 0x10
DYNPD_DPL_P3               = 0x08
DYNPD_DPL_P2               = 0x04
DYNPD_DPL_P1               = 0x02
DYNPD_DPL_P0               = 0x01


FEATURE                    = 0x1D
FEATURE_EN_DPL             = 0x04
FEATURE_EN_ACK_PAY         = 0x02
FEATURE_EN_DYN_ACK         = 0x01
