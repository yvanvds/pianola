import sys
sys.path.insert(0, '/usr/lib/python2.7/bridge')

import Queue
from Messages import MB

try:
  from bridgeclient import BridgeClient as bridgeclient
except ImportError:
  # for windows development without arduino bridge
  from fakeBridge import fakeBridge as bridgeclient

#############################################################

class MeccaBridge:
  def __init__(self):
    self.bridge = bridgeclient()
    self.messageChanged = False
    self.message = bytearray(MB.NUM)
    self.changeValue = 1

    # initial (invalid) pin assignment
    self.pin1 = 0
    self.pin2 = 0
    self.pin3 = 0

#############################################################

  def sendMessages(self): 
    if self.messageChanged == True:
      # update change indicator
      self.message[MB.CHANGE] = self.changeValue
      self.changeValue += 1

      # i'm not sure how python handles byte overflows???
      if self.changeValue == 256:
        self.changeValue = 0

      # send message
      # print ','.join([str(i) for i in self.message])
      self.bridge.put("M", "".join(map(chr, self.message)))
      self.messageChanged = False

############################################################

  def sendServoPosition(self, pin, servo, position, time):
    offset = self.getServoOffset(pin, servo)
    
    # put bytes in message
    self.message[offset    ] = position
    self.message[offset + 1] = time
    self.messageChanged      = True

###########################################################
    
  def sendInit(self, pinNr, pinID):
    if pinNr == 1:
      self.pin1 = pinID
      self.message[MB.PIN_ID1] = pinID
    elif pinNr == 2:
      self.pin2 = pinID
      self.message[MB.PIN_ID2] = pinID
    elif pinNr == 3:
      self.pin3 = pinID
      self.message[MB.PIN_ID3] = pinID

###########################################################

  def sendPinLight(self, pin, servo, color):
    offset = self.getServoOffset(pin, servo)
    self.message[offset + 2] = color
    self.messageChanged      = True

###########################################################
    
  def sendHeadLight(self, r, g, b, f):
    self.message[MB.LIGHT_R] = r
    self.message[MB.LIGHT_G] = g
    self.message[MB.LIGHT_B] = b
    self.message[MB.LIGHT_F] = f
    self.messageChanged      = True

###########################################################

  def getServoOffset(self, pin, servo):
    offset = 0
    # add pin offset
    if pin == self.pin1:
      offset = MB.ID1_SERVO0_POS
    elif pin == self.pin2:
      offset = MB.ID2_SERVO0_POS
    elif pin == self.pin3:
      offset = MB.ID3_SERVO0_POS
    # add servo offset (3 messages for each servo)
    offset += (servo * 3)
    return offset