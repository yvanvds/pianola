#!/usr/bin/python

from Connector import ConnectorClass
from OSCServer import OSCServerClass

import time
import threading

robotName = "igor"
connector = ConnectorClass(robotName)
oscServer = OSCServerClass(robotName, 34567)

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



