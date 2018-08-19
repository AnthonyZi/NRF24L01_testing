import rf24_interface as rf24i
import rf24_constants as rf24c
import time

class BaseStation(object):
    def __init__(self):
        self.radio = rf24i.RF24_Interface(interrupt_callback=self.callback_rf24)

    def callback_rf24(self,irq_vector):
        rx_dr,tx_ds,max_rt = irq_vector
        if rx_dr: # rx data ready
            self.read_received_packets()
        if tx_ds: # tx data sent -> disabled in rf24_interface
            pass
        if max_rt: # max retransmissions -> disabled in rf24_interface
            pass

    def read_received_packets(self):
        data = self.radio.read_all_payloads()
        for d in data:
            print(d)

###############################################################################

    def enable_receiver(self):
        self.radio.power_up()
        time.sleep(0.0015)
        self.radio.set_rx()
        self.radio.chip_enable()
        time.sleep(0.00013)
