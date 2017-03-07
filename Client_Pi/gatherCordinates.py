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
  for i in range(2000):
  #It may take a second or two to get good data
  #print gpsd.fix.latitude,', ',gpsd.fix.longitude,'  Time: ',gpsd.utc
 
    os.system('clear')
	if i > 90 and i < 110:
		file = open("text1.txt", "a")
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
	if i > 110 and i < 120:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >120 and i < 140:
		file = open("text1.txt", "a")
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
	if i > 140 and i < 150:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >150 and i < 170:
		file = open("text1.txt", "a")
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
	if i > 170 and i < 180:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >180 and i < 200:
		file = open("text1.txt", "a")
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
	if i > 200 and i < 210:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >210 and i < 230:
		file = open("text1.txt", "a")
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
	if i > 230 and i < 240:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >240 and i < 260:
		file = open("text1.txt", "a")
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
	if i > 260 and i < 270:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >270 and i < 290:
		file = open("text1.txt", "a")
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
	if i > 290 and i < 300:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >300 and i < 320:
		file = open("text1.txt", "a")
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
	if i > 320 and i < 330:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >330 and i < 350:
		file = open("text1.txt", "a")
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
	if i > 350 and i < 360:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >360 and i < 380:
		file = open("text1.txt", "a")
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
	if i > 380 and i < 390:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >390 and i < 410:
		file = open("text1.txt", "a")
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
	if i > 410 and i < 420:
		LCD1602.write(0, 0, "Move")
		file = open("text1.txt", "a")
		file.write("\n")
	if i >420 and i < 440:
		file = open("text1.txt", "a")
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
	if i > 440 and i < 450:
		LCD1602.write(0, 0, "Done")
		file = open("text1.txt", "a")
		file.write("\n")
	
	
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
    
    time.sleep(2) #set to whatever
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
