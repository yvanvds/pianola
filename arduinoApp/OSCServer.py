from OSC import OSCServer
import socket
import types
import time
from MeccaBridge import MeccaBridge

def handle_timeout(self):
    self.timed_out = True

########################################################################

class OSCServerClass:
  def __init__(self, id, ip, port):
    self.robot = id

    self.bridge = MeccaBridge()

    self.server = OSCServer((ip, port))
    self.server.timeout = 0
    self.active = True
    self.server.handle_timeout = types.MethodType(handle_timeout, self.server)

    self.server.addMsgHandler("/" + self.robot + "/pinMove"  , self.pinMoveHandler  )
    self.server.addMsgHandler("/" + self.robot + "/pinLight" , self.pinLightHandler )
    self.server.addMsgHandler("/" + self.robot + "/init"     , self.initHandler     )
    self.server.addMsgHandler("/" + self.robot + "/headLight", self.headLightHandler)

    self.gotMessage = False
    
#######################################################################

  def run(self):
    print("serving on {}".format(self.server.server_address))
    self.server.running = True
    while self.server.running:
      while True:
        self.server.handle_request()
        if not self.gotMessage:
          break
        self.gotMessage = False

      self.bridge.sendMessages()
      time.sleep(0.01);

######################################################################

  def pinMoveHandler(self, path, tags, args, source):
    #print(path + "\n")
    #print ', '.join(map(str, args))
    self.bridge.sendServoPosition(args[0], args[1], args[2], args[3])
    self.gotMessage = True
 
######################################################################    
       
  def pinLightHandler(self, path, tags, args, source):
    self.bridge.sendPinLight(args[0], args[1], args[2])
    self.gotMessage = True

######################################################################

  def initHandler(self, path, tags, args, source):
    self.bridge.sendInit(args[0], args[1])
    self.gotMessage = True

######################################################################

  def headLightHandler(self, path, targs, args, source):
    self.bridge.sendHeadLight(args[0], args[1], args[2], args[3])
    self.gotMessage = True

