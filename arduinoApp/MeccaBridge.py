import sys
sys.path.insert(0, '/usr/lib/python2.7/bridge')

import Messages

try:
  from bridgeclient import BridgeClient as bridgeclient
except ImportError:
  # for windows development without arduino bridge
  from fakeBridge import fakeBridge as bridgeclient

class MeccaBridge:
  def __init__(self):
    self.messageCount = 0
    self.bridge = bridgeclient()
    
    # init meccanoid
    message = str(Messages.Command.MeccanoidInitialise) + str(' 1')
    self.sendMessage(message)

  def sendMessage(self, message):
    self.bridge.put('COUNT', str(self.messageCount))
    self.messageCount += 1
    self.bridge.put('MESSAGE', message)

  def sendServoPosition(self, chain, servo, position, time):
    message = str(Messages.Command.MeccanoidSetServoMotorPosition)
    message += str(' ') + str(chain) + str(' ') + str(servo) + str(' ') + str(position) + str(' ') + str(time)
    self.sendMessage(message)
    
  def sendInit(self):
    message = str(Messages.Command.MeccanoidInitialise)
    message += str( ' 2')
    self.sendMessage(message)

