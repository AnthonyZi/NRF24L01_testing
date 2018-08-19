import base_station
import time

if __name__ == "__main__":
    bs = base_station.BaseStation()
    bs.enable_receiver()
    bs.radio.print_details()

    while True:
        time.sleep(1)
