import spidev
import rf24_constants as rf24c
import RPi.GPIO as GPIO

class RF24_Interface(object):
    def __init__(self, interrupt_callback, payload_size=32, bus=0, ss=0):

        self.extern_interrupt_callback = interrupt_callback
        self.payload_size = payload_size

        self.rf_channel = 0x01
        self.rf_setup = (rf24c.RF_SETUP_RF_DR_250)
        self.config_init = (rf24c.CONFIG_MASK_TX_DS |\
                            rf24c.CONFIG_MASK_MAX_RT |\
                            rf24c.CONFIG_EN_CRC |\
                            rf24c.CONFIG_CRCO)
        self.config = self.config_init
        self.setup_retr = (rf24c.SETUP_RETR_ARD_4000 | rf24c.SETUP_RETR_ARC_15)

        self.spi_init(bus, ss)
        self.gpio_init()
        self.rf24_init()

    def spi_init(self, bus, ss):
        self.spi = spidev.SpiDev()
        self.spi.open(bus,ss)
        self.spi.bits_per_word = 8
        self.spi.cshigh = False
        self.spi.lsbfirst = False
        self.spi.max_speed_hz = 9*(10**6) # MHz
        self.spi.mode = 0b00

    def gpio_init(self):
        self.CE_PIN      = 22
        self.IRQ_PIN     = 25
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.CE_PIN, GPIO.OUT, initial=GPIO.LOW)
        GPIO.setup(self.IRQ_PIN, GPIO.IN)
        GPIO.add_event_detect(self.IRQ_PIN, GPIO.FALLING)
        GPIO.add_event_callback(self.IRQ_PIN, callback=self.callback_IRQ)

    def rf24_init(self):
        self.write_register(rf24c.RF_CH, self.rf_channel)
        self.write_register(rf24c.RF_SETUP, self.rf_setup)
        self.write_register(rf24c.CONFIG, self.config_init)
        self.write_register(rf24c.SETUP_RETR, self.setup_retr)

###############################################################################

    def set_payload_size(self, payload_size):
        self.payload_size = payload_size

###############################################################################

    def write_register(self, register, value):
        if isinstance(value, list):
            spi_data = [ (rf24c.W_REGISTER | (rf24c.REGISTER_MASK & register)), *value ]
        else:
            spi_data = [ (rf24c.W_REGISTER | (rf24c.REGISTER_MASK & register)), value ]
        self.spi.xfer2(spi_data)

    def read_status(self):
        return self.spi.xfer2([rf24c.NOP])[-1]

    def read_register_byte(self, register):
        spi_data = [ (rf24c.R_REGISTER | (rf24c.REGISTER_MASK & register)), 0]
        return self.spi.xfer2(spi_data)[-1]

    def read_register(self, register, length):
        spi_data = [ (rf24c.R_REGISTER | (rf24c.REGISTER_MASK & register)), *([0]*length) ]
        return self.spi.xfer2(spi_data)[1:]


    def callback_IRQ(self,channel):
        status = self.read_status()
        rx_data_ready       = (status & rf24c.STATUS_RX_DR) > 0
        tx_data_sent        = (status & rf24c.STATUS_TX_DS) > 0
        max_retransmissions = (status & rf24c.STATUS_MAX_RT) > 0

        irq_vector = rx_data_ready,tx_data_sent,max_retransmissions
        self.extern_interrupt_callback(irq_vector)

    def power_up(self, state="ON"):
        if state == "ON":
            self.config = (self.config | rf24c.CONFIG_PWR_UP)
        else:
            self.config = (self.config & (~rf24c.CONFIG_PWR_UP))
        self.write_register(rf24c.CONFIG, self.config)

    def power_down(self):
        self.power_up(state="OFF")

    def chip_enable(self, state="ON"):
        if state == "ON":
            GPIO.output(self.CE_PIN, GPIO.HIGH)
        else:
            GPIO.output(self.CE_PIN, GPIO.LOW)

    def chip_disable(self):
        self.chip_enable("OFF")

    def read_payload(self):
        spi_data = [ rf24c.R_RX_PAYLOAD, *([0]*self.payload_size)]
        return self.spi.xfer2(spi_data)[1:]

    def clear_interrupts(self, rx_dr=False, tx_ds=False, max_rt=False):
        status = 0
        if rx_dr:
            status = status | rf24c.STATUS_RX_DR
        if tx_ds:
            status = status | rf24c.STATUS_TX_DS
        if max_rt:
            status = status | rf24c.STATUS_MAX_RT

        status = status & rf24c.STATUS_IRQ_MASK
        self.write_register(rf24c.STATUS, status)

    def read_all_payloads(self):
        data = []

        data.append(self.read_payload())
        self.clear_interrupts(rx_dr=True)

        while not (self.read_register_byte(rf24c.FIFO_STATUS) & rf24c.FIFO_STATUS_RX_EMPTY)>0:
            data.append(self.read_payload())
            self.clear_interrupts(rx_dr=True)
        return data


###############################################################################

    def set_tx(self):
        self.config = self.config & ~(rf24c.CONFIG_PRIM_RX)
        self.write_register(rf24c.CONFIG, self.config)

    def set_rx(self):
        self.config = self.config | rf24c.CONFIG_PRIM_RX
        self.write_register(rf24c.CONFIG, self.config)
        self.write_register(rf24c.RX_PW_P0, self.payload_size)
        self.write_register(rf24c.EN_RXADDR, rf24c.EN_RXADDR_ERX_P0)

    def data_received(self):
        status = self.read_status()
        rx_available_pipes = (status & rf24c.STATUS_RX_P_NO)>>1
        if rx_available_pipes == 0x07:
            return -1
        else:
            return rx_available_pipes


    def print_details(self):
        print("status:")
        print(hex(self.read_status()))
        print("RX_ADDR_P0:")
        print([hex(b) for b in self.read_register(rf24c.RX_ADDR_P0, 5)])
        print("RX_ADDR_P1:")
        print([hex(b) for b in self.read_register(rf24c.RX_ADDR_P1, 5)])
        print("RX_ADDR_P2:")
        print([hex(b) for b in self.read_register(rf24c.RX_ADDR_P2, 5)])
        print("RX_ADDR_P3:")
        print([hex(b) for b in self.read_register(rf24c.RX_ADDR_P3, 5)])
        print("RX_ADDR_P4:")
        print([hex(b) for b in self.read_register(rf24c.RX_ADDR_P4, 5)])
        print("RX_ADDR_P5:")
        print([hex(b) for b in self.read_register(rf24c.RX_ADDR_P5, 5)])
        print("RX_PW_P0:")
        print(hex(self.read_register_byte(rf24c.RX_PW_P0)))
        print("RX_PW_P1:")
        print(hex(self.read_register_byte(rf24c.RX_PW_P1)))
        print("RX_PW_P2:")
        print(hex(self.read_register_byte(rf24c.RX_PW_P2)))
        print("RX_PW_P3:")
        print(hex(self.read_register_byte(rf24c.RX_PW_P3)))
        print("RX_PW_P4:")
        print(hex(self.read_register_byte(rf24c.RX_PW_P4)))
        print("RX_PW_P5:")
        print(hex(self.read_register_byte(rf24c.RX_PW_P5)))
        print("EN_AA:")
        print(hex(self.read_register_byte(rf24c.EN_AA)))
        print("EN_RXADDR:")
        print(hex(self.read_register_byte(rf24c.EN_RXADDR)))
        print("RF_CH:")
        print(hex(self.read_register_byte(rf24c.RF_CH)))
        print("RF_SETUP:")
        print(hex(self.read_register_byte(rf24c.RF_SETUP)))
        print("CONFIG:")
        print(hex(self.read_register_byte(rf24c.CONFIG)))
        print("DYNPD:")
        print(hex(self.read_register_byte(rf24c.DYNPD)))
        print("FEATURE:")
        print(hex(self.read_register_byte(rf24c.FEATURE)))
