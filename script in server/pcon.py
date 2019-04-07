#!/usr/bin/env python
import RPi.GPIO as GPIO
from time import sleep
import os
pin = 17
host = '192.168.123.195'
GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, GPIO.OUT, initial=GPIO.LOW)
def pcon():
    GPIO.output(pin, GPIO.HIGH)
    sleep(0.5)
    GPIO.output(pin, GPIO.LOW)

if os.system("ping %s -c 3" %host) != 0:
    pcon()
    print("Turning on")
else:
    print("PC already on")
GPIO.cleanup()
