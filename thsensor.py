# -*- coding: utf-8 -*-
# @Author: Ramon Melo
# @Date:   2018-01-09
# @Last Modified by:   Ramon Melo
# @Last Modified time: 2018-01-09

import machine
import dht
import time

class THSensor(object):

    def __init__(self, pin):
        self.sensor = dht.DHT22(machine.Pin(int(2)))
        self.last = 0

        self.last_temperature = 0
        self.last_humidity = 0

    def data(self):
        if (time.time() - self.last > 5):
            self.last = time.time()

            self.sensor.measure()

            self.last_temperature = self.sensor.temperature()
            self.last_humidity = self.sensor.humidity()

        return self.last_temperature, self.last_humidity
