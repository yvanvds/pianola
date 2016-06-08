import socket
from Messages import Message

from pythonosc import osc_message_builder, udp_client

class ConnectorClass:
  """description of class"""

  def __init__(self):
    self.ip = socket.gethostbyname(socket.gethostname())
    dot = self.ip.rfind(".") + 1
    self.ip_base = self.ip[:dot]
    self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

  def announce(self):
    for i in range(1, 254):
      nextIP = self.ip_base + str('{0}').format(i)
      self.sock.sendto(bytes("igor", 'ASCII'), (nextIP, 3456) )
 


