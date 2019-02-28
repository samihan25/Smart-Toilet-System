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
