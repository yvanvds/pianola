#!/usr/bin/python

from Connector import ConnectorClass
from OSCServer import OSCServerClass

import time
import threading
import ConfigParser
import socket

def getIP(routerAddress):
  s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  s.connect((routerAddress, 0))
  return s.getsockname()[0]

config = ConfigParser.SafeConfigParser()
config.read('/mnt/sda/config.cfg')
robotName = config.get('robot options', 'name', 0)
routerAddress = config.get('network', 'routeraddress', 0)
ipAddress = getIP(routerAddress)

print("Robot name: " + robotName + "\n")
print("Address   : " + ipAddress + "\n")

connector = ConnectorClass(robotName)
oscServer = OSCServerClass(robotName, ipAddress, 34567)

# Start thread on multicast group to 
# send our identity to the Controller

class myThread(threading.Thread):
  def __init__(self, threadID, name):
    threading.Thread.__init__(self)
    self.threadID = threadID
    self.name = name

  def run(self):
    print("Starting " + self.name + "\n")
    connector.checkMulticast()

idThread = myThread(1, "UDP Listener Thread")
idThread.start()

# Run osc Server until app shutdown
oscServer.run()



