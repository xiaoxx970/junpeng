#!/usr/bin/env python
#在树莓派上运行，pin17（BCM）接到电脑主板开机线负极，正极接3v3，host写电脑局域网IP判断开机就不在嗯电源键
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
