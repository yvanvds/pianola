import socket
from Messages import Message

from pythonosc import osc_message_builder, udp_client
import time

class ConnectorClass:
  """description of class"""

  def __init__(self):
    self.ip = socket.gethostbyname(socket.gethostname())
    dot = self.ip.rfind(".") + 1
    self.ip_base = self.ip[:dot]
    self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    self.sock.setblocking(0)
    self.connected = False

  def connect(self, id):
    while self.isConnected() == False:
      self.announce(id)
      time.sleep(1)
      self.waitForAcknowledge()
      time.sleep(1)
    print("Connected to Controller!")

  def announce(self, id):
    for i in range(1, 254):
      nextIP = self.ip_base + str('{0}').format(i)
      self.sock.sendto(bytes(id, 'ASCII'), (nextIP, 3456) )

  def waitForAcknowledge(self):
    try:
      data, self.addr = self.sock.recvfrom(64)
      stringdata = data.decode('ASCII')
      if stringdata == "acknowledged\x00": 
        self.connected = True
    except:
      print("No controller found")
 
  def isConnected(self):
    return self.connected

  def getAddress(self):
    return self.addr




