import socket
import struct
from Messages import Message

from pythonosc import osc_message_builder, udp_client
import time

class ConnectorClass:
  """description of class"""

  def __init__(self, id):
    self.ip = socket.gethostbyname(socket.gethostname())
    self.id = id
    self.recvsock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    self.recvsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    self.recvsock.bind(('', 3456))
    mreq = struct.pack("4sl", socket.inet_aton('239.255.42.99'), socket.INADDR_ANY)
    self.recvsock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

    self.sendsock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

  def checkMulticast(self):
    while True:
      try:
        data, self.addr = self.recvsock.recvfrom(64)
        stringdata = data.decode('ASCII')
        if stringdata == "identify\x00": 
          self.sendsock.sendto(bytes(self.id, 'ASCII'), (self.addr[0], 3457))
      except:
          pass

  def getAddress(self):
    return self.addr




