import rf24_interface as rf24i
import rf24_constants as rf24c
import time

def callback_irq(irq_vector):
    rx_data_ready,tx_data_sent,max_retransmissions = irq_vector
    if rx_data_ready:
        print("RX Data Ready")
    if tx_data_sent:
        print("TX Data Sent")
    if max_retransmissions:
        print("Max Retransmission Attempts Interrupt")

if __name__ == "__main__":
    time.sleep(1)
    print("init rf24")
    radio = rf24i.RF24_Interface(interrupt_callback=callback_irq)

    time.sleep(1)
    print("set rx")
    radio.set_rx()
    time.sleep(1)
    print("power up")
    radio.power_up()
    time.sleep(1)
    print("chip enableup")
    radio.chip_enable()

    print("status:")
    print(hex(radio.read_status()))
    print("RX_ADDR_P0:")
    print([hex(b) for b in radio.read_register(rf24c.RX_ADDR_P0, 5)])
    print("RX_ADDR_P1:")
    print([hex(b) for b in radio.read_register(rf24c.RX_ADDR_P1, 5)])
    print("RX_ADDR_P2:")
    print([hex(b) for b in radio.read_register(rf24c.RX_ADDR_P2, 5)])
    print("RX_ADDR_P3:")
    print([hex(b) for b in radio.read_register(rf24c.RX_ADDR_P3, 5)])
    print("RX_ADDR_P4:")
    print([hex(b) for b in radio.read_register(rf24c.RX_ADDR_P4, 5)])
    print("RX_ADDR_P5:")
    print([hex(b) for b in radio.read_register(rf24c.RX_ADDR_P5, 5)])
    print("RX_PW_P0:")
    print(hex(radio.read_register_byte(rf24c.RX_PW_P0)))
    print("RX_PW_P1:")
    print(hex(radio.read_register_byte(rf24c.RX_PW_P1)))
    print("RX_PW_P2:")
    print(hex(radio.read_register_byte(rf24c.RX_PW_P2)))
    print("RX_PW_P3:")
    print(hex(radio.read_register_byte(rf24c.RX_PW_P3)))
    print("RX_PW_P4:")
    print(hex(radio.read_register_byte(rf24c.RX_PW_P4)))
    print("RX_PW_P5:")
    print(hex(radio.read_register_byte(rf24c.RX_PW_P5)))
    print("EN_AA:")
    print(hex(radio.read_register_byte(rf24c.EN_AA)))
    print("EN_RXADDR:")
    print(hex(radio.read_register_byte(rf24c.EN_RXADDR)))
    print("RF_CH:")
    print(hex(radio.read_register_byte(rf24c.RF_CH)))
    print("RF_SETUP:")
    print(hex(radio.read_register_byte(rf24c.RF_SETUP)))
    print("CONFIG:")
    print(hex(radio.read_register_byte(rf24c.CONFIG)))
    print("DYNPD:")
    print(hex(radio.read_register_byte(rf24c.DYNPD)))
    print("FEATURE:")
    print(hex(radio.read_register_byte(rf24c.FEATURE)))

    while True:
        time.sleep(1)
        received = radio.data_received()
        if(received > 0):
            print(received)
