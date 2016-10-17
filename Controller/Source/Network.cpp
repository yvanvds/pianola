/*
  ==============================================================================

    Network.cpp
    Created: 4 Jun 2016 6:26:24pm
    Author:  yvan

  ==============================================================================
*/

#include "Network.h"
#include "MonitorWindow.h"
#include "Defines.h"
#include "Utilities.h"
#include "Robots.h"

Network::Network(MonitorWindow * monitorWindow)
  : oscReceiver(new OSCReceiver)
  , udpMulticastSocket(new DatagramSocket)
  , udpMessageSocket(new DatagramSocket)
  , multicastTimer(5)
  , monitorWindow(monitorWindow)
  , connected(false)
{

  // setup osc
  oscReceiver->addListener(this);
  oscReceiver->registerFormatErrorHandler(
    [this] (const char * data, int dataSize) 
    {
      this->monitorWindow->getLog()->addInvalidPacket(data, dataSize);
    }
  );

  // setup udp (for discovering robots on network)
  udpMulticastSocket->setEnablePortReuse(true);
  udpMulticastSocket->bindToPort(MULTICAST_PORT);
  udpMulticastSocket->joinMulticast(MULTICAST);

  udpMessageSocket->bindToPort(MESSAGE_PORT);
  startTimer(1000);
}

Network::~Network() {
  stopTimer();

  udpMulticastSocket->shutdown();
  udpMessageSocket->shutdown();
  oscReceiver->disconnect();
}

void Network::oscMessageReceived(const OSCMessage & message) {
  // tokenize addressPattern
  //Array<String> tokens;
  //OSCTokenize(tokens, message.getAddressPattern().toString());
  Robot * r = nullptr;
  r = Robots().getRobot(message[0].getString());

  if (r != nullptr) {
    r->handleMessage(message);
  }
  else {
    goto unhandled;
  }
  return;

unhandled:
  ToLog("Unhandled message:");
  ToLog(message);
  
}

void Network::oscBundleReceived(const OSCBundle & bundle) {
  monitorWindow->getLog()->addMessage(bundle);
}

void Network::connect() {
  if (oscReceiver->connect(OSC_PORT)) {
    ToLog(String("OSC listening on port ") + String(OSC_PORT));
    connected = true;
  }
  else {
    handleConnectError();
  }
}

void Network::disconnect() {
  if (oscReceiver->disconnect()) {
    ToLog(String("OSC disconnected from port ") + String(OSC_PORT));
    connected = false;
  }
  else {
    handleDisconnectError();
  }
}

void Network::handleConnectError() {
  ToLog(
    "Error: OSC could not connect to port "
    + String(OSC_PORT)
    + ". Perhaps another controller instance is running?"
  );
}

void Network::handleDisconnectError() {
  ToLog(String("Error: OSC could not disconnect from port ") + String(OSC_PORT));
}

bool Network::isConnected() {
  return connected;
}

void Network::requestIdentify() {
  if (udpMulticastSocket->waitUntilReady(false, 5) == 1) {
    udpMulticastSocket->write(MULTICAST, MULTICAST_PORT, "identify", sizeof("identify"));
  }
}

void Network::timerCallback() {
  Robots().update();
  
  // request client discovery on multicast address every 30 seconds
  multicastTimer--;
  if (multicastTimer == 0) {
    multicastTimer = 15;
    requestIdentify();
  }

  while (true) {
	  int bytesRead = udpMessageSocket->read(&udpBuffer, 1024, false, udpSender, udpPort);
	  if (bytesRead > 0) {
		  String name;
		  String port; // used for virtual robots
		  bool writePort = false;
		  for (int i = 0; i < bytesRead; i++) {
			  if (!writePort) {
				  if (udpBuffer[i] == ':') writePort = true;
				  else name += udpBuffer[i];
			  }
			  else {
				  port += udpBuffer[i];
			  }

		  }

		  Meccanoid * m = Robots().getMeccanoid(name);

		  if (m != nullptr) {
			  m->resetLastSeen();
			  if (m->getIp() != udpSender) {
				  m->setIp(udpSender);
				  m->initialize();
				  m->assignSocket(udpMessageSocket.get());
			  }
		  }

		  VirtualBot * v = Robots().getVirtualBot(name);

		  if (v != nullptr) {
			  v->resetLastSeen();
			  if (v->getIp() != udpSender) {
				  v->setIp(udpSender);
				  v->setPort(port.getIntValue());
				  v->initialize();
				  v->assignSocket(udpMessageSocket.get());
			  }
		  }
	  }
	  else {
		  break; // no new network message
	  }
  }

  WindowPtr->updateRobotGui();
}