from Connector import ConnectorClass
from OSCServer import OSCServerClass

import time

robotName = "igor"
connector = ConnectorClass()

""" Setup connection and announce self,
    then wait for Controller app to acknowledge
    our request
"""

connector.connect(robotName)

server = OSCServerClass(robotName, 34567)
server.run()




