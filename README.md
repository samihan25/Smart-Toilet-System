# smart-toilet

Required items:
– Raspberry PI 3 & SD Card with ubuntu-mate Operating System https://www.raspberrypi.org/products/raspberry-pi-3-model-b/
– MQ135 sensor pack
– 4 x pitch jumpers

Preparing Raspberry PI 3 & SHDC:
Create the setup as follows:
1. Download below two as described https://ubuntu-mate.org/raspberry-pi/
– 7-Zip to extract the image.
– Win32 Disk Imager to write the image.
2. Extracted ‘ubuntu-mate from zip and flashed SHCD using Win32 Disk Imager
3. Put the SHCD into slot and power-up the Raspberry PI 3.
4. After ubuntu-mate is up, execute following on the terminal:

sudo apt-get update
sudo apt-get upgrade
sudo apt-get install git                      //if git not installed


"""
GAS Sensor MQ135 using Raspberry Pi 

"""
# Import all the libraries we need to run
import sys
import RPi.GPIO as GPIO
import os
from time import sleep
import Adafruit_DHT
import urllib2
import datetime

TRUE = 1
FALSE = 0

DEBUG = 1

# Setup the pins we are connect to
MQpin = 12

#Setup our API and delay
#myAPI = "***Insert Your API CODE HERE***"
myDelay = 5 #how many seconds between posting data

GPIO.setmode(GPIO.BCM)
GPIO.setup(MQpin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)


def getSensorData():
     return (str(GPIO.input(MQpin)))

   
# main() function
def main():
    
    print 'starting...'

    while True:
        try:
            GAS = getSensorData()

            LT = datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S')

            print LT + " : " + GAS             

            sleep(int(myDelay))
        except:
            print " " 
            print "MQ135 :" + GAS
            print 'exiting.'
            break

# call main
if __name__ == '__main__':
    main()rin

Connect as illustrated in picture:
VCC (MQ135 board) <-> pin02 (RPi-3 3.3v)
Ground (MQ135 board) <-> pin30 (RPi-3 Ground)
DO (MQ135 board) <-> pin32 (RPi-3 GPIO-12)
AO (MQ135 board) <-> not used yet
