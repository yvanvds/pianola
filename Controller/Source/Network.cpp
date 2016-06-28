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
  , udpSendSocket(new DatagramSocket)
  , udpRecvSocket(new DatagramSocket)
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
  udpSendSocket->setEnablePortReuse(true);
  udpSendSocket->bindToPort(UDP_PORT);
  udpSendSocket->joinMulticast(MULTICAST);

  udpRecvSocket->bindToPort(UDP_PORT + 1);
  startTimer(1000);
}

Network::~Network() {
  stopTimer();

  udpSendSocket->shutdown();
  udpRecvSocket->shutdown();
  oscReceiver->disconnect();
}

void Network::oscMessageReceived(const OSCMessage & message) {
  // tokenize addressPattern
  Array<String> tokens;
  OSCTokenize(tokens, message.getAddressPattern().toString());

  // all AddressPatterns should at least be 3 parts, first is project name
  if (tokens.size() < 3) goto unhandled; // important!!! (robot handleMessage depends on this check)
  if (tokens[0] != PROJECT) goto unhandled;

  Meccanoid * m = Robots().getMeccanoid(tokens[1]);

  // if this is a meccanoid, let it take care of the message
  if (m != nullptr) {
    m->handleMessage(tokens, message);
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
  if (udpSendSocket->waitUntilReady(false, 5) == 1) {
    udpSendSocket->write(MULTICAST, UDP_PORT, "identify", sizeof("identify"));
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

  int bytesRead = udpRecvSocket->read(&udpBuffer, 1024, false, udpSender, udpPort);
  if (bytesRead > 0) {
    String name;
    for (int i = 0; i < bytesRead; i++) {
      name += udpBuffer[i];
    }

    Meccanoid * m = Robots().getMeccanoid(name);

    if (m != nullptr) {
      m->resetLastSeen();
      if (m->getIp() != udpSender) {
        m->setIp(udpSender);
        m->initialize();
      }
      
    }
  }

  WindowPtr->updateRobotGui();
}