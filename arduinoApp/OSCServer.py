from pythonosc import dispatcher
from pythonosc import osc_server
import socket

class OSCServerClass:

  def __init__(self, id, port):
    self.robot = id
    self.dispatcher = dispatcher.Dispatcher()
    self.dispatcher.map("/" + self.robot + "/servo1", self.servoHandler, 1)
    self.dispatcher.map("/" + self.robot + "/servo2", self.servoHandler, 2)

    self.server = osc_server.BlockingOSCUDPServer(
      (socket.gethostbyname(socket.gethostname()), port), self.dispatcher)
    
    
  def run(self):
    print("serving on {}".format(self.server.server_address))
    self.server.serve_forever()   

  def servoHandler(self, unused_addr, args, servoNr): 
    print("[{0}] ~ {1}".format(args[0], servoNr))


