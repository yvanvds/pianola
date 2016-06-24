from OSC import OSCServer
import socket
import types
import time
from MeccaBridge import MeccaBridge

def handle_timeout(self):
    self.timed_out = True

class OSCServerClass:

  def __init__(self, id, port):
    self.robot = id

    self.bridge = MeccaBridge()

    self.server = OSCServer((socket.gethostbyname(socket.gethostname()), port))
    self.server.timeout = 0
    self.active = True
    self.server.handle_timeout = types.MethodType(handle_timeout, self.server)

    self.server.addMsgHandler("/" + self.robot + "/servo1", self.servo1Handler)
    self.server.addMsgHandler("/" + self.robot + "/servo2", self.servo2Handler)
    self.server.addMsgHandler("/" + self.robot + "/servo3", self.servo3Handler)
    self.server.addMsgHandler("/" + self.robot + "/servo4", self.servo4Handler)
    self.server.addMsgHandler("/" + self.robot + "/servo5", self.servo5Handler)
    self.server.addMsgHandler("/" + self.robot + "/servo6", self.servo6Handler)
    self.server.addMsgHandler("/" + self.robot + "/servo7", self.servo7Handler)
    self.server.addMsgHandler("/" + self.robot + "/servo8", self.servo8Handler)

    self.server.addMsgHandler("/" + self.robot + "/init", self.initHandler)
    
  def run(self):
    print("serving on {}".format(self.server.server_address))
    self.server.running = True
    while self.server.running:
      self.server.handle_request()
      time.sleep(0.001);

  def servo1Handler(self, path, tags, args, source):
    self.bridge.sendServoPosition(0, 0, args[0], 100)

  def servo2Handler(self, path, tags, args, source):
    self.bridge.sendServoPosition(0, 1, args[0], 100)

  def servo3Handler(self, path, tags, args, source):
    self.bridge.sendServoPosition(0, 2, args[0], 100)

  def servo4Handler(self, path, tags, args, source):
    self.bridge.sendServoPosition(1, 0, args[0], 100)

  def servo5Handler(self, path, tags, args, source):
    self.bridge.sendServoPosition(1, 1, args[0], 100)

  def servo6Handler(self, path, tags, args, source):
    self.bridge.sendServoPosition(1, 2, args[0], 100)

  def servo7Handler(self, path, tags, args, source):
    self.bridge.sendServoPosition(2, 0, args[0], 100)

  def servo8Handler(self, path, tags, args, source):
    self.bridge.sendServoPosition(2, 1, args[0], 100)

  def initHandler(self, path, tags, args, source):
    self.bridge.sendInit()



