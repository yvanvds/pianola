from Connector import ConnectorClass
import time

robotName = "igor"
connector = ConnectorClass()

""" Setup connection and announce self,
    then wait for Controller app to acknowledge
    our request
"""

connector.connect(robotName)





