#CECI est un thread qui va tourner de manière indéfénie

import serial

import time

def count_words(a):
    ser = serial.Serial('/dev/ttyUSB0')
    while(True):
        print('TWSS')
        time.sleep(5)

        u=ser.readline().decode()
        print(u)

        time.sleep(2)


    return u
