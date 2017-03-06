#! /usr/bin/python
# Written by Dan Mandle http://dan.mandle.me September 2012
# License: GPL 2.0
 
import os
from gps import *
from time import *
import time
import LCD1602
import threading
 
gpsd = None #seting the global variable
 
os.system('clear') #clear the terminal (optional)
def setup():
        LCD1602.init(0x27, 1)	# init(slave address, background light)
        LCD1602.clear()
        time.sleep(2)
        LCD1602.write(0, 0, 'Greetings!!')
	LCD1602.write(1, 1, 'from SunFounder')
	time.sleep(2)
        LCD1602.clear() 
class GpsPoller(threading.Thread):
  def __init__(self):
    threading.Thread.__init__(self)
    global gpsd #bring it in scope
    gpsd = gps(mode=WATCH_ENABLE) #starting the stream of info
    self.current_value = None
    self.running = True #setting the thread running to true
 
  def run(self):
    global gpsd
    while self.running: #was gpsp.running
      gpsd.next() #this will continue to loop and grab EACH set of gpsd info to clear the buffer
 
if __name__ == '__main__':
  gpsp = GpsPoller() # create the thread
  setup()
  gpsp.start() # start it up
  time.sleep(3)
  a=1
  #while True:
  for i in range(10):
  #It may take a second or two to get good data
  #print gpsd.fix.latitude,', ',gpsd.fix.longitude,'  Time: ',gpsd.utc
 
    os.system('clear')

    file = open("text3.txt", "a")
    file.write("%s" % gpsd.fix.latitude)
    file.write("\t")
    file.write("%s" % gpsd.fix.longitude)
    file.write("\t")
    file.write("%s" % gpsd.fix.speed)
    file.write("\t")
    #file.write("%s" % gpsd.fix.time)
    #file.write("\t")
    file.write("%s" % a)
    file.write("\n")
    file.close()
    LCD1602.write(0, 0, str(gpsd.fix.latitude))
    LCD1602.write(0, 1, str(gpsd.fix.longitude))
    print
    print ' GPS reading'
    print '----------------------------------------'
    print 'latitude    ' , gpsd.fix.latitude
    print 'longitude   ' , gpsd.fix.longitude
    print 'time utc    ' , gpsd.utc,' + ', gpsd.fix.time
    print 'altitude (m)' , gpsd.fix.altitude
    print 'eps         ' , gpsd.fix.eps
    print 'epx         ' , gpsd.fix.epx
    print 'epv         ' , gpsd.fix.epv
    print 'ept         ' , gpsd.fix.ept
    print 'speed (m/s) ' , gpsd.fix.speed
    print 'climb       ' , gpsd.fix.climb
    print 'track       ' , gpsd.fix.track
    print 'mode        ' , gpsd.fix.mode
    print 'sats        ' , gpsd.satellites
    print 	
    
    time.sleep(3) #set to whatever
    LCD1602.clear()
   # if a > 20:
    #  print "\nKilling Thread..."
    #  gpsp.running = False
     # gpsp.join() # wait for the thread to finish what it's doing
     # break
    #a+=1
  gpsp.running = False
  gpsp.join()
  print "Done.\nExiting."  
